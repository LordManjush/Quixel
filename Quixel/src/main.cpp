#include <imgui-SFML.h>
#include "Style/ImguiStyle.h"
#include <iostream>
#include "Quixel.h"

QuixelExtra::Icon icon;
ImGui::ImGuiStyles imguiStyles;
Quixel::Editor::Editor editor;


sf::Clock deltaClock{};


//Views
sf::View SceneView;
sf::View GameView;
sf::RenderTexture SceneViewRt;
sf::RenderTexture GameViewRt;

int main()
{
    sf::RenderWindow window{ sf::VideoMode(1080, 600), "Quixel editor" };
    window.setFramerateLimit(120);
    ImGui::SFML::Init(window);
    GameView.setCenter(0, 0);
    SceneView.setCenter(0, 0);
    SceneView.setSize(sf::Vector2f(1080, 500));
    GameView.setSize(sf::Vector2f(1080, 500));
    auto& io = ImGui::GetIO();
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
    editor.InitEditor();
    auto fancyFont = io.Fonts->AddFontFromFileTTF(
        "./Data/fonts/NotoSans-Regular.ttf", 20);
    if (!ImGui::SFML::UpdateFontTexture()) {
        std::cerr << "No luck\n";
    }

    imguiStyles.DarkMode();

    while (window.isOpen()) {
        sf::Event event{};
        while (window.pollEvent(event)) {
            ImGui::SFML::ProcessEvent(window, event);

            if (event.type == sf::Event::Closed) {
                window.close();
            }

            ImGui::SFML::Update(window, deltaClock.restart());


            ImGui::PushFont(fancyFont);
            ImGui::DockSpaceOverViewport();
            editor.SceneViewPort(SceneViewRt, SceneView);
            editor.GameViewPort(GameViewRt, GameView);

            editor.SceneHierarchy(SceneViewRt);
            editor.Console();
            editor.BluePrintEditor();
            SceneViewRt.clear(sf::Color(128, 128, 128));
            GameViewRt.clear(sf::Color::Black);
            editor.ProperitesPanel();
            editor.DrawAll(SceneViewRt, GameViewRt);



            SceneViewRt.display();
            GameViewRt.display();


            ImGui::PopFont();

            window.clear();
            ImGui::SFML::Render(window);
            window.display();
        }
    }
    ImGui::SFML::Shutdown();

    return 0;
}




