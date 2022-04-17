//
// Created by David Sullivan on 4/13/22.
//

#include "application.h"
#include "color_definitions.h"

#include <math.h>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/CircleShape.hpp>

#include <iostream>

Application::Application(): m_graph(), m_vertex_count(0) {}

void Application::reset_vertex_count(int count) {
    m_vertex_count = count;
    m_graph = graph_lite::Graph<int, bool, int, graph_lite::EdgeDirection::UNDIRECTED>();
    for (int i = 0; i < count; i++) {
        m_graph.add_node_with_prop(i,false);
    }
}

void Application::display(sf::RenderWindow* window) {
    this->draw_graph(window);
    this->gui();
}

void Application::gui() {
    ImGui::Begin("Controls");
    ImGui::End();
}

void Application::draw_graph(sf::RenderWindow* window) {


    unsigned int window_width = window->getSize().x;
    unsigned int window_height = window->getSize().y;

    unsigned int window_center_x = window_width / 2;
    unsigned int window_center_y = window_height / 2;

    if (m_vertex_count <= 0) {
        std::cout << "returned" << std::endl;
        return;
    }

    float vertex_radius = 25.0;
    float graph_radius = 500;
    float angle_increment = 2.0 * M_PI / float(m_vertex_count);
    for(int i = 0; i < m_vertex_count; i++) {
        float angle = i * angle_increment;
        float vertex_center_x = (cos(angle) * graph_radius) + window_center_x;
        float vertex_center_y = (sin(angle) * graph_radius) + window_center_y;

        sf::CircleShape vertex = sf::CircleShape(vertex_radius);
        vertex.setOrigin(vertex_radius/2.0, vertex_radius/2.0);


        vertex.setPosition(vertex_center_x, vertex_center_y);
        vertex.setFillColor(app_colors::VERTEX);
        window->draw(vertex);
    }

}