//
//  FontFace.h
//  vectormap
//
//  Created by Adam Eskreis on 5/20/13.
//  Copyright (c) 2013 Adam Eskreis. All rights reserved.
//

#pragma once

#include <Challenge/Challenge.h>
#include <Challenge/Font/FontTypes.h>
#include <Challenge/Font/Glyph.h>

#include <ft2build.h>
#include FT_FREETYPE_H

namespace challenge
{
    class FontFace
    {
    public:
        FontFace(FT_Library library, FontFile &file, int size);
        ~FontFace();
        
        bool ContainsGlyph(int character);
        
        int GetMaxCharHeight();
        int GetLineHeight();
        
        bool HasKerning() { return mHasKerning; }
        bool IsHorizontal() { return mHorizontal; }
        bool IsVertical() { return mVertical; }
        
        FT_Face& GetFTFace() { return mFace; }
        
        int GetKerning(Glyph *leftGlyph, Glyph *rightGlyph);
        
    private:
        FT_Face mFace;
        std::vector<Range> mGlyphRanges;
        bool mHasKerning;
        bool mHorizontal;
        bool mVertical;
    };
};
