//
//  FontConfig.h
//  vectormap
//
//  Created by Adam Eskreis on 5/20/13.
//  Copyright (c) 2013 Adam Eskreis. All rights reserved.
//

#include <Challenge/Challenge.h>
#include <Challenge/Font/FontEngine.h>

namespace challenge
{
    class FontConfig
    {
    public:
        static TFontDescMap ReadResource(const std::string &resource);
        
    private:
        static Range GetRangeForName(const std::string &name);
    };
};

