//
// Created by David Sullivan on 4/17/22.
//

#ifndef GRACEFULTOOLING_PLATFORM_CONFIGURATION_H
#define GRACEFULTOOLING_PLATFORM_CONFIGURATION_H

#include <string>


#ifdef __APPLE__
    const std::string SYSTEM_FONT_PATH("/Library/Fonts/");
    const std::string ARIAL_FONT_PATH(SYSTEM_FONT_PATH + "Arial Unicode.ttf");
//#elifdef __WIN32__
//    const std::string SYSTEM_FONT_PATH("C:\\Windows\\Fonts");
//    const std::string ARIAL_FONT_PATH(SYSTEM_FONT_PATH + "Arial\\ Unicode.ttf");
//    assert(false, "missing definitions");
#endif

#endif //GRACEFULTOOLING_PLATFORM_CONFIGURATION_H
