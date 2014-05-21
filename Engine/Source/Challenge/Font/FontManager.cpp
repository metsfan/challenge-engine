#include <Challenge/Challenge.h>
#include <rapidxml/rapidxml.hpp>

#include <Challenge/Font/FontManager.h>
#include <Challenge/Disk/Asset.h>
#include <Challenge/Font/FontConfig.h>

namespace challenge
{
    const std::string FontManager::kSystemFont = "_system";
    const int FontManager::kDefaultFontSize = 13;
    
    TFontMap FontManager::mFonts;
    TFontDescMap FontManager::mConfigFonts;
    
    Font* FontManager::AddFont(FONT_DESC &fontDesc)
    {
        Font *newFont = new Font(fontDesc);
        mFonts[fontDesc.GetKey()] = newFont;
        return newFont;
    }
    
    Font* FontManager::GetFont(FONT_DESC &fontDesc)
    {
        Font *font;
        uint64_t key = fontDesc.GetKey();
        if(!mFonts.count(key))
        {
            font = AddFont(fontDesc);
        } else
        {
            font = mFonts[key];
        }
        return font;
    }
    
    Font* FontManager::GetFont(const std::string &name, int size)
    {
        bool systemFont = false;
        
        FONT_DESC desc;
        if (name.size() > 0 && name != kSystemFont && mConfigFonts.count(name))
        {
            desc = mConfigFonts[name];
            desc.FontFamily = name;
        } else {
            desc = mConfigFonts[kSystemFont];
            systemFont = true;
        }

        desc.FontSize = size;
        
        Font *font = FontManager::GetFont(desc);
        
        if (!systemFont)
        {
            font->SetBackupFont(FontManager::GetFont(kSystemFont, size));
        }
        
        return font;
    }
    
    Font*  FontManager::GetDefaultFont()
    {
        return FontManager::GetFont(kSystemFont, kDefaultFontSize);
    }
    
    void FontManager::LoadSystemFont(const std::string &name)
    {
        if (!mConfigFonts.count(kSystemFont)) {
            FontManager::CopySystemFonts(name);
            
            std::string filename = "system_font_" + name + ".xml";
            FontManager::LoadFontConfig(filename);
        }
    }
    
    void FontManager::CopySystemFonts(const std::string &name)
    {
        /*std::string filename = "system_font_files_" + name + ".xml";
        Resource file(filename);
        const TByteArray &data = file.Data();
        
        rapidxml::xml_document<> doc;
        doc.parse<0>((char *)&data[0]);
        
        rapidxml::xml_node<> *rootNode = doc.first_node("FontFiles");
        rapidxml::xml_node<> *fileNode = rootNode->first_node("File");
        
        std::vector<SystemFontFile> files;
        while (fileNode) {
            SystemFontFile file;
            std::string name = fileNode->first_attribute("name")->value();
            file.name = name;
            
            rapidxml::xml_attribute<> *outFileAttr = fileNode->first_attribute("outfile");
            if (outFileAttr) {
                file.outfile = outFileAttr->value();
            } else {
                file.outfile = name;
            }
            file.outfile += ".ttf";
            
            files.push_back(file);
            
            fileNode = fileNode->next_sibling();
        }
        
        SystemFontReader<CurrentPlatform>::CopyFonts(files);*/
    }
    
    void FontManager::LoadFontConfig(const std::string &filename)
    {
        TFontDescMap newFonts = FontConfig::ReadResource(filename);
        mConfigFonts.insert(newFonts.begin(), newFonts.end());
    }
}

