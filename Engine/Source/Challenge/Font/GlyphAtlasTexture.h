//
//  GlyphAtlasTexture.h
//  MapEngineLibraryIOS
//
//  Created by Eddie Kimmel on 1/3/14.
//  Copyright (c) 2014 Adam Eskreis. All rights reserved.
//

#pragma once

#include <Challenge/Challenge.h>
#include <Challenge/Font/GlyphAtlas.h>
#include <Challenge/Font/Glyph.h>
#include <Challenge/Renderer/Texture.h>

namespace challenge
{
    class IGraphicsDevice;

    class GlyphAtlasTexture
    {
    public:
        
        GlyphAtlasTexture(IGraphicsDevice* device, const Size& size);
        ~GlyphAtlasTexture();
        
        GlyphData GetCoordinates(Font* font, int character, unsigned short outlineSize);
        bool ContainsGlyph(Font* font, int character, unsigned short outlineSize);
        
        ITexture* GetTexture() const;
        GlyphAtlas* GetGlyphAtlas() { return &mGlyphAtlas;}
        
        bool IsValid() const;
        
        // Will dispatch a graphics job to update the texture if required.
        void UpdateTextureAsync();
        
        void UpdateTexture();
        
    private:
        
        GlyphAtlas mGlyphAtlas;
        ITexture *mTexture2D[2];
        int mFrontBuffer;
    };
}