//
//  TextUtil.h
//  MapEngineLibraryIOS
//
//  Created by Eddie Kimmel on 3/17/14.
//  Copyright (c) 2014 Adam Eskreis. All rights reserved.
//

#pragma once

#include <Challenge/Core/BasicTypes.h>

namespace challenge
{
    class Font;
    
    struct TextUtilParams
    {
        int outlineSize = 0;
        int lineSpacing = 0;
        
        /** If set to 0, no maximum width is used */
        int maxWidth = 0;
        
        /** If set to 0, no maximum height is used */
        int maxHeight = 0;
    };
    
    class TextUtil
    {
    public:
        
        /**
         * Returns the size of the text using the given parameters.
         * The width and height of the text will not be greater than the maxWidth and maxHeight specified in the TextUtilParams.
         */
		static Size SizeOfText(const std::wstring& text, Font* font, const TextUtilParams& params = TextUtilParams());
        
        /** Calculates a heuristic size of the text using the given parameters. */
		static Size HeuristicSizeOfText(const std::wstring& text, real heuristicCharWidth, real heuristicCharHeight, const TextUtilParams& params = TextUtilParams());
        
        /** Calculates the width of each word in the text, using the space character as the delimiter. */
		static std::vector<real> WidthsOfTokens(const std::wstring& text, Font* font, int outlineSize = 0);
        
        /** Calculates the width of each word in the text, using the space character as the delimiter. */
		static std::vector<real> HeuristicWidthsOfTokens(const std::wstring& text, real heuristicCharWidth, int outlineSize = 0);
        
    private:
        
		static Size SizeOfText(const std::vector<real>& tokenWidths, int maxCharHeight, int spaceWidth, const TextUtilParams& params = TextUtilParams());
    };
}