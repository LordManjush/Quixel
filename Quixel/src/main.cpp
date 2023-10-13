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

int main()
{
    sf::RenderWindow window{ sf::VideoMode(1080, 600), "Quixel editor" };
    window.setFramerateLimit(120);
    ImGui::SFML::Init(window);
    //GameView.setCenter(0, 0);
    //SceneView.setCenter(0, 0);
    SceneView.setSize(sf::Vector2f(1080, 500));
    GameView.setSize(sf::Vector2f(1080, 500));
    imnodes::CreateContext();
    auto& io = ImGui::GetIO();
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;

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

            sf::RenderTexture SceneViewRt;
            sf::RenderTexture GameViewRt;

            sf::CircleShape shape{ 50, 100 };
            shape.setFillColor(sf::Color::Red);

            ImGui::PushFont(fancyFont);
            ImGui::DockSpaceOverViewport();
            SceneViewRt.create(1080, 500);
            GameViewRt.create(1080, 500);
            SceneViewRt.clear(sf::Color::Black);
            GameViewRt.clear(sf::Color::Black);
            editor.DrawAll(SceneViewRt, GameViewRt);



            SceneViewRt.display();
            GameViewRt.display();
            editor.SceneViewPort(SceneViewRt, SceneView, ImVec2(1080, 500));
            editor.GameViewPort(GameViewRt, GameView, ImVec2(700, 500));
            editor.ProperitesPanel();
            editor.SceneHierarchy(SceneViewRt);

            //draw


            ImGui::PopFont();

            window.clear();
            ImGui::SFML::Render(window);
            window.display();
        }
    }
    ImGui::SFML::Shutdown();
    imnodes::DestroyContext();
    return 0;
}




