//
//  Label.h
//  MapEngineLibraryIOS
//
//  Created by Adam Eskreis on 8/28/13.
//  Copyright (c) 2013 Adam Eskreis. All rights reserved.
//

#pragma once

#include <Challenge/Challenge.h>
#include <Challenge/Renderer/Shape/MeshShape.h>
#include <Challenge/Font/FontEngine.h>

namespace challenge
{
    struct LabelVertex
    {
        float position[2];
        float texCoord[2];
        float lineNum;
    };
    
    
    class GlyphAtlasTexture;
    class Label : public MeshShape,
                  public Validatable,
                  public IGlyphAtlasListener
    {
    public:
        
        Label(IGraphicsDevice *device);
        ~Label();
        
        void SetText(const std::wstring &text)
        {
            mText = text;
            this->Invalidate();
        }
        
        void SetFont(Font *font)
        {
            if (font)
            {
                mFont = font;
                mFontKey = 0;
            }
            else
            {
                mFont = FontManager::GetDefaultFont();
            }
           
            this->Invalidate();
        }
        
        void SetTextColor(float r, float g, float b, float a)
        {
            mTextColor.r = r;
            mTextColor.g = g;
            mTextColor.b = b;
            mTextColor.a = a;
        }
        
        void SetTextColor(const Vector4f &color)
        {
            this->SetTextColor(color.r, color.g, color.b, color.a);
        }
        
        void SetTextOutlineColor(real r, real g, real b, real a)
        {
            mTextOutlineColor.r = r;
            mTextOutlineColor.g = g;
            mTextOutlineColor.b = b;
            mTextOutlineColor.a = a;
        }
        
        void SetTextOutlineSize(byte outline)
        {
            mOutlineSize = outline;
            this->Invalidate();
        }
        
        void SetTextOutlineColor(const Vector4f &color)
        {
            mTextOutlineColor = color;
        }
        
        void SetLineSpacing(double space)
        {
            mLineSpacing = space;
            this->Invalidate();
        }
        
        void SetAlpha(float alpha)
        {
            mAlpha = alpha;
        }
        
        void SetPosition(real x, real y)
        {
            mPosition.x = x;
            mPosition.y = y;
        }
        
        void SetPosition(const Point& p)
        {
            mPosition.x = p.x;
            mPosition.y = p.y;
        }
        
        void SetSize(real width, real height)
        {
            mSize.width = width;
            mSize.height = height;
            this->Invalidate();
        }
        
        void SetSize(const Size& size)
        {
            mSize.width = size.width;
            mSize.height = size.height;
            this->Invalidate();
        }
        
        void SetScale(float scale)
        {
            mScale = scale;
        }
        
        float GetScale() const
        {
            return mScale;
        }
        
        static Size GetSize(const std::u16string& text, Font* font, int outlineSize, double lineHeight, double maxWidth, int maxLines);
        static Size GetHeuristicSize(const std::u16string& text, double heuristicCharWidth, double heuristicLineHeight, double maxLineWidth, int maxLines);
        static void DetermineTokenWidths(const std::u16string& text, double heuristicCharWidth, std::vector<double>& tokenWidths);
        
        void SetAlignment(TextAlignHorizontal horizontal, TextAlignVertical vertical)
        {
            this->SetHorizontalAlignment(horizontal);
            this->SetVerticalAlignment(vertical);
        }
        
        void SetHorizontalAlignment(TextAlignHorizontal horizontal)
        {
            mHorizontalAlignment = horizontal;
            mAnchorPoint.x = horizontal * 0.5f;
        }
        
        void SetVerticalAlignment(TextAlignVertical vertical)
        {
            mVerticalAlignment = vertical;
            mAnchorPoint.y = vertical * 0.5f;
        }
        
        void SetAngle(real angle)
        {
            if (mAngle != angle) {
                mAngle = angle;
                double radians = glm::radians(mAngle);
                mLabelOriginAndAngle.z = sin(radians);
                mLabelOriginAndAngle.w = cos(radians);
            }
        }
        
        void OnAtlasReset()
        {
            mAtlasValid = false;
            this->Invalidate();
        }
        
        Bounds GetLocalBounds()
        {
            Point min(-mTextSize.width * mAnchorPoint.x, -mTextSize.height * mAnchorPoint.y);
            Point max = min + Point(mTextSize.width, mTextSize.height);
            return Bounds(min / mFontScale, max / mFontScale);
        }
        
        Bounds GetBounds()
        {
            Bounds bounds = this->GetLocalBounds();
            bounds.Offset(Point(mPosition.x, mPosition.y));
            return bounds;
        }
        
        float GetAlpha()
        {
            return mAlpha;
        }
        
        bool IsCutOff()
        {
            return mHasCutOff;
        }
        
        int GetNumberOfLines()
        {
            return mNumLines;
        }
        
        Size GetSize()
        {
            return Size(mTextSize.width / mFontScale, mTextSize.height / mFontScale);
        }
        
        double Width()
        {
            return mTextSize.width / mFontScale;
        }
        
        double Height()
        {
            return mTextSize.height / mFontScale;
        }
        
        void Draw(IGraphicsDevice *device, RenderState &state, PrimitiveType primitiveType = PrimitiveTypeTriangleList);
        
    private:
        
        static GlyphAtlasTexture* msAtlasTexture;
        
		std::wstring mText;
        Font *mFont;
        Vector4f mTextColor;
        Vector4f mTextOutlineColor;
        byte mOutlineSize;
        uint64_t mFontKey;
        
        Vector2f mPosition;
        float mAlpha;
        float mScale;
        double mLineSpacing;
        double mFontScale;
        bool mHasCutOff;
        bool mAtlasValid;
        int mNumLines;
        Size mSize;
        Size mScaledSize;
        Size mTextSize;
        real mAngle;
        Vector2f mAnchorPoint;
        Vector4f mLabelOriginAndAngle;
        TextAlignHorizontal mHorizontalAlignment;
        TextAlignVertical mVerticalAlignment;
        std::vector<double> mLineWidths;
        MeshShape *mOutlineShape;
        
        int mLabelOriginAndAngleUniform;
        int mLineOffsetUniform;
        int mGlyphAtlasUniform;
        int mPositionUniform;
        int mAlphaUniform;
        int mScaleUniform;
        int mColorUniform;
        
        void AddGlyphToVertices(std::vector<LabelVertex>& vertices, const Point& cursor, const GlyphData& data, int line);
        
        double DetermineLineStart(double lineWidth);
        
        /**
         * This function will populate glyphs with data from the atlas of this label.
         * The value of atlasChanged will signify whether or not the atlas did not previously contain one of the glyphs
         * in this label.
         * Return - Whether or not the atlas was able to add all of the requested glyphs to the atlas.
         */
        bool RetrieveGlyphData(std::vector<GlyphData>& glyphs, bool* atlasChanged, unsigned short outlineSize);
        
        static void DetermineTokenWidths(Font* font, int outlineSize, const std::u16string& text, std::vector<double>& tokenWidths);
        static void DetermineTokenWidths(const std::vector<GlyphData>& glyphs, std::vector<double>& tokenWidths);
        
        // Returns true if the text was cut off
        static bool DetermineLineAttributes(const std::vector<double>& tokenWidths, int maxLines, double maxWidth, double spaceWidth, std::vector<double>& lineWidths, std::vector<int>& tokensOnLine);
    };
};
