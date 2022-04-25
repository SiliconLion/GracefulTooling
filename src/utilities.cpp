//
// Created by David Sullivan on 4/19/22.
//

#include "utilities.h"
#include <imgui.h>
#include <SFML/Graphics/RenderWindow.hpp>

sf::Color from_ImVec4(ImVec4 imColor){
    return sf::Color(
            sf::Uint8(imColor.x * 255.f),
            sf::Uint8(imColor.y * 255.f),
            sf::Uint8(imColor.z * 255.f),
            sf::Uint8(imColor.w * 255.f)
            );
}

sf::Color from_float3(float fColor[3] ){
    return sf::Color(
            sf::Uint8(fColor[0] * 255.f),
            sf::Uint8(fColor[1] * 255.f),
            sf::Uint8(fColor[2] * 255.f),
            255
            );
}

sf::Color from_float4(float fColor[4] ){
    auto c = sf::Color(
            sf::Uint8(fColor[0] * 255.f),
            sf::Uint8(fColor[1] * 255.f),
            sf::Uint8(fColor[2] * 255.f),
            sf::Uint8(fColor[3] * 255.f)
    );
}

ImVec4 fromSFColor(sf::Color sColor){
    return ImVec4(
            float(sColor.r) / 255.f,
            float(sColor.g) / 255.f,
            float(sColor.b) / 255.f,
            float(sColor.a) / 255.f
            );
}