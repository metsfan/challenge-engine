//
//  FontFace.h
//  vectormap
//
//  Created by Adam Eskreis on 5/20/13.
//  Copyright (c) 2013 Adam Eskreis. All rights reserved.
//

#pragma once

#include <Challenge/Challenge.h>
#include <Challenge/Font/Types.h>
#include <ft2build.h>
#include FT_FREETYPE_H
#include <Challenge/Font/Glyph.h>

namespace challenge
{
    class FontFace
    {
    public:
        FontFace(FT_Library library, FontFile &file, int size, bool hintingEnabled = true);
        ~FontFace();
        
        void SetSize(int size);
        
        bool ContainsGlyph(int character);
        
        double GetMaxCharHeight();
        double GetLineHeight();
        
        bool HasKerning() { return mHasKerning; }
        bool IsHorizontal() { return mHorizontal; }
        bool IsVertical() { return mVertical; }
        
        FT_Face& GetFTFace() { return mFace; }
        
        double GetKerning(Glyph *leftGlyph, Glyph *rightGlyph);
        
        bool IsHintingEnabled() const { return mHintingEnabled;}
        
        const FontFile& GetFile() const {return mFile;}
        
    private:
        FT_Face mFace;
        FontFile mFile;
        std::vector<Range> mGlyphRanges;
        int mSize;
        bool mHasKerning;
        bool mHorizontal;
        bool mVertical;
        bool mHintingEnabled;
    };
};
