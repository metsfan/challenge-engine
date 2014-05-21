//
//  GlyphAtlasTexture.cpp
//  MapEngineLibraryIOS
//
//  Created by Eddie Kimmel on 1/3/14.
//  Copyright (c) 2014 Adam Eskreis. All rights reserved.
//

#include <Challenge/Challenge.h>
#include <Challenge/Font/GlyphAtlasTexture.h>
#include <Challenge/Renderer/GraphicsDevice.h>

namespace challenge
{
    GlyphAtlasTexture::GlyphAtlasTexture(IGraphicsDevice* device, const Size& size)
    : mGlyphAtlas(size), mFrontBuffer(0)
    {
        TEXTURE_DESC desc;
		desc.InternalFormat = TextureFormatAlpha;
		desc.Format = TextureFormatAlpha;

        mTexture2D[0] = device->CreateTexture2D(desc);
        mTexture2D[1] = device->CreateTexture2D(desc);
    }
    
    GlyphAtlasTexture::~GlyphAtlasTexture()
    {
        //mTexture2D[0]->Release();
        //mTexture2D[1]->Release();
    }
    
    GlyphData GlyphAtlasTexture::GetCoordinates(Font* font, int character, unsigned short outlineSize)
    {
        return mGlyphAtlas.GetCoordinates(font, character, outlineSize);
    }
    
    bool GlyphAtlasTexture::ContainsGlyph(Font* font, int character, unsigned short outlineSize)
    {
        return mGlyphAtlas.ContainsGlyph(font, character, outlineSize);
    }
    
    bool GlyphAtlasTexture::IsValid() const
    {
        return mGlyphAtlas.IsValid();
    }
    
    ITexture* GlyphAtlasTexture::GetTexture() const
    {
        return mTexture2D[mFrontBuffer];
    }
    
    void GlyphAtlasTexture::UpdateTextureAsync()
    {
        /*mTexture2D[mFrontBuffer]->PostGraphicsJob([=]()
        {
            this->UpdateTexture();
        });*/
		this->UpdateTexture();
    }
    void GlyphAtlasTexture::UpdateTexture()
    {
        if (!mGlyphAtlas.IsValid())
        {
            mGlyphAtlas.Validate();
            
            // Swap front and back
            mFrontBuffer = (mFrontBuffer + 1) % 2;
            
            // Update the new front texture.
            mTexture2D[mFrontBuffer]->Initialize((BYTE *)mGlyphAtlas.GetData(), mGlyphAtlas.GetSize());
        }
    }
}
