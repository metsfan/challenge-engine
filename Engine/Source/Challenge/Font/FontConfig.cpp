//
//  FontConfig.cpp
//  vectormap
//
//  Created by Adam Eskreis on 5/20/13.
//  Copyright (c) 2013 Adam Eskreis. All rights reserved.
//
#include <Challenge/Challenge.h>

#include <rapidxml/rapidxml.hpp>

#include <Challenge/Font/FontConfig.h>
#include <Challenge/Disk/File.h>
#include <Challenge/Disk/Asset.h>

namespace challenge
{
    TFontDescMap FontConfig::ReadResource(const std::string &filename)
    {
        TFontDescMap fonts;
        
        Asset resource(filename);
        if(resource.ReadData())
        {
            TByteArray data = resource.GetData();
			data.push_back('\0');
            
            rapidxml::xml_document<> doc;
            doc.parse<0>((char *)&data[0]);
            
            rapidxml::xml_node<> *rootNode = doc.first_node("Fonts");
            if (!rootNode) {
                //throw Exception(BadParameterException, "Missing \"Fonts\" Element", "All font configurations must contains a root element called \"Fonts\"");
            }
            
            rapidxml::xml_node<> *fontNode = rootNode->first_node("Font");
            while (fontNode)
            {
                rapidxml::xml_attribute<> *nameAttr = fontNode->first_attribute("name");
                if (!nameAttr) {
                    //throw Exception(BadParameterException, "Missing Font Name", "All Font configurations must contain a \"name\" attribute");
                }
                
                std::string name(nameAttr->value());
                FONT_DESC& desc = fonts[name];
                
                rapidxml::xml_attribute<> *hintingAttr = fontNode->first_attribute("hinting");
                bool hinting = false;
                
                if (hintingAttr) {
                    hinting = atoi(hintingAttr->value());
                }
                
                desc.HintingEnabled = hinting;
                
                rapidxml::xml_node<> *fontFileNode = fontNode->first_node("FontFile");
                while (fontFileNode)
                {
                    rapidxml::xml_attribute<> *fileNameAttr = fontFileNode->first_attribute("filename");
                    if (!fileNameAttr) {
                        //throw Exception(BadParameterException, "Missing Font Filename", "All FontFile configurations must contain a \"filename\" attribute");
                    }
                    
                    std::string filename(fileNameAttr->value());
                    FontFile file(filename);
                    
                    rapidxml::xml_node<> *rangeNode = fontFileNode->first_node("Range");
                    while (rangeNode) {
                        rapidxml::xml_attribute<> *rangeNameAttr = rangeNode->first_attribute("name");
                        if (!rangeNameAttr) {
                            //throw Exception(BadParameterException, "Missing Range Name", "All Range configurations must contain a \"name\" attribute");
                        }
                        file.AddRange(FontConfig::GetRangeForName(rangeNameAttr->value()));
                        
                        rangeNode = rangeNode->next_sibling();
                    }
                    
                    desc.Files.push_back(file);
                    
                    fontFileNode = fontFileNode->next_sibling();
                }

                fontNode = fontNode->next_sibling();
            }
        }
        
        return fonts;
    }
    
    
    Range FontConfig::GetRangeForName(const std::string &name)
    {
        if (name.compare("latin") == 0) {
            return LATIN_RANGE;
        } else if(name.compare("latin1-supplement") == 0) {
            return LATIN1_SUPPLEMENT_RANGE;
        } else if(name.compare("latin-extended-a") == 0) {
            return LATIN_EXTENDED_A_RANGE;
        } else if(name.compare("latin-extended-b") == 0) {
            return LATIN_EXTENDED_B_RANGE;
        } else if(name.compare("ipa-extensions") == 0) {
            return IPA_EXTENSIONS_RANGE;
        } else if(name.compare("spacing-modified-letters") == 0) {
            return SPACING_MODIFIED_LETTERS_RANGE;
        } else if(name.compare("combining-diacritical-marks") == 0) {
            return COMBINING_DIACRITICAL_MARKS_RANGE;
        } else if(name.compare("greek-coptic") == 0) {
            return GREEK_COPTIC_RANGE;
        } else if(name.compare("cyrillic") == 0) {
            return CRYILLIC_RANGE;
        } else if(name.compare("cyrillic-supplement") == 0) {
            return CRYILLIC_SUPPLEMENT_RANGE;
        } else if(name.compare("armenian") == 0) {
            return ARMENIAN_RANGE;
        } else if(name.compare("hebrew") == 0) {
            return HEBREW_RANGE;
        } else if(name.compare("arabic") == 0) {
            return ARABIC_RANGE;
        } else if(name.compare("arabic-supplement") == 0) {
            return ARABIC_SUPPLEMENT_RANGE;
        } else if(name.compare("bengali") == 0) {
            return BENGALI_RANGE;
        } else if(name.compare("gurmukhi") == 0) {
            return GURMUKHI_RANGE;
        } else if(name.compare("gujarati") == 0) {
            return GUJARATI_RANGE;
        } else if(name.compare("oriya") == 0) {
            return ORIYA_RANGE;
        } else if(name.compare("tamil") == 0) {
            return TAMIL_RANGE;
        } else if(name.compare("telugu") == 0) {
            return TELUGU_RANGE;
        } else if(name.compare("kannada") == 0) {
            return KANNADA_RANGE;
        } else if(name.compare("malayalam") == 0) {
            return MALAYALAM_RANGE;
        } else if(name.compare("sinhala") == 0) {
            return SINHALA_RANGE;
        } else if(name.compare("thai") == 0) {
            return THAI_RANGE;
        } else if(name.compare("lao") == 0) {
            return LAO_RANGE;
        } else if(name.compare("tibetan") == 0) {
            return TIBETAN_RANGE;
        } else if(name.compare("myanmar") == 0) {
            return MYANMAR_RANGE;
        } else if(name.compare("hangul-jamo") == 0) {
            return HANGUL_JAMO_RANGE;
        } else if(name.compare("georgian") == 0) {
            return GEORGIAN_RANGE;
        } else if(name.compare("mongolian") == 0) {
            return MONGOLIAN_RANGE;
        } else if(name.compare("latin-extended-additional") == 0) {
            return LATIN_EXTENDED_ADDITIONAL_RANGE;
        } else if(name.compare("greek-extended-range") == 0) {
            return GREEK_EXTENDED_RANGE;
        } else if(name.compare("general-punctuation") == 0) {
            return GENERAL_PUNCTUATION_RANGE;
        } else if(name.compare("cjk-radicals-supplement-range") == 0) {
            return CJK_RADICALS_SUPPLEMENT_RANGE;
        } else if(name.compare("kangxi-radicals") == 0) {
            return KANGXI_RADICALS_RANGE;
        } else if(name.compare("cjk-symbols-and-punctuation") == 0) {
            return CJK_SYMBOLS_AND_PUNCTUATION_RANGE;
        } else if(name.compare("hiragana") == 0) {
            return HIRAGANA_RANGE;
        } else if(name.compare("katakana") == 0) {
            return KATAKANA_RANGE;
        } else if(name.compare("bopomofo") == 0) {
            return BOPOMOFO_RANGE;
        } else if(name.compare("hangul-compatibility-jamo") == 0) {
            return HANGUL_COMPATIBILITY_JAMO_RANGE;
        } else if(name.compare("cjk-unified-ideographs-extension-a") == 0) {
            return CJK_UNIFIED_IDEOGRAPHS_EXTENSION_A_RANGE;
        } else if(name.compare("cjk-unified-ideographs") == 0) {
            return CJK_UNIFIED_IDEOGRAPHS_RANGE;
        } else if(name.compare("yi-syllables") == 0) {
            return YI_SYLLABLES_RANGE;
        } else if(name.compare("yi-radicals") == 0) {
            return YI_RADICALS_RANGE;
        } else if(name.compare("hangul-syllables") == 0) {
            return HANGUL_SYLLABLES_RANGE;
        } else if(name.compare("cjk-compatibility-ideographs") == 0) {
            return CJK_COMPATIBILITY_IDEOGRAPHS_RANGE;
        } else if(name.compare("arabic-presentation-forms-a") == 0) {
            return ARABIC_PRESENTATION_FORMS_A_RANGE;
        } else if(name.compare("arabic-presentation-forms-b") == 0) {
            return ARABIC_PRESENTATION_FORMS_B_RANGE;
        } else if(name.compare("cjk-unified-ideographs-extension-b") == 0) {
            return CJK_UNIFIED_IDEOGRAPHS_EXTENSION_B_RANGE;
        } else if(name.compare("halfwidth-and-fullwidth-forms") == 0) {
            return HALFWIDTH_AND_FULLWIDTH_FORMS_RANGE;
        } else if(name.compare("non-latin") == 0) {
            return NON_LATIN_RANGE;
        } else if(name.compare("ascii") == 0) {
            return ASCII_RANGE;
        } else if(name.compare("fallback") == 0) {
            return FALLBACK_RANGE;
        }
        
        return LATIN_RANGE;
    }
};
