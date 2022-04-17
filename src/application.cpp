//
// Created by David Sullivan on 4/13/22.
//

#include "application.h"
#include "color_definitions.h"

#include <math.h>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/CircleShape.hpp>

#include <iostream>

Application::Application():
    m_graph(), m_vertex_count(0),
    m_graph_radius(400), m_vertex_radius(45)
    {}

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
    ImGui::Text("Appearance");
    ImGui::SliderFloat("Graph Radius", &m_graph_radius, 100.f, 550.f);
    ImGui::SliderFloat("Vertex Radius", &m_vertex_radius, 15.f, 90.f);

    ImGui::Text("Graph Settings");

    int updatedVertexCount = m_vertex_count;
    if(ImGui::InputInt("Vertex Count", &updatedVertexCount)){
        this->reset_vertex_count(updatedVertexCount);
    }
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

    float angle_increment = 2.0 * M_PI / float(m_vertex_count);
    for(int i = 0; i < m_vertex_count; i++) {
        //the -pi/2 makes it so the 0'th vertex is always at the top of the cirlce
        float angle = (i * angle_increment) - M_PI_2;
        float vertex_center_x = (cos(angle) * m_graph_radius) + window_center_x;
        float vertex_center_y = (sin(angle) * m_graph_radius) + window_center_y;

        sf::CircleShape vertex = sf::CircleShape(m_vertex_radius);
        vertex.setOrigin(m_vertex_radius/2.0, m_vertex_radius/2.0);


        vertex.setPosition(vertex_center_x, vertex_center_y);
        vertex.setFillColor(app_colors::VERTEX);
        window->draw(vertex);
    }

}