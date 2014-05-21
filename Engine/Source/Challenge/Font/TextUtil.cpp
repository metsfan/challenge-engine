//
//  TextUtil.cpp
//  MapEngineLibraryIOS
//
//  Created by Eddie Kimmel on 3/17/14.
//  Copyright (c) 2014 Adam Eskreis. All rights reserved.
//
#include <Challenge/Challenge.h>
#include <Challenge/Font/TextUtil.h>
#include <Challenge/Font/Font.h>

namespace challenge
{
	Size TextUtil::SizeOfText(const std::wstring& text, Font* font, const TextUtilParams& params)
    {
        std::vector<real> tokenWidths = TextUtil::WidthsOfTokens(text, font, params.outlineSize);
        return TextUtil::SizeOfText(tokenWidths, font->GetMaxCharHeight(), font->GetSpaceWidth(), params);
    }
    
    Size TextUtil::HeuristicSizeOfText(const std::wstring& text, real heuristicCharWidth, real heuristicCharHeight, const TextUtilParams& params)
    {
        std::vector<real> tokenWidths = TextUtil::HeuristicWidthsOfTokens(text, heuristicCharWidth, params.outlineSize);
        return TextUtil::SizeOfText(tokenWidths, heuristicCharHeight, heuristicCharWidth, params);
    }
    
	std::vector<real> TextUtil::WidthsOfTokens(const std::wstring& text, Font* font, int outlineSize)
    {
        std::vector<real> tokenWidths;
        
        real tokenWidth = 0;
        int textSize = text.size();
        for(int i = 0; i < textSize; ++i)
        {
            Glyph* data = font->GetGlyph(text[i], outlineSize);
            if (data->GetCharacter() != ' ')
            {
                tokenWidth += data->GetBearing().x + data->GetAdvance().x;
            }
            else
            {
                tokenWidths.push_back(tokenWidth);
                tokenWidth = 0;
            }
        }
        
        tokenWidths.push_back(tokenWidth);
        
        return tokenWidths;
    }
    
	std::vector<real> TextUtil::HeuristicWidthsOfTokens(const std::wstring& text, real heuristicCharWidth, int outlineSize)
    {
        int outlineBuffer = 2 * outlineSize;
        
        std::vector<real> tokenWidths;
        
        real tokenWidth = 0;
        int textSize = text.size();
        for(int i = 0; i < textSize; ++i)
        {
            if (text[i] != ' ')
            {
                tokenWidth += heuristicCharWidth + outlineBuffer;
            }
            else
            {
                tokenWidths.push_back(tokenWidth);
                tokenWidth = 0;
            }
        }
        
        tokenWidths.push_back(tokenWidth);
        
        return tokenWidths;
    }
    
    Size TextUtil::SizeOfText(const std::vector<real>& tokenWidths, int maxCharHeight, int spaceWidth, const TextUtilParams& params)
    {
        Size size;
        
        int lineHeight = maxCharHeight + params.lineSpacing;
        int numberOfLines = params.maxHeight / lineHeight;
        
        // If a single line is larger than our max height, we can't fit anything.
        if (params.maxHeight > 0 && lineHeight > params.maxHeight)
        {
            return Size(0,0);
        }
        
        // Will be -1 if we want an unlimited number of lines.
        int lastLine = numberOfLines - 1;
        
        int currentLine = 0;
        int numTokensOnLine = 0;
        real lineWidth = 0;
        
        bool finished = false;
        
        for(real tokenWidth : tokenWidths)
        {
            if (finished)
            {
                break;
            }
            
            real widthWithToken = lineWidth + tokenWidth;
            if (numTokensOnLine != 0)
            {
                widthWithToken += spaceWidth;
            }
            
            if (params.maxWidth > 0 && widthWithToken > params.maxWidth)
            {
                // Token is too long for this line
                
                // lastLine is -1 if we have no limit, so this will never be hit.
                if (currentLine == lastLine)
                {
                    size.width = std::max(size.width, widthWithToken);
                    finished = true;
                }
                else
                {
                    // Finish this line and move token to next line
                    currentLine++;
                    if (numTokensOnLine == 0)
                    {
                        // First and only token on this line - place it and we are done
                        size.width = std::max(size.width, widthWithToken);
                        finished = true;
                        
                    }
                    else
                    {
                        // Use the size of the other tokens and continue
                        size.width = std::max(size.width, lineWidth);
                        
                        // If the token was too long for that line, end
                        if (params.maxWidth > 0 && tokenWidth > params.maxWidth)
                        {
                            size.width = std::max(size.width, tokenWidth);
                            finished = true;
                        }
                        else
                        {
                            // Put the token on the next line
                            lineWidth = tokenWidth;
                            numTokensOnLine = 1;
                        }
                    } // If else last line
                }
            }
            else
            {
                lineWidth = widthWithToken;
                numTokensOnLine++;
                size.width = std::max(size.width, lineWidth);
            }
        }
        
        size.width = std::max(size.width, lineWidth);
        
        if (params.maxWidth > 0)
        {
            size.width = std::min((real)params.maxWidth, size.width);
        }
        
        size.height = (1 + currentLine) * lineHeight;
        
        return size;
    }
}
