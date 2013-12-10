//
//  FontFace.cpp
//  vectormap
//
//  Created by Adam Eskreis on 5/20/13.
//  Copyright (c) 2013 Adam Eskreis. All rights reserved.
//

#include <Challenge/Challenge.h>
#include <Challenge/Font/FontFace.h>

namespace challenge
{
    FontFace::FontFace(FT_Library library, FontFile &file, int size)
    {
        FT_Error error;
        error = FT_New_Face(library, file.filepath.c_str(), 0, &mFace);
        if (error) {
            throw "Failed to create FreeType face";
        }
        
        error = FT_Set_Pixel_Sizes(mFace, 0, size);
        if (error) {
            throw "Failed to set pixel size";
        }
        
        mHasKerning = FT_HAS_KERNING(mFace);
        mHorizontal = FT_HAS_HORIZONTAL(mFace);
        mVertical = FT_HAS_VERTICAL(mFace);
        
        mGlyphRanges = file.glyphRanges;
    }
    
    FontFace::~FontFace()
    {
        FT_Done_Face(mFace);
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
    
    int FontFace::GetMaxCharHeight()
    {
        return mFace->max_advance_height >> 6;
    }
    
    int FontFace::GetLineHeight()
    {
        return mFace->height >> 6;
    }
    
    int FontFace::GetKerning(Glyph *leftGlyph, Glyph *rightGlyph)
    {
        if (mHasKerning) {
            FT_Vector delta;
            FT_Get_Kerning(mFace, leftGlyph->mGlyphIndex, rightGlyph->mGlyphIndex
                           ,FT_KERNING_UNSCALED, &delta );
            return delta.x >> 6;
        }
        
        return 0;
    }
};