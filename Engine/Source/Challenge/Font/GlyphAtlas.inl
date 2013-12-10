namespace challenge
{
	template <typename CharType>
	GlyphAtlas<CharType>::GlyphAtlas(FONT_STRING_DESC<CharType> fontStringDesc, Font *font, Size size, TFontPassList passes) :
        mSize(size),
        mFont(font),
        mFontStringDesc(fontStringDesc),
        mNumAtlases(1),
        mShelfHeight(0),
        mCursor(kBaseOffset),
        mPasses(passes)
	{
		mDataSize = size.width * size.height;
		mData.resize(mDataSize);
		memset(&mData[0], 0, sizeof(FontTexel) * mDataSize);
	}
    
	template <typename CharType>
	GlyphAtlas<CharType>::~GlyphAtlas()
	{
	}

	template <typename CharType>
	void GlyphAtlas<CharType>::AddGlyph(int character)
	{
        if (mGlyphs.count(character)) {
            return;
        }
        
        Glyph *glyph = mFont->GetGlyphForPass(mPasses[0], character);
        if (!glyph) {
            printf("MISSING CHARACTER: %d\n", character);
            return;
        }
        
		Point offset;

		int advance = 0;
        Point bearing;
		for(int p = 0; p < mPasses.size(); p++) {
			FontPass pass = mPasses[p];
			glyph = mFont->GetGlyphForPass(pass, character);

			int glyphAdvance = glyph->GetAdvance().x + pass.x;
			if(advance < glyphAdvance) {
				advance = glyphAdvance;
			}
            
            bearing = glyph->GetBearing();
		}
		
		if(mCursor.x + advance + kBaseOffset.x > mSize.width) {

			mCursor.y += mShelfHeight;
			if(mCursor.y + mFont->GetMaxCharHeight() > (mSize.height * mNumAtlases)) {
				std::vector<FontTexel> newData(mData.size() + mDataSize);
				std::copy(mData.begin(), mData.end(), newData.begin());
				mData = newData;
				mCursor.y = mNumAtlases * mSize.height + kBaseOffset.y;
				mNumAtlases++;
			}
			mShelfHeight = 0;
			mCursor.x = kBaseOffset.x;
		}

		int height = mFont->GetMaxCharHeight();
        
        Point startPoint(mCursor.x, mCursor.y);
        
        int width = 0;
        //int bearing = 0;
        
		for(int p = 0; p < mPasses.size(); p++) {
			FontPass pass = mPasses[p];

			glyph = mFont->GetGlyphForPass(pass, character);
            const Size &glyphSize = glyph->GetSize();

			offset.x = mCursor.x + pass.x;
			offset.y = mCursor.y + pass.y;

			FontColor color = mFontStringDesc.TextColor;
			if(pass.type == FontPassOutline) {
				color = mFontStringDesc.OutlineColor;
			}
            //printf("Pass: %d, Color: %f, %f, %f, %f\n", pass.type, color[0], color[1], color[2], color[3]);
			glyph->RenderToBuffer(color, &mData[0], mSize, offset, mFont->GetMaxCharHeight(), NULL);
            
            if(glyphSize.width + pass.x > width) {
				width = glyphSize.width + pass.x;
			}
            if(glyphSize.height + offset.y > height) {
				height = glyphSize.height + offset.y;
			}
		}

		//printf("%d\n", width);
        
        mCursor.x += advance + kBaseOffset.x;
        Point endPoint(startPoint.x + width, startPoint.y + height);
        
        GlyphData data;
		data.minCoordinate.x = (float)startPoint.x / (float)mSize.width;
		data.minCoordinate.y = (float)startPoint.y / (float)mSize.height;
        
		data.maxCoordinate.x = (float)endPoint.x / (float)mSize.width;
		data.maxCoordinate.y = (float)endPoint.y / (float)mSize.height;
        
		data.page = mNumAtlases;
        
        data.size.width = width;
        data.size.height = height;
        
        data.advance = advance;
        data.bearing = bearing;
        data.maxHeight = mFont->GetMaxCharHeight();
        
        mGlyphs[character] = data;

		if(height > mShelfHeight) {
            mShelfHeight = height;
        }
        
        mLastUpdated = time(NULL);
	}

	template <typename CharType>
	const GlyphData GlyphAtlas<CharType>::GetCoordinates(int character)
	{
		if(!mGlyphs.count(character)) {
			this->AddGlyph(character);
		}

		GlyphData entry = mGlyphs[character];

		float ratio = (float)entry.page / (float)mNumAtlases;
		
		entry.minCoordinate.y *= ratio;
		entry.maxCoordinate.y *= ratio;

		return entry;
	}
    
    template <typename CharType>
    long GlyphAtlas<CharType>::GetKerning(int leftChar, int rightChar)
    {
        return mFont->GetKerning(leftChar, rightChar);
    }
    
    template <typename CharType>
    void GlyphAtlas<CharType>::Empty()
    {
        mData.clear();
        mData.resize(mDataSize);
        mCursor = kBaseOffset;
        mGlyphs.clear();
        mShelfHeight = 0;
    }
}