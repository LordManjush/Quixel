#include "Editor/QuixelEditor.h"
#include "SpriteRenderer.h"
#include <AddIcon/Add Icon.h>
#include <imgui_stdlib.h>
#include <imgui-SFML.h>


Quixel::Scene::GameObject* selectedGameObject = nullptr;
std::vector<Quixel::Scene::GameObject> gameObjects;
bool IsPlaying = false;

#pragma region Views
bool SceneWindow = true;
bool GameWindow = true;
bool PropertiesWindow = true;
bool ConsoleWindow = true;
#pragma endregion
Quixel::Scene::Camera MainCamera;


void Quixel::Editor::Editor::SceneViewPort(sf::RenderTexture& rt, sf::View& SceneView, ImVec2 Size)
{
    Quixel::Scene::Camera SceneCamera;
    if (Quixel::InputSystem::IsKeyPressed(ImGuiKey_A))
    {
        SceneCamera.Position.x--;
    }
    if (Quixel::InputSystem::IsKeyPressed(ImGuiKey_D))
    {
        SceneCamera.Position.x++;
    }
    if (Quixel::InputSystem::IsKeyPressed(ImGuiKey_W))
    {
        SceneCamera.Position.y--;
    }
    if (Quixel::InputSystem::IsKeyPressed(ImGuiKey_S))
    {
        SceneCamera.Position.y++;
    }
    if (SceneWindow == true)
    {
        sf::ContextSettings context;
        context.antialiasingLevel = 9;
        rt.create(1080, 500);
        SceneView.setCenter(SceneCamera.Position.x, SceneCamera.Position.y);
        // SceneView.move(SceneCamera.Position.x, SceneCamera.Position.y);
        SceneView.setSize(rt.getSize().x, rt.getSize().y);
        rt.setView(SceneView);

        ImGui::Begin("SceneView", &SceneWindow, ImGuiWindowFlags_NoScrollbar);
        ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0, 0));
        ImGui::Image(rt, sf::Color::White);
        ImGui::PopStyleVar();
        ImGui::End();

    }
}

void Quixel::Editor::Editor::GameViewPort(sf::RenderTexture& rt, sf::View& GameView, ImVec2 Size)
{
    if (GameWindow == true)
    {
        GameView.setSize(Size.x, Size.y);
        GameView.setCenter(MainCamera.Position);
        rt.create(1080, 500);
        rt.setView(GameView);
        ImGuiWindowFlags flags;
        flags = ImGuiWindowFlags_NoScrollWithMouse, ImGuiWindowFlags_NoTitleBar;
        ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(8, 0));
        ImGui::Begin("Game", nullptr, flags);
        ImGui::Image(rt, sf::Color::White);
        ImGui::PopStyleVar();
        ImGui::End();
    }

}
void Quixel::Editor::Editor::SceneHierarchy(sf::RenderTexture& rt)
{
    ImGui::Begin("Hierarchy", nullptr, ImGuiWindowFlags_MenuBar);
    if (ImGui::BeginMenuBar())
    {
        if (ImGui::BeginMenu("File"))
        {
            ImGui::MenuItem("Save", NULL, nullptr);
            ImGui::MenuItem("Open", NULL, nullptr);
            ImGui::MenuItem("Build", NULL, nullptr);
            ImGui::EndMenu();
        }
        if (ImGui::BeginMenu("View"))
        {
            ImGui::MenuItem("Scene View", NULL, &SceneWindow);
            ImGui::MenuItem("Properties", NULL, &PropertiesWindow);
            ImGui::MenuItem("Console", NULL, &ConsoleWindow);
            ImGui::EndMenu();
        }
        ImGui::EndMenuBar();
    }

#pragma region Play and Stop
    ImGui::Separator();
    if (IsPlaying == false)
    {
        if (ImGui::Button("Play") && IsPlaying == false)
        {
            IsPlaying = true;
        }
    }
    if (IsPlaying == true)
    {
        if (ImGui::Button("Stop") && IsPlaying == true)
        {
            IsPlaying = false;
        }
    }
    ImGui::Separator();

#pragma endregion

    if (ImGui::Button("Add")) {
        Scene::GameObject newGameObject;
        gameObjects.push_back(newGameObject);
    }
    if (ImGui::Selectable("Main Camera"))
    {
        MainCamera.IsSelected = true;
        selectedGameObject = nullptr;
    }
    ImGui::Separator();
    for (size_t i = 0; i < gameObjects.size(); i++) {
        Scene::GameObject& object = gameObjects[i];
        object.ID = i;
        ImGui::PushID(i + "obj");
        if (ImGui::Selectable(object.name.c_str(), false, ImGuiSelectableFlags_None, ImVec2(ImGui::GetWindowSize().x - 80, 20)))
        {
            MainCamera.IsSelected = false;
            selectedGameObject = &object;
        }
        ImGui::SameLine();
        if (ImGui::Selectable("Remove")) {
            gameObjects.erase(gameObjects.begin() + i);
            i--;
            selectedGameObject != &object;
        }
        ImGui::PopID();
        ImGui::Separator();
    }
    ImGui::End();
}
void Quixel::Editor::Editor::ProperitesPanel()
{
    if (PropertiesWindow == true)
    {
        if (ImGui::IsKeyPressed(ImGuiKey_Escape))
        {
            MainCamera.IsSelected = false;
            selectedGameObject = nullptr;
        }
        ImGui::Begin("Properties", &PropertiesWindow);
        if (MainCamera.IsSelected == true && selectedGameObject == nullptr)
        {
            ImGui::Separator();
            ImGui::Text("Name - MainCamera");
            ImGui::Separator();
            if (ImGui::CollapsingHeader("Transform"))
            {
                ImGui::DragFloat2("Position", reinterpret_cast<float*>(&MainCamera.Position), 1, 0.1, 0.1);
            }
            if (ImGui::CollapsingHeader("Settings"))
            {
                ImGui::ColorEdit3("Color ", MainCamera.color);
                ImGui::DragFloat(" Opacity", &MainCamera.Opacity, 1, 0.1, 0.1);
            }
        }
        if (selectedGameObject != nullptr)
        {
            ImGui::InputText("##dgdfg", &selectedGameObject->name);
            ImGui::Separator();
            if (ImGui::Button("To top") && selectedGameObject->ID > 0)
            {
                std::swap(gameObjects[selectedGameObject->ID], gameObjects[selectedGameObject->ID - 1]);
                int ID = selectedGameObject->ID;
                selectedGameObject = &gameObjects[ID];
            }
            ImGui::SameLine();
            if (ImGui::Button("To botton") && selectedGameObject->ID < gameObjects.size() - 1)
            {
                std::swap(gameObjects[selectedGameObject->ID], gameObjects[selectedGameObject->ID + 1]);
                int ID = selectedGameObject->ID;
                selectedGameObject = &gameObjects[ID];
            }
            ImGui::Separator();
            if (ImGui::CollapsingHeader("About"))
            {
                ImGui::Separator();
                ImGui::Text("Name - %s", selectedGameObject->name);
                ImGui::Separator();
                ImGui::Text("ID - %i", selectedGameObject->ID);
                ImGui::Separator();


            }
            if (ImGui::CollapsingHeader("Transform"))
            {
                ImGui::Separator();
                ImGui::Text("Position");
                ImGui::Separator();
                ImGui::DragFloat2(" ", reinterpret_cast<float*>(&selectedGameObject->Position), 1, 0.1, 0.1);
    
                ImGui::Separator();
                ImGui::Text("Scale");
                ImGui::DragFloat2("  ", reinterpret_cast<float*>(&selectedGameObject->Scale), 1, 0.1, 0.1);
 
                ImGui::Separator();
                ImGui::DragFloat("Rotation", &selectedGameObject->Rotation, 1, 0.1, 0.1);
                ImGui::Separator();
            }
            if (ImGui::CollapsingHeader("SpriteRenderer"))
            {
                Quixel::Compoent::SpriteRenderer(selectedGameObject);

                ImGui::ColorEdit3("Color", selectedGameObject->color);
                ImGui::DragFloat("Opacity", &selectedGameObject->Opacity, 1, 0.1, 0.1);

            }
        }
        if (MainCamera.IsSelected == false && selectedGameObject == nullptr)
        {
            ImGui::Text("None Selected");
        }
        ImGui::End();
    }
}

void Quixel::Editor::Editor::BluePrintEditor()
{
    if (ImGui::Begin("BluePrints"))
    {
        imnodes::BeginNodeEditor();
        if (selectedGameObject != nullptr)
        {
            ImGui::Text(selectedGameObject->name.c_str());
        }
        if (selectedGameObject == nullptr)
        {
            ImGui::Text("No GameObject selected");
        }
        imnodes::EndNodeEditor();
        ImGui::End();
    }
}

void Quixel::Editor::Editor::DrawAll(sf::RenderTexture& rt1, sf::RenderTexture& rt2)
{
    rt2.clear(sf::Color((int)(MainCamera.color[0] * 255),
        (int)(MainCamera.color[1] * 255),
        (int)(MainCamera.color[2] * 255),
        MainCamera.Opacity));
    for (auto& object : gameObjects)
    {
        for (auto& texture : object.sprites)
        {
             object.shape.setTexture(texture.texture);
        }
        Quixel::Scene::DrawAll(rt1, object);
        Quixel::Scene::DrawAll(rt2, object);
    }
}


