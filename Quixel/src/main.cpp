#include <SFML/Graphics.hpp>
#include <imgui.h>
#include <imgui-SFML.h>
#include "Style/ImguiStyle.h"
#include <iostream>
#include "Quixel.h"

QuixelExtra::Icon icon;
Quixel::Scene::Window _window;
ImGui::ImGuiStyles imguiStyles;
int main()
{

    Quixel::Start(_window);

    ImGui::SFML::Init(_window.window);
    auto& io = ImGui::GetIO();
    //io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;

    auto fancyFont = io.Fonts->AddFontFromFileTTF(
        "./Data/fonts/NotoSans-Regular.ttf", 20);
    if (!ImGui::SFML::UpdateFontTexture()) {
        std::cerr << "No luck\n";
    }
    imguiStyles.DarkMode();
    icon.SetUpIcon("./Data/Icons/Error.png");
    sf::Clock deltaClock{};
    while (_window.window.isOpen()) {
        sf::Event event{};
        while (_window.window.pollEvent(event)) {
            ImGui::SFML::ProcessEvent(_window.window, event);

            if (event.type == sf::Event::Closed) {
                _window.window.close();
            }
        }
        
        ImGui::SFML::Update(_window.window, deltaClock.restart());

        ImGui::PushFont(fancyFont);

        //Editor



        ImGui::PopFont();
        Quixel::Update(_window);


        ImGui::SFML::Render(_window.window);

        _window.window.display();
    }
    ImGui::SFML::Shutdown();
}




