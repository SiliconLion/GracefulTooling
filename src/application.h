//
// Created by David Sullivan on 4/13/22.
//

#ifndef GRACEFULTOOLING_APPLICATION_H
#define GRACEFULTOOLING_APPLICATION_H

#include "imgui.h"
#include "imgui-SFML.h"
#include "graph_lite.h"
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/Font.hpp>

#include <memory>



#include "color_definitions.h"
#include "gui_graph.h"

using graph_lite::Graph;

//Forward declaration of this class
class GuiState;

class GuiState {
public:
    int vertex_1 = 0;
    int vertex_2 = 0;
    int vertex_3 = 0;
    int vertex_4 = 0;
    int vertex_5 = 0;
    ImVec4 color1 = {
            float(app_colors::EDGE_1.r) / 255.f,
            float(app_colors::EDGE_1.g) / 255.f,
            float(app_colors::EDGE_1.b) / 255.f,
            1.0
    };
    GuiState(){};
} ;



//this will become where the state for the application is held, but for now it just
//factors out the gui drawing code.
class Application {
public:
    Application(int vertexCount=0);
    void display(sf::RenderWindow& window);
    void newGraphWithCount(int count);
    int get_vertex_count();
private:
    int m_vertex_count;
    float m_graph_radius;
    float m_vertex_radius;
    sf::Font m_vertex_font;

    GuiGraph m_graph;

    GuiState m_guiState;

    void gui();
    void draw_graph(sf::RenderWindow& window);
};









#endif //GRACEFULTOOLING_APPLICATION_H
