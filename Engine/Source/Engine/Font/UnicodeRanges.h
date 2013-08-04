//
//  UnicodeRanges.h
//  vectormap
//
//  Created by Adam Eskreis on 5/20/13.
//  Copyright (c) 2013 Adam Eskreis. All rights reserved.
//

#pragma once

#include <Engine/Font/FontTypes.h>

namespace challenge
{
    static const Range LATIN_RANGE(0x0000, 0x007F);
    static const Range LATIN1_SUPPLEMENT_RANGE(0x0080, 0x00FF);
    static const Range LATIN_EXTENDED_A_RANGE(0x0100, 0x017F);
    static const Range LATIN_EXTENDED_B_RANGE(0x0180, 0x024F);
    static const Range IPA_EXTENSIONS_RANGE(0x0250, 0x02AF);
    static const Range SPACING_MODIFIED_LETTERS_RANGE(0x02B0, 0x02FF);
    static const Range COMBINING_DIACRITICAL_MARKS_RANGE(0x0300, 0x036F);
    static const Range GREEK_COPTIC_RANGE(0x0370, 0x03FF);
    static const Range CRYILLIC_RANGE(0x0400, 0x04FF);
    static const Range CRYILLIC_SUPPLEMENT_RANGE(0x0500, 0x052F);
    static const Range ARMENIAN_RANGE(0x0530, 0x058F);
    static const Range HEBREW_RANGE(0x0590, 0x05FF);
    static const Range ARABIC_RANGE(0x0600, 0x06FF);
    static const Range ARABIC_SUPPLEMENT_RANGE(0x0750, 0x077F);
    static const Range BENGALI_RANGE(0x0980, 0x09FF);
    static const Range GURMUKHI_RANGE(0x0A00, 0x0A7F);
    static const Range GUJARATI_RANGE(0xA80, 0x0AFF);
    static const Range ORIYA_RANGE(0x0B00, 0x0B7F);
    static const Range TAMIL_RANGE(0x0B80, 0x0BFF);
    static const Range TELUGU_RANGE(0x0C00, 0x0C7F);
    static const Range KANNADA_RANGE(0x0C80, 0x0CFF);
    static const Range MALAYALAM_RANGE(0x0D00, 0x0DFF);
    static const Range SINHALA_RANGE(0x0D80, 0x0DFF);
    static const Range THAI_RANGE(0x0E00, 0x0E7F);
    static const Range LAO_RANGE(0x0E80, 0x0EFF);
    static const Range TIBETAN_RANGE(0x0F00, 0x0FFF);
    static const Range MYANMAR_RANGE(0x1000, 0x109F);
    static const Range HANGUL_JAMO_RANGE(0x1100, 0x11FF);
    static const Range GEORGIAN_RANGE(0x10A0, 0x10FF);
    static const Range MONGOLIAN_RANGE(0x1800, 0x18AF);
    static const Range LATIN_EXTENDED_ADDITIONAL_RANGE(0x1E00, 0x1EFF);
    static const Range GREEK_EXTENDED_RANGE(0x1F00, 0x1FFF);
    static const Range GENERAL_PUNCTUATION_RANGE(0x2000, 0x206F);
    static const Range CJK_RADICALS_SUPPLEMENT_RANGE(0x2E80, 0x2EFF);
    static const Range KANGXI_RADICALS_RANGE(0x2F00, 0x2FDF);
    static const Range CJK_SYMBOLS_AND_PUNCTUATION_RANGE(0x3000, 0x303F);
    static const Range HIRAGANA_RANGE(0x3040, 0x309F);
    static const Range KATAKANA_RANGE(0x30A0, 0x30FF);
    static const Range BOPOMOFO_RANGE(0x3100, 0x312F);
    static const Range HANGUL_COMPATIBILITY_JAMO_RANGE(0x3130, 0x318F);
    static const Range CJK_UNIFIED_IDEOGRAPHS_EXTENSION_A_RANGE(0x3400, 0x4DBF);
    static const Range CJK_UNIFIED_IDEOGRAPHS_RANGE(0x4E00, 0x9FFF);
    static const Range YI_SYLLABLES_RANGE(0xA000, 0xA48F);
    static const Range YI_RADICALS_RANGE(0xA490, 0xA4CF);
    static const Range HANGUL_SYLLABLES_RANGE(0xAC00, 0xD7AF);
    static const Range CJK_COMPATIBILITY_IDEOGRAPHS_RANGE(0xF900, 0xFAFF);
    static const Range ARABIC_PRESENTATION_FORMS_A_RANGE(0xFB50, 0xFDFF);
    static const Range ARABIC_PRESENTATION_FORMS_B_RANGE(0xFE70, 0xFEFF);
    static const Range HALFWIDTH_AND_FULLWIDTH_FORMS_RANGE(0xFF00, 0xFFEF);
    static const Range CJK_UNIFIED_IDEOGRAPHS_EXTENSION_B_RANGE(0x20000, 0x2A6DF);
    //static const Range _RANGE(0x, 0x);
    
    static const Range NON_LATIN_RANGE(0x00A0, USHRT_MAX);
    
};

