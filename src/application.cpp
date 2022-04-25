//
// Created by David Sullivan on 4/13/22.
//

#include "application.h"
#include "color_definitions.h"
#include "platform_configuration.h"
#include "utilities.h"

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
        ImGui::Text("Connections");

        //probably very bad form to make these global, there's not a good reason to
        //make them dedicated variables in the application class, other than so that the
        //input fields are reset each frame.



        auto inputFlags = ImGuiInputTextFlags_EnterReturnsTrue | ImGuiInputTextFlags_AlwaysInsertMode;
        ImGui::InputInt("##Vertex 1", &(m_guiState.vertex_1), inputFlags);
//        ImGui::SameLine();
        ImGui::InputInt("##Vertex 2", &(m_guiState.vertex_2), inputFlags);
//        ImGui::SameLine();

        if (ImGui::BeginPopupModal("Edge Color Picker 1", NULL, ImGuiWindowFlags_AlwaysAutoResize)){
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
            ImGui::OpenPopup("Edge Color Picker 1");
        }
        ImGui::SameLine();
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

        ImGui::Separator();

        ImGui::Text("Coloring");
//        ImGui::Text("Vertex to Color");
        ImGui::InputInt("##Vertex to color", &m_guiState.vertex_5);
        if(ImGui::ColorButton("##Vertex Color Picker", m_guiState.color2)) {
            ImGui::OpenPopup("Vertex Color Picker");
        }


        if (ImGui::BeginPopupModal("Vertex Color Picker", NULL, ImGuiWindowFlags_AlwaysAutoResize)){
            auto flags =    ImGuiColorEditFlags_NoAlpha;
//                            ImGuiColorEditFlags_
            auto color2Copy = m_guiState.color2;
            ImGui::ColorPicker3("Color Picker", (float*)&(m_guiState.color2), flags);
            if(ImGui::Button("Done")) {ImGui::CloseCurrentPopup();}
            ImGui::SameLine();
            if(ImGui::Button("Cancel")){
                m_guiState.color2 = color2Copy;
                ImGui::CloseCurrentPopup();
            }

            ImGui::EndPopup();
        }

        ImGui::SameLine();
        if(ImGui::Button("Color Vertex")) {
            m_graph.colorVertex(m_guiState.vertex_5, from_ImVec4(m_guiState.color2));
        }


//        ImGui::Text("Color Edge");
        ImGui::InputInt("##Input Vertex 6", &(m_guiState.vertex_6), inputFlags);
//        ImGui::SameLine();
        ImGui::InputInt("##Input Vertex 7", &(m_guiState.vertex_7), inputFlags);
        if(ImGui::ColorButton("##Edge Color Picker2", m_guiState.color3)) {
            ImGui::OpenPopup("Edge Color Picker 2");
        }


        if (ImGui::BeginPopupModal("Edge Color Picker 2", NULL, ImGuiWindowFlags_AlwaysAutoResize)){
            auto flags =    ImGuiColorEditFlags_NoAlpha;
//                            ImGuiColorEditFlags_
            auto color3Copy = m_guiState.color3;
            ImGui::ColorPicker3("Color Picker", (float*)&(m_guiState.color3), flags);
            if(ImGui::Button("Done")) {ImGui::CloseCurrentPopup();}
            ImGui::SameLine();
            if(ImGui::Button("Cancel")){
                m_guiState.color3 = color3Copy;
                ImGui::CloseCurrentPopup();
            }

            ImGui::EndPopup();
        }

        ImGui::SameLine();
        if(ImGui::Button("Color Edge")) {
            m_graph.colorEdge(m_guiState.vertex_6, m_guiState.vertex_7, from_ImVec4(m_guiState.color3));
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

        ImGui::InputInt("Vertex Count", &(m_guiState.newVertexCount));

        if(ImGui::Button("Update Graph")) {
            ImGui::OpenPopup("Warning: Destructive Action");
        }

        if(ImGui::BeginPopupModal("Warning: Destructive Action")) {
            ImGui::Text("WARNING! This action will reset the graph. Do you wish to proceed?");
            if(ImGui::Button("Yes")) {
                this->newGraphWithCount(m_guiState.newVertexCount);
                ImGui::CloseCurrentPopup();
            }
            if(ImGui::Button("No!")) {
                ImGui::CloseCurrentPopup();
            }


            ImGui::EndPopup();
        }


    }
    ImGui::End();
}

void Application::draw_graph(sf::RenderWindow& window) {
    m_graph.display(window);
}