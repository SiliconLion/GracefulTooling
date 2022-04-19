//
// Created by David Sullivan on 4/16/22.
//

#ifndef GRACEFULTOOLING_COLOR_DEFINITIONS_H
#define GRACEFULTOOLING_COLOR_DEFINITIONS_H

#include <SFML/Graphics/RenderWindow.hpp>

namespace app_colors {

    //ToDo: all of these come from sRGB colors, and sf::Color uses RGB. Looks wrong.

    //a plain very dark purple
    const auto BACKGROUND_1 = sf::Color(42, 9, 68);
    //slightly less dark purple
    const auto BACKGROUND_2 = sf::Color(59, 24, 95);
    //low saturation pink
    const auto VERTEX_1 = sf::Color(161, 37, 104);
    //low saturation yellow
    const auto VERTEX_TEXT = sf::Color(254, 194, 96);
    //same as VERTEX_TEXT for now
    const auto VERTEX_HIGHLIGHT_1 = sf::Color(254, 194, 96);
    const auto VERTEX_HIGHLIGHT_2 = sf::Color(255, 223, 129);
    //low saturation mint green
    const auto EDGE_1 = sf::Color(40, 90, 70);

    const auto EDGE_TEXT = sf::Color(254, 230, 215);

    const auto DEBUG_1 = sf::Color(255, 0, 0);
    const auto DEBUG_2 = sf::Color(0, 255, 0);
    const auto DEBUG_3 = sf::Color(0, 0, 255);
}




#endif //GRACEFULTOOLING_COLOR_DEFINITIONS_H
