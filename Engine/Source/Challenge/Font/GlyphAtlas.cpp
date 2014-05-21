#include <Challenge/Challenge.h>
#include <Challenge/Font/GlyphAtlas.h>
#include <Challenge/Font/Font.h>

namespace challenge
{
	GlyphAtlas::GlyphAtlas(const Size& size) :
        mSize(size),
        mNumAtlases(1),
        mShelfHeight(0),
        mCursor(kBaseOffset)
	{
		mDataSize = size.width * size.height;
		mData.resize(mDataSize);
		memset(&mData[0], 0, sizeof(FontTexel) * mDataSize);
	}
    
	GlyphAtlas::~GlyphAtlas()
	{
	}
    
	void GlyphAtlas::AddGlyph(Font* font, int character, unsigned short outlineSize)
	{
        uint64_t key = this->GenerateKey(font, character, outlineSize);
        
        if (mGlyphs.count(key)) {
            return;
        }
        if (!font)
        {
            return;
        }
        
        Glyph *glyph = font->GetGlyph(character, outlineSize);
        if (!glyph) {
            Logger::Log(LogWarning, "MISSING CHARACTER: %d\n", character);
            return;
        }
        
		double advance = glyph->GetAdvance().x;
        Point bearing = glyph->GetBearing();
		
        int width = glyph->GetDataSize().width;
        int height = glyph->GetDataSize().height;
        
		if(mCursor.x + width + kBaseOffset.x > mSize.width)
        {
			mCursor.y += mShelfHeight;
            int maxCharHeight = font->GetMaxCharHeight();
			if(mCursor.y + maxCharHeight > (mSize.height * mNumAtlases))
            {
                this->Empty();
			}
			mShelfHeight = 0;
			mCursor.x = kBaseOffset.x;
		}
        
        Point startPoint(mCursor.x, mCursor.y);
        Point offset = mCursor;
        
        glyph->RenderToBuffer(&mData[0], mSize, offset, font->GetMaxCharHeight(), NULL);
        
        mCursor.x += width + kBaseOffset.x;
        Point endPoint(startPoint.x + width, startPoint.y + height);
        
        GlyphData data;

		data.minCoordinate.x = (startPoint.x) / mSize.width;
		data.minCoordinate.y = (startPoint.y) / mSize.height;
		data.maxCoordinate.x = (endPoint.x) / mSize.width;
		data.maxCoordinate.y = (endPoint.y) / mSize.height;
        
		data.page = mNumAtlases;
        
        data.size.x = width;
        data.size.y = height;
        
        data.dataPosition = Vector2i(startPoint.x, startPoint.y);
        data.dataSize = Vector2i(width, height);
        
        // Horizontal advance is probably not linear based on font size.
        data.advance = advance;
        data.bearing = Vector2f(bearing.x, bearing.y);
        
        data.maxHeight = font->GetMaxCharHeight();
        
        data.character = character;
        mGlyphs[key] = data;
        
		if(height > mShelfHeight)
        {
            mShelfHeight = height;
        }
        
        mLastUpdated = Util::GetSystemTime();
        this->Invalidate();
	}
    
	const GlyphData GlyphAtlas::GetCoordinates(Font* font, int character, unsigned short outlineSize)
	{
        uint64_t key = this->GenerateKey(font, character, outlineSize);
        
		if(!mGlyphs.count(key))
        {
			this->AddGlyph(font, character, outlineSize);
		}
        
		GlyphData entry = mGlyphs[key];
        
		float ratio = (float)entry.page / (float)mNumAtlases;
		
		entry.minCoordinate.y *= ratio;
		entry.maxCoordinate.y *= ratio;
        
		return entry;
	}
    
    void GlyphAtlas::Empty()
    {
        mData.clear();
        mData.resize(mDataSize);
        mCursor = kBaseOffset;
        mGlyphs.clear();
        mShelfHeight = 0;
        
        std::lock_guard<TAtlasListenerSet> lock(mListeners);
        for(auto listener : mListeners)
        {
            listener->OnAtlasReset();
        }
    }
    
    uint64_t GlyphAtlas::GenerateKey(Font* font, int character, unsigned short outlineSize)
    {
        unsigned short fontId = font->GetFontId();
        uint64_t key = fontId;
        key <<= 16;
        key |= outlineSize;
        key <<= 32;
        key |= character;
        return key;
    }
    
    void GlyphAtlas::AddListener(IGlyphAtlasListener* listener)
    {
        std::lock_guard<TAtlasListenerSet> lock(mListeners);
        mListeners.insert(listener);
    }
    
    void GlyphAtlas::RemoveListener(IGlyphAtlasListener* listener)
    {
        std::lock_guard<TAtlasListenerSet> lock(mListeners);
        mListeners.erase(listener);
    }
    
};