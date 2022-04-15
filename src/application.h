//
// Created by David Sullivan on 4/13/22.
//

#ifndef GRACEFULTOOLING_APPLICATION_H
#define GRACEFULTOOLING_APPLICATION_H

#include "imgui.h"
#include "imgui-SFML.h"

//this will become where the state for the application is held, but for now it just
//factors out the gui drawing code.
class Application {
public:
    //theses fields will 100% be replaced
    float m_color[3];
    char windowTitle[256];

    Application();
    void display(sf::RenderWindow& window);
    sf::Color colorAsSFColor();
private:
};


#endif //GRACEFULTOOLING_APPLICATION_H
