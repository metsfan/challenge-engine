//
//  Label.cpp
//  MapEngineLibraryIOS
//
//  Created by Adam Eskreis on 8/28/13.
//  Copyright (c) 2013 Adam Eskreis. All rights reserved.
//
#include <Challenge/Challenge.h>
#include <Challenge/GameApplication.h>

#include <Challenge/Renderer/Shape/Label.h>
#include <Challenge/Renderer/Texture.h>
#include <Challenge/Font/GlyphAtlasTexture.h>

namespace challenge
{
    GlyphAtlasTexture* Label::msAtlasTexture = NULL;
    
    static const Size kGlyphAtlasSize(2048, 2048);
    static const char16_t kEllipsisCharacter = 0x2026;
	static const size_t kMaxLineOffsets = 20;
    
    Label::Label(IGraphicsDevice *device) :
        MeshShape(device, "Label"),
        mFont(FontManager::GetDefaultFont()),
        mFontScale(1),
        mAlpha(1),
        mTextColor(Vector4f(0, 0, 0, 1)),
        mFontKey(0),
        mSize(0, 0),
        mAnchorPoint(0,0),
        mLineSpacing(1),
        mHasCutOff(false),
        mNumLines(1),
        mAtlasValid(true),
        mAngle(-1),
        mOutlineSize(0),
        mScale(1.0f)
    {
        mOutlineShape = new MeshShape(device, "label");
        
        this->SetAngle(0);
        
        mGlyphAtlasUniform = device->GetContext()->GetGlobalIndex("ATLAS_TEXTURE");
		mLineOffsetUniform = device->GetContext()->GetGlobalIndex("LINE_OFFSETS");
		mAlphaUniform = device->GetContext()->GetGlobalIndex("ALPHA");
		mColorUniform = device->GetContext()->GetGlobalIndex("COLOR");
		mPositionUniform = device->GetContext()->GetGlobalIndex("POSITION");
		mLabelOriginAndAngleUniform = device->GetContext()->GetGlobalIndex("ORIGIN_ANGLE");
		mScaleUniform = device->GetContext()->GetGlobalIndex("SCALE");

		mLineOffsets.resize(kMaxLineOffsets);
    }
    
    Label::~Label()
    {
        if (msAtlasTexture)
            msAtlasTexture->GetGlyphAtlas()->RemoveListener(this);
        if (mOutlineShape)
            delete mOutlineShape;
    }
    
    void Label::Draw(IGraphicsDevice *device, RenderState &state, PrimitiveType primitiveType)
    {
		if (mText.size() == 0)
		{
			return;
		}

        if (!msAtlasTexture)
        {
            msAtlasTexture = new GlyphAtlasTexture(device, kGlyphAtlasSize);
        }
        
        bool wasAtlasValid = mAtlasValid;
        bool atlasChanged = false;
        
        if (!this->IsValid(true) || !wasAtlasValid)
        {
            // Update our scaled size.
            mScaledSize = mSize * mFontScale;
            if (mScaledSize.width < 1.0)
                mScaledSize.width = std::numeric_limits<int>::max();
            
            GlyphData ellipsis = msAtlasTexture->GetCoordinates(mFont, kEllipsisCharacter, 0);
            GlyphData outlineEllipsis = msAtlasTexture->GetCoordinates(mFont, kEllipsisCharacter, mOutlineSize);
            
            std::vector<GlyphData> glyphs;
            std::vector<GlyphData> outlineGlyphs;
            glyphs.reserve(mText.size());
            outlineGlyphs.reserve(mText.size());
            
            bool success = this->RetrieveGlyphData(glyphs, &atlasChanged, 0);
            
            if (!success)
                return;
            
            success = this->RetrieveGlyphData(outlineGlyphs, &atlasChanged, mOutlineSize);
            
            if (!success)
                return;
            
            // Define some common values
            double fontHeight = (mFont->GetSize() + mOutlineSize) * mFontScale;

            double lineHeight = fontHeight + mLineSpacing;
            unsigned int maxLines = std::floor(mScaledSize.height / lineHeight);
            if (maxLines < 1)
                maxLines = 1;
            
            // Determine the width of each line
            std::vector<double> tokenWidths;
            this->DetermineTokenWidths(outlineGlyphs, tokenWidths);

            std::vector<int> numTokensPerLine;
            
            mLineWidths.clear();
            mHasCutOff = Label::DetermineLineAttributes(tokenWidths, maxLines, mScaledSize.width, mFont->GetSpaceWidth(), mLineWidths, numTokensPerLine);
            mNumLines = mLineWidths.size();
            mTextSize.width = 0;
            
            mTextSize.width = mTextSize.height = 0;
            float minY = fontHeight, maxY = fontHeight;
            
            // Variables to be used in the loop
            std::vector<LabelVertex> buffer;
            std::vector<LabelVertex> outlineBuffer;
            
            buffer.reserve(mText.size() * 6);
            outlineBuffer.reserve(mText.size() * 6);
            
            Point outlineCursor(0, fontHeight);
            int currentToken = 1;
            int currentLine = 0;
            
            bool newLine = true;
            for(int i = 0; i < mText.size(); ++i)
            {
                char16_t nchar = mText[i];
                
                if (nchar == ' ')
                {
                    currentToken++;
                    if (currentToken > numTokensPerLine[currentLine])
                    {
                        currentToken = 1;
                        mLineWidths[currentLine] = outlineCursor.x;
                        currentLine++;
                        
                        // No more lines
                        if (currentLine == mNumLines)
                            break;
                        
                        // Setup next line
                        outlineCursor.y += lineHeight;
                        outlineCursor.x = 0;
                        
                        newLine = true;
                        continue;
                    }
                }
                
                const GlyphData& data = glyphs[i];
                
                const GlyphData& outlineData = outlineGlyphs[i];
                const Vector2i& outlineSize = outlineData.size;
                int outlineKerning = 0;
                
                if(!newLine)
                {
                    outlineKerning = mFont->GetKerning(mText[i - 1], nchar, mOutlineSize, mOutlineSize);
                }
                
                outlineCursor.x += outlineKerning;
                    
                if (mHasCutOff && currentLine + 1 == mNumLines)
                {
                    // We are on the last line and are at risk of needing an ellipse
                    if (outlineCursor.x + outlineSize.x + outlineEllipsis.size.x > mScaledSize.width)
                    {
                        // This character + an ellipse would not fit
                        if (i + 1 != mText.size())
                        {
                            // This is not the last character, so we need to clip something
                            if (i != 0 && mText[i - 1] == ' ')
                            {
                                buffer.resize(buffer.size() - 6);
                            }
                            this->AddGlyphToVertices(outlineBuffer, outlineCursor, outlineEllipsis, currentLine);
                            this->AddGlyphToVertices(buffer, Point(outlineCursor.x + mOutlineSize, outlineCursor.y + mOutlineSize), ellipsis, currentLine);
                            outlineCursor.x += outlineEllipsis.advance;
                            
                            mTextSize.width = std::max(outlineCursor.x, mTextSize.width);
                            break;
                        }
                    }
                }
                
                this->AddGlyphToVertices(outlineBuffer, outlineCursor, outlineData, currentLine);
                this->AddGlyphToVertices(buffer, Point(outlineCursor.x + mOutlineSize, outlineCursor.y + mOutlineSize), data, currentLine);
                
                outlineCursor.x += outlineData.advance;
                mTextSize.width = std::max(outlineCursor.x, mTextSize.width);
                minY = std::min(minY, (float)(outlineCursor.y - outlineData.bearing.y));
                maxY = std::max(maxY, (float)(outlineCursor.y - outlineData.bearing.y + outlineData.size.y));
                newLine = false;
            }
            
            if (currentLine != mNumLines)
            {
                mLineWidths[currentLine] = outlineCursor.x + mOutlineSize;
            }
            
            for(auto& vert : buffer)
            {
                vert.position[1] -= minY;
            }
            
            for(auto& vert : outlineBuffer)
            {
                vert.position[1] -= minY;
            }
            
            mTextSize.height = maxY - minY;
            
            // Update mesh shape
			this->SetData(&buffer[0], buffer.size() * sizeof(LabelVertex), buffer.size(), PrimitiveTypeTriangleList);
            
            if (mOutlineSize > 0)
            {
				mOutlineShape->SetData(&outlineBuffer[0], outlineBuffer.size() * sizeof(LabelVertex), outlineBuffer.size(), PrimitiveTypeTriangleList);
            }
            
            mAtlasValid = true;
            
            if (!msAtlasTexture->IsValid())
            {
                msAtlasTexture->UpdateTextureAsync();
            }
        }
        
        // If the atlas has all of our required glyphs, render.
        if (!atlasChanged)
        {
            mLabelOriginAndAngle.x = mTextSize.width * mAnchorPoint.x;
            mLabelOriginAndAngle.y = mTextSize.height * mAnchorPoint.y;
            
			state.SetShaderData(mGlyphAtlasUniform, msAtlasTexture->GetTexture());
            state.SetShaderData(mPositionUniform, &mPosition);
            
			for (int i = 0; i < mLineWidths.size(); i++) {
                mLineOffsets[i] = this->DetermineLineStart(mLineWidths[i]);
            }

			state.SetShaderData(mLineOffsetUniform, &mLineOffsets[0]);
            state.SetShaderData(mAlphaUniform, &mAlpha);
			state.SetShaderData(mLabelOriginAndAngleUniform, &mLabelOriginAndAngle);
            
			float scale = (1.0 / mFontScale) * mScale;
            state.SetShaderData(mScaleUniform, &scale);
            
            //device->GetContext()->SetActiveTexture(msAtlasTexture->GetTexture(), 0);
            
			device->EnableState(AlphaBlending);
            device->SetBlendingFunction(BlendOne, BlendOneMinusSrcAlpha);
            
            if (mOutlineSize > 0)
            {
				state.SetShaderData(mColorUniform, &mTextOutlineColor);
                
                mOutlineShape->Draw(device, state);
            }

			state.SetShaderData(mColorUniform, &mTextColor);
            
            MeshShape::Draw(device, state);
        }
    }
    
    void Label::AddGlyphToVertices(std::vector<LabelVertex>& buffer, const Point& cursor, const GlyphData& data, int currentLine)
    {
        LabelVertex vertex;
        
        vertex.lineNum = currentLine;
        
        const Vector2i& size = data.size;
        
        double x = cursor.x + data.bearing.x;
        double y = cursor.y - data.bearing.y;
        
        // BL
        vertex.position[0] = x;
        vertex.position[1] = y + size.y;
        vertex.texCoord[0] = data.minCoordinate.x;
        vertex.texCoord[1] = data.maxCoordinate.y;
        buffer.push_back(vertex);
        
        // TL
        vertex.position[0] = x;
        vertex.position[1] = y;
        vertex.texCoord[0] = data.minCoordinate.x;
        vertex.texCoord[1] = data.minCoordinate.y;
        buffer.push_back(vertex);
        
        // BR
        vertex.position[0] = x + size.x;
        vertex.position[1] = y + size.y;
        vertex.texCoord[0] = data.maxCoordinate.x;
        vertex.texCoord[1] = data.maxCoordinate.y;
        buffer.push_back(vertex);
        
        // BR
        vertex.position[0] = x + size.x;
        vertex.position[1] = y + size.y;
        vertex.texCoord[0] = data.maxCoordinate.x;
        vertex.texCoord[1] = data.maxCoordinate.y;
        buffer.push_back(vertex);
        
        // TL
        vertex.position[0] = x;
        vertex.position[1] = y;
        vertex.texCoord[0] = data.minCoordinate.x;
        vertex.texCoord[1] = data.minCoordinate.y;
        buffer.push_back(vertex);
        
        // TR
        vertex.position[0] = x + size.x;
        vertex.position[1] = y;
        vertex.texCoord[0] = data.maxCoordinate.x;
        vertex.texCoord[1] = data.minCoordinate.y;
        buffer.push_back(vertex);
    }
    
    double Label::DetermineLineStart(double lineWidth)
    {
        switch(mHorizontalAlignment)
        {
            case TextAlignLeft:
                return 0;
                break;
            case TextAlignCenter:
                return (mTextSize.width - lineWidth) * 0.5;
                break;
            case TextAlignRight:
                return (mTextSize.width - lineWidth);
                break;
        }
    }
    
    bool Label::RetrieveGlyphData(std::vector<GlyphData>& glyphs, bool* atlasChanged, unsigned short outlineSize)
    {
        // This loop will repeat zero or one times. Zero times if the atlas did not reset during the loop.
        // And one time if the atlas did reset during the loop.
        // If the atlas resets a second time, the atlas simply cannot fit our string and we just leave.
        int num = 0;
        bool& changed = *atlasChanged;
        changed = false;
        
        do
        {
            mAtlasValid = true;
            glyphs.clear();
            for (int i = 0; i < mText.size(); i++)
            {
                if (!msAtlasTexture->ContainsGlyph(mFont, mText[i], outlineSize))
                {
                    changed = true;
                }
                glyphs.push_back(msAtlasTexture->GetCoordinates(mFont, mText[i], outlineSize));
            }
            
            if (!msAtlasTexture->ContainsGlyph(mFont, kEllipsisCharacter, outlineSize))
            {
                changed = true;
            }
            num++;
        } while (!mAtlasValid  && num < 2);
        
        return num != 2;
        // End loop
    }
    
    void Label::DetermineTokenWidths(const std::vector<GlyphData>& glyphs, std::vector<double>& tokenWidths)
    {
        double tokenWidth = 0;
        int textSize = glyphs.size();
        for(int i = 0; i < textSize; ++i)
        {
            const GlyphData& data = glyphs[i];
            if (data.character != ' ')
            {
                tokenWidth += data.size.x;
            }
            else
            {
                tokenWidths.push_back(tokenWidth);
                tokenWidth = 0;
            }
        }
        
        tokenWidths.push_back(tokenWidth);
    }
    
    void Label::DetermineTokenWidths(Font* font, int outlineSize, const std::u16string& text, std::vector<double>& tokenWidths)
    {
        double tokenWidth = 0;
        double oneOverScale = 1.0 / font->GetFontScale();
        for(char16_t c : text)
        {
            Glyph* glyph = font->GetGlyph(c, outlineSize);
            if (c != ' ')
            {
                tokenWidth += outlineSize + std::max(glyph->GetSize().width, glyph->GetAdvance().x) * oneOverScale;
            }
            else
            {
                tokenWidths.push_back(tokenWidth);
                tokenWidth = 0;
            }
        }
        
        tokenWidths.push_back(tokenWidth);
    }
    
    void Label::DetermineTokenWidths(const std::u16string& text, double heuristicCharWidth, std::vector<double>& tokenWidths)
    {
        double tokenWidth = 0;
        int textSize = text.size();
        for(int i = 0; i < textSize; ++i)
        {
            if (text[i] != ' ')
            {
                tokenWidth += heuristicCharWidth;
            }
            else
            {
                tokenWidths.push_back(tokenWidth);
                tokenWidth = 0;
            }
        }
        
        tokenWidths.push_back(tokenWidth);
    }
    
    bool Label::DetermineLineAttributes(const std::vector<double>& tokenWidths, int maxLines, double maxWidth, double spaceWidth, std::vector<double>& lineWidths, std::vector<int>& tokensOnLine)
    {
        int lastLine = maxLines - 1;
        
        double lineWidth = 0;
        int numTokensOnLine = 0;
        
        for(double tokenWidth : tokenWidths)
        {
            double widthWithToken = lineWidth + tokenWidth;
            if (numTokensOnLine != 0)
                widthWithToken += spaceWidth;
            
            if (widthWithToken > maxWidth)
            {
                // Token is too long for this line
                
                if (lineWidths.size() == lastLine)
                {
                    // No more lines left, we will insert an ellipsis here
                    numTokensOnLine++;
                    lineWidth = widthWithToken;
                    lineWidths.push_back(maxWidth);
                    tokensOnLine.push_back(numTokensOnLine);
                    return true;
                }
                else
                {
                    // Finish this line and move token to next line
                    if (numTokensOnLine == 0)
                    {
                        // First and only token on this line - place it and we are done
                        lineWidths.push_back(maxWidth);
                        tokensOnLine.push_back(1);
                        return true;
                    }
                    else
                    {
                        // Use the size of the other tokens and continue
                        lineWidths.push_back(lineWidth);
                        tokensOnLine.push_back(numTokensOnLine);
                        
                        // Put the token on the next line
                        lineWidth = tokenWidth;
                        numTokensOnLine = 1;
                        
                        // If the token was too long for that line, end
                        if (lineWidth > maxWidth)
                        {
                            lineWidths.push_back(maxWidth);
                            tokensOnLine.push_back(1);
                            return true;
                        }
                    }
                } // If else last line
            }
            else
            {
                lineWidth = widthWithToken;
                numTokensOnLine++;
            }
        }
        
        lineWidths.push_back(lineWidth);
        tokensOnLine.push_back(numTokensOnLine);
        return false;
    }
    
    Size Label::GetSize(const std::u16string& text, Font* font, int outlineSize, double lineHeight, double maxWidth, int maxLines)
    {
        std::vector<double> tokenWidths;
        std::vector<double> lineWidths;
        std::vector<int> tokens;
        
        Label::DetermineTokenWidths(font, outlineSize, text, tokenWidths);
        Label::DetermineLineAttributes(tokenWidths, maxLines, maxWidth, font->GetSpaceWidth(), lineWidths, tokens);

        double maxX = 0;
        for(double d : lineWidths)
        {
            if (d > maxX)
                maxX = d;
        }
    
        double maxY = lineHeight * lineWidths.size();
        return Size(maxX, maxY);
    }
    
    Size Label::GetHeuristicSize(const std::u16string& text, double heuristicCharWidth, double heuristicLineHeight, double maxLineWidth, int maxLines)
    {  
        // Determine the width of each line
        std::vector<double> tokenWidths;
        std::vector<double> lineWidths;
        std::vector<int> tokens;
        
        Label::DetermineTokenWidths(text, heuristicCharWidth, tokenWidths);
        Label::DetermineLineAttributes(tokenWidths, maxLines, maxLineWidth, heuristicCharWidth, lineWidths, tokens);
        
        double maxX = 0;
        for(double d : lineWidths)
        {
            if (d > maxX)
                maxX = d;
        }
        double maxY = heuristicLineHeight * lineWidths.size();
        
        return Size(maxX, maxY);
    }
};
