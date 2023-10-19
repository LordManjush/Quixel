#include "Editor/QuixelEditor.h"
#include "SpriteRenderer.h"
#include <AddIcon/Add Icon.h>
#include <imgui_stdlib.h>
#include <imgui-SFML.h>
#include <Editor/Console.h>
#include <json.hpp>



Quixel::Scene::GameObject* selectedGameObject = nullptr;

bool IsPlaying = false;

std::vector<Quixel::Message> ConsoleMessages;
Quixel::Scene::Scene currentScene;

#pragma region Views
bool SceneWindow = true;
bool GameWindow = true;
bool PropertiesWindow = true;
bool ConsoleWindow = true;
#pragma endregion
Quixel::Scene::Camera MainCamera;
Quixel::Scene::Camera SceneCamera;
bool HasSaved = false;
Quixel::Scene::Save_Load saveAndload;
using json = nlohmann::json;

float zoom = 9;
void Quixel::Editor::Editor::SceneViewPort(sf::RenderTexture& rt, sf::View& SceneView)
{

    if (SceneWindow == true)
    {
        if (ImGui::IsKeyDown(ImGuiKey_G))
        {
            SceneCamera.Position.x = 350;
            SceneCamera.Position.y = 150;
        }
        if (ImGui::IsKeyDown(ImGuiKey_A))
        {
            SceneCamera.Position.x = SceneCamera.Position.x - 8;
        }
        if (ImGui::IsKeyDown(ImGuiKey_D))
        {
            SceneCamera.Position.x = SceneCamera.Position.x + 8;
        }
        if (ImGui::IsKeyDown(ImGuiKey_W))
        {
            SceneCamera.Position.y = SceneCamera.Position.y - 8;
        }
        if (ImGui::IsKeyDown(ImGuiKey_S))
        {
            SceneCamera.Position.y = SceneCamera.Position.y + 8;
        }

        sf::ContextSettings context;
        context.antialiasingLevel = 9;
        float zoomNum = ImGui::GetIO().MouseWheel;
        zoom += zoomNum;
        SceneView.setCenter(SceneCamera.Position.x, SceneCamera.Position.y);
        // SceneView.move(SceneCamera.Position.x, SceneCamera.Position.y);
        SceneView.setSize(1080, 500);
        SceneView.zoom(zoom);
        rt.create(1080, 500);
        rt.setView(SceneView);


        ImGui::Begin("SceneView", &SceneWindow, ImGuiWindowFlags_NoScrollbar);
        ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0, 0));
        ImGui::Image(rt, sf::Color::White);
        ImGui::PopStyleVar();
        ImGui::End();

    }
}

void Quixel::Editor::Editor::GameViewPort(sf::RenderTexture& rt, sf::View& GameView)
{
    if (GameWindow == true)
    {
        GameView.setSize(700, 500);
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
            if (ImGui::MenuItem("Save", NULL, nullptr))
            {
                for (auto& gameObject : currentScene.gameObjects)
                {
                    saveAndload.SaveGameObject(gameObject, "Game.qpk");
                }
                Message savedMessage;
                savedMessage.text = "Saved Project";
                ConsoleMessages.push_back(savedMessage);
            }
            if (ImGui::MenuItem("Open", NULL, nullptr))
            {
               // saveAndload.LoadGameObject("Game.qpk");
                for (auto& gameObject : currentScene.gameObjects)
                {

                }
            }
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
        currentScene.gameObjects.push_back(newGameObject);
    }
    if (ImGui::Selectable("Main Camera"))
    {
        MainCamera.IsSelected = true;
        selectedGameObject = nullptr;
    }
    ImGui::Separator();
    for (size_t i = 0; i < currentScene.gameObjects.size(); i++) {
        Scene::GameObject& object = currentScene.gameObjects[i];
        object.ID = i;
        ImGui::PushID(i + "obj");
        if (ImGui::Selectable(object.name.c_str(), false, ImGuiSelectableFlags_None, ImVec2(ImGui::GetWindowSize().x - 80, 20)))
        {
            MainCamera.IsSelected = false;
            selectedGameObject = &object;
        }
        ImGui::SameLine();
        if (ImGui::Selectable("Remove")) {
            currentScene.gameObjects.erase(currentScene.gameObjects.begin() + i);
            i--;
            selectedGameObject != &object;
            HasSaved = false;
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
                std::swap(currentScene.gameObjects[selectedGameObject->ID], currentScene.gameObjects[selectedGameObject->ID - 1]);
                int ID = selectedGameObject->ID;
                selectedGameObject = &currentScene.gameObjects[ID];
            }
            ImGui::SameLine();
            if (ImGui::Button("To bottom") && selectedGameObject->ID < currentScene.gameObjects.size() - 1)
            {
                std::swap(currentScene.gameObjects[selectedGameObject->ID], currentScene.gameObjects[selectedGameObject->ID + 1]);
                int ID = selectedGameObject->ID;
                selectedGameObject = &currentScene.gameObjects[ID];
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
Quixel::BluePrints::BluePrintEditor bluePrintEditor;
int Lat;
void Quixel::Editor::Editor::BluePrintEditor()
{
    if (ImGui::Begin("BluePrints"))
    {

        if (selectedGameObject != nullptr)
        {
            ImGui::Text(selectedGameObject->name.c_str());
            bluePrintEditor.Start();
            if (ImGui::IsKeyPressed(ImGuiKey_Z))
            {
                Quixel::BluePrints::BaseNode b;
                b.id = Lat;
                Lat = Lat + 1;
                bluePrintEditor.nodes.push_back(b);
            }

        }
        if (selectedGameObject == nullptr)
        {
            ImGui::Text("No GameObject selected");
        }
        ImGui::End();
    }
}
void Quixel::Editor::Editor::Console()
{
    if (ImGui::Begin("Console"))
    {
        if (ImGui::ColorButton("Clear", ImVec4(255, 0, 0, 255), ImGuiColorEditFlags_NoTooltip) && ConsoleMessages.size() >= 0)
        {
            ConsoleMessages.clear(); 
        }
        for (auto& message : ConsoleMessages)
        {
            ImGui::Selectable(message.text.c_str());
        }
        ImGui::End();
    }
}

void Quixel::Editor::Editor::DrawAll(sf::RenderTexture& rt1, sf::RenderTexture& rt2)
{
    rt2.clear(sf::Color((int)(MainCamera.color[0] * 255),
        (int)(MainCamera.color[1] * 255),
        (int)(MainCamera.color[2] * 255),
        MainCamera.Opacity));
    for (auto& object : currentScene.gameObjects)
    {
        for (auto& texture : object.sprites)
        {
            object.shape.setTexture(texture.texture);
            Quixel::Scene::DrawAll(rt1, object);
            Quixel::Scene::DrawAll(rt2, object);
        }
    }
}


