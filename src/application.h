//
// Created by David Sullivan on 4/13/22.
//

#ifndef GRACEFULTOOLING_APPLICATION_H
#define GRACEFULTOOLING_APPLICATION_H

#include "imgui.h"
#include "imgui-SFML.h"
#include "graph_lite.h"

#include "color_definitions.h"
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/Font.hpp>

using graph_lite::Graph;

//this will become where the state for the application is held, but for now it just
//factors out the gui drawing code.
class Application {
public:
    Application();
    void display(sf::RenderWindow* window);
    void reset_vertex_count(int count);
    int get_vertex_count();
private:
    int m_vertex_count;
//    int mouse_x;
//    int mouse_y;
    float m_graph_radius;
    float m_vertex_radius;

    sf::Font m_vertex_font;

    //an undirected graph with vertices with ints identifying vertices, a bool to denote if it
    //is currently selected, and edges labeled with ints as well.
    Graph<int, bool, int, graph_lite::EdgeDirection::UNDIRECTED> m_graph;

    void gui();
    void draw_graph(sf::RenderWindow* window);
};



#endif //GRACEFULTOOLING_APPLICATION_H
