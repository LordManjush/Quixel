#include <SFML/Graphics.hpp>
#include <imgui.h>
#include <imgui-SFML.h>
#include "Style/ImguiStyle.h"
#include <iostream>
#include "Quixel.h"

QuixelExtra::Icon icon;

ImGui::ImGuiStyles imguiStyles;
int main()
{
    sf::RenderWindow window{ sf::VideoMode(1080, 700), "Quixel" };
    window.setFramerateLimit(120);

    ImGui::SFML::Init(window);
    auto& io = ImGui::GetIO();
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;

    auto fancyFont = io.Fonts->AddFontFromFileTTF(
        "./Data/fonts/NotoSans-Regular.ttf", 20);
    if (!ImGui::SFML::UpdateFontTexture()) {
        std::cerr << "No luck\n";
    }
    imguiStyles.DarkMode();
    icon.SetUpIcon("./Data/Icons/Error.png");
    Quixel::Update();
    sf::Clock deltaClock{};
    while (window.isOpen()) {
        sf::Event event{};
        while (window.pollEvent(event)) {
            ImGui::SFML::ProcessEvent(window, event);

            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        ImGui::SFML::Update(window, deltaClock.restart());

        ImGui::PushFont(fancyFont);
        ImGui::DockSpaceOverViewport();
        ImGui::ShowDemoWindow();
        ImGui::Begin("Test");
        ImGui::Image(icon.image);
        ImGui::End();

        Quixel::Update();

        ImGui::PopFont();
        window.clear();

        ImGui::SFML::Render(window);

        window.display();
    }
    ImGui::SFML::Shutdown();
}




