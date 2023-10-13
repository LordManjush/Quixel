#include "Editor/QuixelEditor.h"
#include <imgui.h>
#include <AddIcon/Add Icon.h>
#include "Quixel.h"
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
Quixel::Scene::Camera SceneCamera;

void Quixel::Editor::Editor::SceneViewPort(sf::RenderTexture& rt, sf::View& SceneView, ImVec2 Size)
{
    if (ImGui::IsKeyDown(ImGuiKey_A))
    {
        SceneCamera.Position.x--;
    }
    if (ImGui::IsKeyDown(ImGuiKey_D))
    {
        SceneCamera.Position.x++;
    }
    if (ImGui::IsKeyDown(ImGuiKey_W))
    {
        SceneCamera.Position.y--;
    }
    if (ImGui::IsKeyDown(ImGuiKey_S))
    {
        SceneCamera.Position.y++;
    }
    if (SceneWindow == true)
    {
        sf::ContextSettings context;
        context.antialiasingLevel = 9;
        SceneView.setCenter(SceneCamera.Position.x, SceneCamera.Position.y);
        SceneView.setSize(rt.getSize().x, rt.getSize().y);
        rt.create(1080, 500);
        rt.setView(SceneView);
        ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0, 0));
        ImGui::Begin("SceneView", &SceneWindow, ImGuiWindowFlags_NoScrollbar);
        ImGui::Image(rt, sf::Color::White);
        ImGui::End();
        ImGui::PopStyleVar();
    }
}
void Quixel::Editor::Editor::GameViewPort(sf::RenderTexture& rt, sf::View& GameView, ImVec2 Size)
{
    if (GameWindow == true)
    {
        GameView.setSize(Size.x, Size.y);
        GameView.setCenter(MainCamera.Position.x, MainCamera.Position.y);
        rt.create(1080, 500);
        rt.setView(GameView);
        ImGuiWindowFlags flags;
        flags = ImGuiWindowFlags_NoScrollWithMouse, ImGuiWindowFlags_NoTitleBar;
        ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(200, 0));
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
    if (IsPlaying == false)
    {
        ImGui::Separator();
        if (ImGui::Button("Play") && IsPlaying == false)
        {
            IsPlaying = true;
        }
        ImGui::Separator();
    }
    if (IsPlaying == true)
    {
        ImGui::Separator();
        if (ImGui::Button("Stop") && IsPlaying == true)
        {
            IsPlaying = false;
        }
        ImGui::Separator();
    }

#pragma endregion

    if (ImGui::Button("Add")) {
        Scene::GameObject newGameObject;
        newGameObject.shape.setFillColor(sf::Color::Blue);
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

int node_id = 0;
int linkId = 0;

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
            }
        }
        if (selectedGameObject != nullptr)
        {
            ImGui::InputText("##dgdfg", &selectedGameObject->name);

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
                if (ImGui::DragFloat2(" ", reinterpret_cast<float*>(&selectedGameObject->Position), 1, 0.1, 0.1))
                {
                    

                }
                else
                {
                    
                }
                ImGui::Separator();
                ImGui::Text("Scale");
                if (ImGui::DragFloat2("  ", reinterpret_cast<float*>(&selectedGameObject->Scale), 1, 0.1, 0.1))
                {
                    
                }
                else
                {
                    
                }
                ImGui::Separator();
                if (ImGui::DragFloat("Rotation", &selectedGameObject->Rotation, 1, 0.1, 0.1))
                {

                }
                ImGui::Separator();
            }
            if (ImGui::CollapsingHeader("SpriteRenderer"))
            {
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

void Quixel::Editor::Editor::DrawAll(sf::RenderTexture& rt1, sf::RenderTexture& rt2)
{
    for (auto& object : gameObjects)
    {
        Quixel::Scene::DrawAll(rt1, object);
        Quixel::Scene::DrawAll(rt2, object);
    }
}


