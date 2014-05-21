//
//  SystemFontReader.h
//  MapEngineLibraryIOS
//
//  Created by Adam Eskreis on 8/27/13.
//  Copyright (c) 2013 Adam Eskreis. All rights reserved.
//

#pragma once

#include <Challenge/Challenge.h>

namespace challenge
{
    struct SystemFontFile
    {
        std::string name;
        std::string outfile;
    };
    
    template <typename Platform>
    class SystemFontReader
    {
    public:
        static void CopyFonts(const std::vector<SystemFontFile> &files) {}
    };
};
