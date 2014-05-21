#include <Challenge/Challenge.h>
#include <Challenge/Font/Font.h>
#include <Challenge/Font/FontManager.h>
#include <Challenge/Util/Util.h>
#include <Challenge/Disk/File.h>

namespace challenge
{
    FT_Library Font::sFTLibrary = NULL;
    static const std::string kTTFExtension = ".ttf";
    
    unsigned short Font::sUIDCounter = 0;
    SafeObject<std::map<std::string, std::shared_ptr<FontFace> > > Font::sFontFaces;
    
    Font::Font(FONT_DESC &fontDesc) :
        mFontDesc(fontDesc),
        mBackupFont(NULL)
    {
        mUID = sUIDCounter++;
        mScale = 2;//DeviceSpecification::GetDevicePixelDensity();
        
        FT_Error error;
        if(!sFTLibrary) {
            error = FT_Init_FreeType(&sFTLibrary);
            if (error) {
                //throw Exception(InternalException, "Font Freetype", "Freetype failed to initialize.");
            }
        }
        
        if (fontDesc.Files.size() == 0)
        {
           // FontFile defaultFile(File::GetCacheDirectory() + fontDesc.FontFamily + kTTFExtension);
           // fontDesc.Files.push_back(defaultFile);
        }
        
        sFontFaces.lock();
        
        for (int i = 0; i < fontDesc.Files.size(); i++)
        {
            auto cachedFace = sFontFaces.find(fontDesc.Files[i].filepath);
            if (cachedFace != sFontFaces.end())
            {
                mFaces.push_back(cachedFace->second);
            }
            else
            {
                std::ifstream ifile(fontDesc.Files[i].filepath);
                
                if(ifile.good())
                {
                    mFaces.push_back(std::make_shared<FontFace>(sFTLibrary, fontDesc.Files[i], fontDesc.FontSize * 2, fontDesc.HintingEnabled));
                    sFontFaces.insert(std::make_pair(fontDesc.Files[i].filepath, mFaces.back()));
                }
                else
                {
                    Logger::Log(LogError, "Failed to load font at path %s\n", fontDesc.Files[i].filepath.c_str());
                }
            }
        }
        
        sFontFaces.unlock();
    
        mSpaceGlyph = this->GetGlyph(' ');
    }
    
    Font::~Font()
    {
        sFontFaces.lock();
        
        for(auto& face : mFaces)
        {
            if (face.use_count() == 2)
            {
                // Only the static font face map and ourself use this face. remove it from the static map.
                sFontFaces.erase(face->GetFile().filepath);
            }
        }
        
        sFontFaces.unlock();
    }
    
    double Font::GetKerning(Glyph *leftGlyph, Glyph *rightGlyph)
    {
        if (leftGlyph && rightGlyph)
        {
            for(auto face : mFaces)
            {
                if (face->ContainsGlyph(leftGlyph->GetCharacter()))
                {
                    return face->GetKerning(leftGlyph, rightGlyph);
                }
            }
        }
        
        return 0;
    }
    
    double Font::GetKerning(int leftChar, int rightChar, int leftCharOutlineSize, int rightCharOutlineSize)
    {
        Glyph *leftGlyph = this->GetGlyph(leftChar, leftCharOutlineSize);
        Glyph *rightGlyph = this->GetGlyph(rightChar, rightCharOutlineSize);
        
        return this->GetKerning(leftGlyph, rightGlyph);
    }
    
    Glyph* Font::GetGlyph(int character, int outlineSize)
    {
        Glyph *glyph = NULL;
        Font *font = this;
        
        uint64_t key = this->GenerateKey(character, outlineSize);
        
        while (font)
        {
            TGlyphMap *map = &font->mGlyphs;
            
            if(map->find(key) == map->end())
            {
                for(auto face : font->mFaces)
                {
                    if (face->ContainsGlyph(character))
                    {
                        face->SetSize(mScale * mFontDesc.FontSize);
                        
                        glyph = new Glyph(sFTLibrary, *face, character, outlineSize, mFontDesc.HintingEnabled);
                        (*map)[key] = glyph;
                        if (glyph->mSize.y > mMaxHeight)
                        {
                            font->mMaxHeight = glyph->mSize.y;
                        }
                        break;
                    }
                }
            } else
            {
                glyph = (*map)[key];
            }
            
            if (glyph)
                break;
            
            if (font == this && mBackupFont != font)
            {
                font = mBackupFont;
            } else {
                font = NULL;
            }
        }
        return glyph;
    }

}
