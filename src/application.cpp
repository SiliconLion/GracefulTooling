//
// Created by David Sullivan on 4/13/22.
//

#include "application.h"
#include <SFML/Graphics/RenderWindow.hpp>

Application::Application() {
    m_color[0] = 0.0f;
    m_color[1] = 0.0f;
    m_color[2] = 0.0f;
    memcpy(windowTitle, "ImGui + SFML = <3", 256);
}

void Application::display(sf::RenderWindow& window) {
    ImGui::Begin("Sample window"); // begin window

    // Background color edit
    if (ImGui::ColorEdit3("Background color", m_color)) {
    }

    // Window title text edit
    ImGui::InputText("Window title", windowTitle, 255);

    if (ImGui::Button("Update window title")) {
        // this code gets if user clicks on the button
        // yes, you could have written if(ImGui::InputText(...))
        // but I do this to show how buttons work :)
        window.setTitle(windowTitle);
    }

    ImGuiIO& io = ImGui::GetIO();
    ImGui::DragFloat("global scale", &io.FontGlobalScale, 0.005f, 0.3, 4.0, "%.2f", ImGuiSliderFlags_AlwaysClamp); // Scale everything


    ImGui::End(); // end window
}

sf::Color Application::colorAsSFColor() {
    sf::Color bgColor;
    bgColor.r = static_cast<sf::Uint8>(m_color[0] * 255.f);
    bgColor.g = static_cast<sf::Uint8>(m_color[1] * 255.f);
    bgColor.b = static_cast<sf::Uint8>(m_color[2] * 255.f);
    return bgColor;
}