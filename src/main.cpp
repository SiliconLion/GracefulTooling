#include "imgui.h"
#include "imgui-SFML.h"

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/Window/Event.hpp>

#include "graceful_graph.h"
#include "application.h"

int main()
{
    sf::RenderWindow window(sf::VideoMode(2000, 1700), "");
    window.setVerticalSyncEnabled(true);
    ImGui::SFML::Init(window);

//this isn't really the right way to do dpi scalling, but will scale it up, and
// Im on a retina screen so I need this lol.
#ifdef GRACEFUL_CUSTOM_DPI
    ImGuiIO& io = ImGui::GetIO();
    io.FontGlobalScale = GRACEFUL_CUSTOM_DPI;
#endif


    Application app;


    window.setTitle(app.windowTitle);
    window.resetGLStates(); // call it if you only draw ImGui. Otherwise not needed.
    sf::Clock deltaClock;
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            ImGui::SFML::ProcessEvent(event);

            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        ImGui::SFML::Update(window, deltaClock.restart());

        app.display(window);

        window.clear(app.colorAsSFColor()); // fill background with color
        ImGui::SFML::Render(window);
        window.display();
    }

    ImGui::SFML::Shutdown();
}