#include "imgui.h"
#include "imgui-SFML.h"

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/Window/Event.hpp>

#include "color_definitions.h"
#include "application.h"

//using namespace app_colors;





int main()
{





    sf::RenderWindow window(sf::VideoMode(2000, 1700), "");
    window.setVerticalSyncEnabled(true);
    auto _ = ImGui::SFML::Init(window);

//this isn't really the right way to do dpi scalling, but will scale it up, and
// Im on a retina screen so I need this lol.
#ifdef GRACEFUL_CUSTOM_DPI
    ImGuiIO& io = ImGui::GetIO();
    io.FontGlobalScale = GRACEFUL_CUSTOM_DPI;
#endif


    Application app;
    app.reset_vertex_count(105);


    window.resetGLStates(); // call it if you only draw ImGui. Otherwise not needed.
    sf::Clock deltaClock;
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            ImGui::SFML::ProcessEvent(event);

            if (event.type == sf::Event::Closed) {
                window.close();
            }

            if(event.)
        }

        ImGui::SFML::Update(window, deltaClock.restart());



        window.clear(app_colors::BACKGROUND_1); // fill background with color


        app.display(&window);


        ImGui::SFML::Render(window);
        window.display();
    }

    ImGui::SFML::Shutdown();
}