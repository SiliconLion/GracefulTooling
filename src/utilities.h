//
// Created by David Sullivan on 4/19/22.
//

#include <SFML/Graphics/RenderWindow.hpp>
#include <imgui.h>

#ifndef GRACEFULTOOLING_UTILITIES_H
#define GRACEFULTOOLING_UTILITIES_H

sf::Color from_ImVec4(ImVec4 imColor);
sf::Color from_float3(float fColor[3] );
sf::Color from_float4(float fColor[4] );

ImVec4 fromSFColor(sf::Color sColor);




#endif //GRACEFULTOOLING_UTILITIES_H
