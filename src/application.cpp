//
// Created by David Sullivan on 4/13/22.
//

#include "application.h"
#include "color_definitions.h"
#include "platform_configuration.h"

#include <math.h>
#include <iostream>

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/Text.hpp>





Application::Application(int vertexCount):
    m_graph(vertexCount), m_vertex_count(vertexCount),
    m_graph_radius(400), m_vertex_radius(45), m_vertex_font()
    {
        if(!m_vertex_font.loadFromFile(ARIAL_FONT_PATH)) {
            std::cout << "error. cannot find font arial" << std::endl;
            exit(-1);
        }
    }

void Application::newGraphWithCount(int count) {
    m_vertex_count = count;
    GuiDrawSettings settings = m_graph.m_drawSettings;
    m_graph = GuiGraph(count, settings);
}

void Application::display(sf::RenderWindow& window) {
    this->draw_graph(window);
    this->gui();
}

void Application::gui() {
    ImGui::Begin("Controls");

    if(ImGui::CollapsingHeader("Editor")) {
        ImGui::Text("Add Connection");

        int vertex_1 = 0, vertex_2 = 0;
        auto inputFlags = ImGuiInputTextFlags_EnterReturnsTrue | ImGuiInputTextFlags_AlwaysInsertMode;
        ImGui::InputInt("@vertex_1", &vertex_1, inputFlags);
        ImGui::InputInt("@vertex_2", &vertex_2, inputFlags);
        if(ImGui::Button("Connect")){
            this->m_graph.addEdge(vertex_1, vertex_2);
        }
    }

    if(ImGui::CollapsingHeader("Appearance")) {
        //this may be slightly less than kosher, but its not actually bad from a lifetime perspective
        //as this is updated every frame.
        ImGui::SliderFloat("Graph Radius", &(m_graph.m_drawSettings.m_graphRadius), 100.f, 550.f);
        ImGui::SliderFloat("Vertex Radius", &(m_graph.m_drawSettings.m_vertexRadius), 15.f, 90.f);
    }

    if(ImGui::CollapsingHeader("Graph Settings")) {
        int updatedVertexCount = m_vertex_count;
        if (ImGui::InputInt("Vertex Count", &updatedVertexCount)) {
            this->newGraphWithCount(updatedVertexCount);
        }
    }
    ImGui::End();
}

void Application::draw_graph(sf::RenderWindow& window) {
    m_graph.display(window);
}