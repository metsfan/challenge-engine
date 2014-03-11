#include <Challenge/Challenge.h>
#include "ImageParser.h"

#include <png/png.h>
#include <png/pngstruct.h>

#include <jpeg/jpeglib.h>

namespace challenge
{
	struct ImageParserPointer
    {
        const unsigned char* data;
        int currentLocation;
    };

	bool ImageParser::Parse(const TByteArray &data, ImageBitmap &outData)
	{
		ImageType type = ImageParser::DetermineImageType(data);
		if(type != ImageTypeUnknown) {
			switch(type) 
			{
			case ImageTypePNG:
				return ImageParser::ParsePNG(data, outData);
				break;

			case ImageTypeJPEG:
				return ImageParser::ParseJPEG(data, outData);
				break;
			};
		}
	}

	bool ImageParser::ParsePNG(const TByteArray &data, ImageBitmap &outData)
	{
		png_structp png_ptr;
        png_infop info_ptr;
        png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);

        if(png_ptr == NULL)
            return false;

        info_ptr = png_create_info_struct(png_ptr);

        if(info_ptr == NULL)
        {
            png_destroy_read_struct(&png_ptr, NULL, NULL);
            return false;
        }

        ImageParserPointer pointer;
        pointer.data = &data[0];
        pointer.currentLocation = 0;

        png_set_read_fn(png_ptr, (png_voidp)(&pointer),
                        [](png_structp png_ptr, png_bytep outBytes, png_size_t count)
                        {
                                if(png_ptr->io_ptr == NULL)
                                {
                                        return;
                                }
                                ImageParserPointer* dataPointer = (ImageParserPointer*)png_get_io_ptr(png_ptr);
                                memcpy(outBytes, &dataPointer->data[dataPointer->currentLocation], count);
                                dataPointer->currentLocation += count;
                        });
        
		png_voidp error_ptr = png_get_error_ptr(png_ptr);

        png_set_sig_bytes(png_ptr, 0);
        
        png_read_png(png_ptr, info_ptr,
                        PNG_TRANSFORM_STRIP_16 | PNG_TRANSFORM_PACKING
                                        | PNG_TRANSFORM_EXPAND, NULL);

        outData.size.width = png_ptr->width;
        outData.size.height = png_ptr->height;
        

        bool hasAlpha;
        switch (png_ptr->color_type)
        {
                case PNG_COLOR_TYPE_RGBA:
                        hasAlpha = true;
                        break;
                case PNG_COLOR_TYPE_RGB:
                        hasAlpha = false;
                        break;
                default:
                        break;
        }

        unsigned int row_bytes = png_get_rowbytes(png_ptr, info_ptr);
		outData.data.resize(outData.size.width * outData.size.height * 4);
        png_bytepp row_pointers = png_get_rows(png_ptr, info_ptr);

        int intHeight = outData.size.height;
        byte *outPtr = &outData.data[0];
        int rgba_row_stride = outData.size.width * 4;
        
		for (int i = 0; i < intHeight; i++)
		{
			png_bytep row = row_pointers[i];
            
			if (hasAlpha) {
				for (int j = 0, k = 0; j < row_bytes; j += 4, k += 4) {
					outPtr[k] = row[j];
					outPtr[k + 1] = row[j + 1];
					outPtr[k + 2] = row[j + 2];
					outPtr[k + 3] = row[j + 3];
				}
			} else {
				for (int j = 0, k = 0; j < row_bytes; j += 3, k += 4) {
					outPtr[k] = row[j];
					outPtr[k+1] = row[j+1];
					outPtr[k+2] = row[j+2];
					outPtr[k+3] = 255;
				}
			}
            
			outPtr += rgba_row_stride;
		}

        png_destroy_read_struct(&png_ptr, &info_ptr, NULL);

		return true;
	}

	bool ImageParser::ParseJPEG(const TByteArray &data, ImageBitmap &outData)
	{
		struct jpeg_decompress_struct cinfo;
        
        struct jpeg_error_mgr jerr;
        
        cinfo.err = jpeg_std_error(&jerr);
        
        jpeg_create_decompress(&cinfo);
        
		jpeg_mem_src(&cinfo, (unsigned char *)&data[0], (unsigned long)data.size());
       
        (void) jpeg_read_header(&cinfo, TRUE);
        
        (void) jpeg_start_decompress(&cinfo);
        
        int row_stride = cinfo.output_width * cinfo.output_components;
        int rgba_row_stride = cinfo.output_width * 4;
        
        JSAMPARRAY buffer = (cinfo.mem->alloc_sarray)((j_common_ptr)&cinfo, JPOOL_IMAGE, row_stride, 1);
        
		outData.size = Size(cinfo.output_width, cinfo.output_height);
        
        int bitmapSize = cinfo.output_width * cinfo.output_height * 4;
        outData.data.resize(bitmapSize);
        
        byte *outPtr = &outData.data[0];
        
        while (cinfo.output_scanline < cinfo.output_height) {
            (void) jpeg_read_scanlines(&cinfo, buffer, 1);
            
            //memcpy(outPtr, buffer, row_stride);
            for (int i = 0, j = 0; i < row_stride; i += 3, j += 4) {
                outPtr[j] = (*buffer)[i];
                outPtr[j+1] = (*buffer)[i+1];
                outPtr[j+2] = (*buffer)[i+2];
                outPtr[j+3] = 255;
            }
            
            outPtr += rgba_row_stride;
        }
        
        jpeg_destroy_decompress(&cinfo);
        
        return true;
	}

	ImageType ImageParser::DetermineImageType(const TByteArray &data)
	{
		if (data[0] == 0x89 &&       // PNG Test
            data[1] == 0x50 &&
            data[2] == 0x4E &&
            data[3] == 0x47 &&
            data[4] == 0x0D &&
            data[5] == 0x0A &&
            data[6] == 0x1A &&
            data[7] == 0x0A) {
            return ImageTypePNG;
        } else if(data[0] == 0xFF && //JPEG Test
                  data[1] == 0xD8) {
            return ImageTypeJPEG;
        }
        
        return ImageTypeUnknown;
	}
};