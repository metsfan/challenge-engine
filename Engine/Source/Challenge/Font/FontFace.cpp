//
//  FontFace.cpp
//  vectormap
//
//  Created by Adam Eskreis on 5/20/13.
//  Copyright (c) 2013 Adam Eskreis. All rights reserved.
//

#include <Challenge/Challenge.h>
#include <Challenge/Font/FontFace.h>
#include <Challenge/Disk/File.h>

static const double kOneOver64 = 1.0 / 64.0;

namespace challenge
{
    FontFace::FontFace(FT_Library library, FontFile &file, int size, bool hintingEnabled)
    :mHintingEnabled(hintingEnabled), mFile(file)
    {
        if (File::Exists(file.filepath.c_str()))
        {
            FT_Error error;
            error = FT_New_Face(library, file.filepath.c_str(), 0, &mFace);
            if (error)
            {
                //throw Exception(InternalException, "Freetype", "Failed to create FreeType face");
            }
            
            error = FT_Set_Pixel_Sizes(mFace, 0, size);
            mSize = size;
            if (error) {
                //throw Exception(InternalException, "Freetype", "Failed to set pixel size");
            }
            
            mHasKerning = FT_HAS_KERNING(mFace);
            mHorizontal = FT_HAS_HORIZONTAL(mFace);
            mVertical = FT_HAS_VERTICAL(mFace);
            
            mGlyphRanges = file.glyphRanges;
        }
        else
        {
            Logger::Log(LogError, "Attempting to use font face with missing file: %s", file.filepath.c_str());
        }
    }
    
    FontFace::~FontFace()
    {
        FT_Done_Face(mFace);
    }
    
    void FontFace::SetSize(int size)
    {
        if (mSize != size)
        {
            FT_Error error = FT_Set_Pixel_Sizes(mFace, 0, size);
            mSize = size;
            if (error) {
                //throw Exception(InternalException, "Freetype", "Failed to set pixel size");
            }
        }
    }
    
    bool FontFace::ContainsGlyph(int character)
    {
        for (int i = 0; i < mGlyphRanges.size(); i++) {
            if (mGlyphRanges[i].Contains(character)) {
                return true;
            }
        }
        
        return false;
    }
    
    double FontFace::GetMaxCharHeight()
    {
        double scale = 2.0;//DeviceSpecification::GetDevicePixelDensity();
        return mFace->max_advance_height * kOneOver64  / scale;
    }
    
    double FontFace::GetLineHeight()
    {
        double scale = 2.0;//DeviceSpecification::GetDevicePixelDensity();
        return mFace->height * kOneOver64 / scale;
    }
    
    double FontFace::GetKerning(Glyph *leftGlyph, Glyph *rightGlyph)
    {
        if (mHasKerning) {
            FT_Vector delta;
            FT_Get_Kerning(mFace, leftGlyph->mGlyphIndex, rightGlyph->mGlyphIndex
                           ,FT_KERNING_UNSCALED , &delta );
            return delta.x * kOneOver64 / 2.0;//DeviceSpecification::GetDevicePixelDensity();
        }
        
        return 0.0;
    }
};