#pragma once

#include <set>

#include <Challenge/Challenge.h>
#include <Challenge/Font/Glyph.h>
#include <Challenge/Font/Types.h>
#include <Challenge/Util/SafeObject.hpp>

namespace challenge
{
	class Font;

	struct GlyphData
	{
		Vector2 minCoordinate;
		Vector2 maxCoordinate;
        
        Vector2i dataPosition;
        Vector2i dataSize;
        
        Vector2i size;
		int page;
        double advance;
        Vector2f bearing;
        int maxHeight;
        int character;
	};

	typedef std::map<uint64_t, GlyphData> TGlyphEntryMap;
    
    static const Point kBaseOffset(3, 2);

    class IGlyphAtlasListener
    {
    public:
        
        virtual ~IGlyphAtlasListener(){}
        virtual void OnAtlasReset() = 0;
    };
    
    /** This class will become invalid whenever a glyph has been added that was previously not in the atlas.
     *
     * It must be validated externally once the user syncs the atlas's data with their own data
     **/
	class GlyphAtlas : public Validatable
	{
	public:
		GlyphAtlas(const Size& size);
		~GlyphAtlas();

		void AddGlyph(Font* font, int character, unsigned short outlineSize = 0);
        bool ContainsGlyph(Font* font, int character, unsigned short outlineSize = 0) { return mGlyphs.count(this->GenerateKey(font, character, outlineSize)); }
		const void* GetData() { return static_cast<void *>( mData.empty() ? NULL : &mData[0]); }
		const Size& GetSize() const { return mSize; }
		const int GetNumAtlases() { return mNumAtlases; }
		const GlyphData GetCoordinates(Font* font, int character, unsigned short outlineSize = 0);
        bool UpdatedAfter(long time) { return mLastUpdated > time; }
        float GetUsage() { return (float)mCursor.y / (float)mSize.height; }
        void Empty();
        void AddListener(IGlyphAtlasListener* listener);
        void RemoveListener(IGlyphAtlasListener* listener);
        double GetScale(){return 2.0;}
        void Validate() { Validatable::Validate();}

        uint64_t GenerateKey(Font* font, int character, unsigned short outlineSize = 0);
    private:
        
        typedef SafeObject<std::set<IGlyphAtlasListener*> > TAtlasListenerSet;
        
	private:
		std::vector<FontTexel> mData;
		int mDataSize;
		int mShelfHeight;
		Size mSize;
		int mTexWidth;
		Point mCursor;
		int mNumAtlases;
		TGlyphEntryMap mGlyphs;
        long mLastUpdated;
        TAtlasListenerSet mListeners;
	};
}