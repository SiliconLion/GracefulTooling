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
    m_graph_radius(400), m_vertex_radius(45), m_vertex_font(),
    m_guiState()
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

        //probably very bad form to make these global, there's not a good reason to
        //make them dedicated variables in the application class, other than so that the
        //input fields are reset each frame.



        auto inputFlags = ImGuiInputTextFlags_EnterReturnsTrue | ImGuiInputTextFlags_AlwaysInsertMode;
        ImGui::InputInt("##Vertex 1", &(m_guiState.vertex_1), inputFlags);
//        ImGui::SameLine();
        ImGui::InputInt("##Vertex 2", &(m_guiState.vertex_2), inputFlags);
//        ImGui::SameLine();

        if (ImGui::BeginPopupModal("Edge Color Picker", NULL, ImGuiWindowFlags_AlwaysAutoResize)){
            auto flags =    ImGuiColorEditFlags_NoAlpha;
//                            ImGuiColorEditFlags_
            auto color1Copy = m_guiState.color1;
            ImGui::ColorPicker3("Color Picker", (float*)&(m_guiState.color1), flags);
            if(ImGui::Button("Done")) {ImGui::CloseCurrentPopup();}
            ImGui::SameLine();
            if(ImGui::Button("Cancel")){
                m_guiState.color1 = color1Copy;
                ImGui::CloseCurrentPopup();
            }

            ImGui::EndPopup();
        }

        if(ImGui::ColorButton("##Edge Color 1", m_guiState.color1)) {
            ImGui::OpenPopup("Edge Color Picker");
        }

        if(ImGui::Button("Connect")){
            this->m_graph.addEdge(m_guiState.vertex_1, m_guiState.vertex_2, (float*)&(m_guiState.color1) );
        }
        ImGui::Separator();


        ImGui::InputInt("##Vertex 3", &(m_guiState.vertex_3), inputFlags);
//        ImGui::SameLine();
        ImGui::InputInt("##Vertex 4", &(m_guiState.vertex_4), inputFlags);
        if(ImGui::Button("Disconnect")){
            this->m_graph.removeEdge(m_guiState.vertex_3, m_guiState.vertex_4);
        }


        ImGui::Text("Coloring");
        ImGui::SameLine();
        ImGui::InputInt("#vertex to color", &m_guiState.vertex_5);
        if(ImGui::ColorButton("##Edge Color 2", m_guiState.color1)) {
            ImGui::OpenPopup("Edge Color Picker");
        }
        if(ImGui::Button("Color Vertex")) {

        }
    }

    if(ImGui::CollapsingHeader("Appearance")) {
        //this may be slightly less than kosher, but its not actually bad from a lifetime perspective
        //as this is updated every frame.
        ImGui::SliderFloat("Graph Radius", &(m_graph.m_drawSettings.m_graphRadius), 100.f, 550.f);
        ImGui::SliderFloat("Vertex Radius", &(m_graph.m_drawSettings.m_vertexRadius), 15.f, 90.f);
        ImGui::SliderFloat("Edge Width", &(m_graph.m_drawSettings.m_edgeWidth), 3.f, 50.f);

    }

    if(ImGui::CollapsingHeader("Graph Settings")) {
        int updatedVertexCount = m_vertex_count;

        bool allowDestructiveAction = false;
        ImGui::InputInt("Vertex Count", &updatedVertexCount);

        if(ImGui::BeginPopupModal("Warning: Destructive Action")) {
            ImGui::Text("WARNING! This action will reset the graph. Do you wish to proceed?");
            if(ImGui::Button("Yes")) {
                allowDestructiveAction = true;
                ImGui::CloseCurrentPopup();
            }
            if(ImGui::Button("No!")) {ImGui::CloseCurrentPopup();}


            ImGui::EndPopup();
        }

        if(ImGui::Button("Update Graph")) {
            ImGui::OpenPopup("Warning: Destructive Action");
            if (allowDestructiveAction) {
                this->newGraphWithCount(updatedVertexCount);
            }
        }


    }
    ImGui::End();
}

void Application::draw_graph(sf::RenderWindow& window) {
    m_graph.display(window);
}