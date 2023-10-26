#include "Editor/QuixelEditor.h"
#include "SpriteRenderer.h"
#include <AddIcon/Add Icon.h>
#include <imgui_stdlib.h>
#include <imgui-SFML.h>



Quixel::Scene::GameObject* selectedGameObject = nullptr;

bool IsPlaying = false;

std::vector<Quixel::Message> ConsoleMessages;
Quixel::Scene::Scene currentScene;
std::vector<Quixel::Scene::GameObject> gameObjectsForPlay;
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
bool OnStart = false;

#pragma region Blueprints

#pragma endregion


void Quixel::Editor::Editor::InitEditor()
{
    Message m;
    m.text = "[Sucess] Quixel Editor loaded";
    Message z;
    z.text = "[Sucess] Internal errors not found";

    ConsoleMessages.push_back(m);
    ConsoleMessages.push_back(z);
}
void Quixel::Editor::Editor::SceneViewPort(sf::RenderTexture& rt, sf::View& SceneView)
{

    if (SceneWindow == true)
    {
        if (ImGui::IsKeyDown(ImGuiKey_F))
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

        float zoomNum = ImGui::GetIO().MouseWheel;
        zoom -= zoomNum;
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
    if (IsPlaying == true)
    {
        for (auto& gameObject : currentScene.gameObjects)
        {
            for (auto& action : gameObject.actions)
            {
                action.SetUpAllKeys();
                if (action.TypeOfActionID == 1 && ImGui::IsKeyPressed(action.keyCode))
                {
                    if (action.TypeOfLogicID == 0)
                    {

                        Message debug;
                        debug.text = "[Debug] " + action.PrintCode;
                        ConsoleMessages.push_back(debug);
                    }
                    if (action.TypeOfLogicID == 1)
                    {
                        gameObject.Position.x += action.StepData;
                    }
                    if (action.TypeOfLogicID == 2)
                    {
                        gameObject.Position.y += action.StepData;
                    }
                    if (action.TypeOfLogicID == 3)
                    {
                        gameObject.Scale.x += action.StepData;
                    }
                    if (action.TypeOfLogicID == 4)
                    {

                        gameObject.Scale.y += action.StepData;
                    }
                    if (action.TypeOfLogicID == 5)
                    {
                        gameObject.Rotation += action.StepData;
                    }
                    if (action.TypeOfLogicID == 6)
                    {
                        gameObject.color[0] = action.CodeColor[0];

                        gameObject.color[1] = action.CodeColor[1];

                        gameObject.color[2] = action.CodeColor[2];

                        gameObject.Opacity = action.CodeOpacity;
                    }
                    if (action.TypeOfLogicID == 7)
                    {
                        gameObject.Scale.x = action.StepData;
                    }
                    if (action.TypeOfLogicID == 8)
                    {
                        gameObject.Scale.y = action.StepData;
                    }
                    if (action.TypeOfLogicID == 9)
                    {
                        gameObject.Position.x = action.StepData;
                    }
                    if (action.TypeOfLogicID == 10)
                    {
                        gameObject.Position.y = action.StepData;
                    }
                    if (action.TypeOfLogicID == 11)
                    {
                        gameObject.Rotation = action.StepData;
                    }
                }
            }
        }
        for (auto& gameObject : currentScene.gameObjects)
        {
            for (auto& action : gameObject.actions)
            {
                action.SetUpAllKeys();
                if (action.TypeOfActionID == 2 && ImGui::IsKeyDown(action.keyCode))
                {
                    if (action.TypeOfLogicID == 0)
                    {

                        Message debug;
                        debug.text = "[Debug] " + action.PrintCode;
                        ConsoleMessages.push_back(debug);
                    }
                    if (action.TypeOfLogicID == 1)
                    {
                        gameObject.Position.x += action.StepData;
                    }
                    if (action.TypeOfLogicID == 2)
                    {
                        gameObject.Position.y += action.StepData;
                    }
                    if (action.TypeOfLogicID == 3)
                    {
                        gameObject.Scale.x += action.StepData;
                    }
                    if (action.TypeOfLogicID == 4)
                    {

                        gameObject.Scale.y += action.StepData;
                    }
                    if (action.TypeOfLogicID == 5)
                    {
                        gameObject.Rotation += action.StepData;
                    }
                    if (action.TypeOfLogicID == 6)
                    {
                        gameObject.color[0] = action.CodeColor[0];

                        gameObject.color[1] = action.CodeColor[1];

                        gameObject.color[2] = action.CodeColor[2];

                        gameObject.Opacity = action.CodeOpacity;
                    }
                    if (action.TypeOfLogicID == 7)
                    {
                        gameObject.Scale.x = action.StepData;
                    }
                    if (action.TypeOfLogicID == 8)
                    {
                        gameObject.Scale.y = action.StepData;
                    }
                    if (action.TypeOfLogicID == 9)
                    {
                        gameObject.Position.x = action.StepData;
                    }
                    if (action.TypeOfLogicID == 10)
                    {
                        gameObject.Position.y = action.StepData;
                    }
                    if (action.TypeOfLogicID == 11)
                    {
                        gameObject.Rotation = action.StepData;
                    }
                }
            }
        }
        for (auto& gameObject : currentScene.gameObjects)
        {
            for (auto& action : gameObject.actions)
            {
                action.SetUpAllKeys();
                if (action.TypeOfActionID == 3 && ImGui::IsKeyReleased(action.keyCode))
                {
                    if (action.TypeOfLogicID == 0)
                    {

                        Message debug;
                        debug.text = "[Debug] " + action.PrintCode;
                        ConsoleMessages.push_back(debug);
                    }
                    if (action.TypeOfLogicID == 1)
                    {
                        gameObject.Position.x += action.StepData;
                    }
                    if (action.TypeOfLogicID == 2)
                    {
                        gameObject.Position.y += action.StepData;
                    }
                    if (action.TypeOfLogicID == 3)
                    {
                        gameObject.Scale.x += action.StepData;
                    }
                    if (action.TypeOfLogicID == 4)
                    {

                        gameObject.Scale.y += action.StepData;
                    }
                    if (action.TypeOfLogicID == 5)
                    {
                        gameObject.Rotation += action.StepData;
                    }
                    if (action.TypeOfLogicID == 6)
                    {
                        gameObject.color[0] = action.CodeColor[0];

                        gameObject.color[1] = action.CodeColor[1];

                        gameObject.color[2] = action.CodeColor[2];

                        gameObject.Opacity = action.CodeOpacity;
                    }
                    if (action.TypeOfLogicID == 7)
                    {
                        gameObject.Scale.x = action.StepData;
                    }
                    if (action.TypeOfLogicID == 8)
                    {
                        gameObject.Scale.y = action.StepData;
                    }
                    if (action.TypeOfLogicID == 9)
                    {
                        gameObject.Position.x = action.StepData;
                    }
                    if (action.TypeOfLogicID == 10)
                    {
                        gameObject.Position.y = action.StepData;
                    }
                    if (action.TypeOfLogicID == 11)
                    {
                        gameObject.Rotation = action.StepData;
                    }
                }
            }
        }
        for (auto& gameObject : currentScene.gameObjects)
        {
            for (auto& action : gameObject.actions)
            {
                action.SetUpAllKeys();

                if (action.TypeOfActionID == 4)
                {
                    if (action.TypeOfLogicID == 0)
                    {

                        Message debug;
                        debug.text = "[Debug] " + action.PrintCode;
                        ConsoleMessages.push_back(debug);
                    }
                    if (action.TypeOfLogicID == 1)
                    {
                        gameObject.Position.x += action.StepData;
                    }
                    if (action.TypeOfLogicID == 2)
                    {
                        gameObject.Position.y += action.StepData;
                    }
                    if (action.TypeOfLogicID == 3)
                    {
                        gameObject.Scale.x += action.StepData;
                    }
                    if (action.TypeOfLogicID == 4)
                    {

                        gameObject.Scale.y += action.StepData;
                    }
                    if (action.TypeOfLogicID == 5)
                    {
                        gameObject.Rotation += action.StepData;
                    }
                    if (action.TypeOfLogicID == 6)
                    {
                        gameObject.color[0] = action.CodeColor[0];

                        gameObject.color[1] = action.CodeColor[1];

                        gameObject.color[2] = action.CodeColor[2];

                        gameObject.Opacity = action.CodeOpacity;
                    }
                    if (action.TypeOfLogicID == 7)
                    {
                        gameObject.Scale.x = action.StepData;
                    }
                    if (action.TypeOfLogicID == 8)
                    {
                        gameObject.Scale.y = action.StepData;
                    }
                    if (action.TypeOfLogicID == 9)
                    {
                        gameObject.Position.x = action.StepData;
                    }
                    if (action.TypeOfLogicID == 10)
                    {
                        gameObject.Position.y = action.StepData;
                    }
                    if (action.TypeOfLogicID == 11)
                    {
                        gameObject.Rotation = action.StepData;
                    }
                }
            }
        }
    }

    if (GameWindow == true)
    {
        GameView.setSize(700, 500);
        GameView.setCenter(MainCamera.Position);
        rt.create(700, 500);
        rt.setView(GameView);
        ImGuiWindowFlags flags;
        flags = ImGuiWindowFlags_MenuBar;
        ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(8, 0));
        ImGui::Begin("Game", nullptr, flags);

        ImGui::Image(rt, sf::Color::White);
        ImGui::PopStyleVar();
        ImGui::End();
    }

}


void Quixel::Editor::Editor::SceneHierarchy(sf::RenderTexture& rt)
{
    const auto deadline = std::chrono::high_resolution_clock::now() + std::chrono::seconds(1);
    ImGui::Begin("Hierarchy", nullptr, ImGuiWindowFlags_MenuBar);
    if (ImGui::BeginMenuBar())
    {
        if (ImGui::BeginMenu("File"))
        {
            if (ImGui::MenuItem("Save", NULL, nullptr))
            {
                for (auto& gameObject : currentScene.gameObjects)
                {
                    saveAndload.SaveGameObject(gameObject, "Game.qpk", currentScene.gameObjects);
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
            ImGui::EndMenu();
        }
        if (ImGui::BeginMenu("View"))
        {
            ImGui::MenuItem("Scene View", NULL, &SceneWindow);
            ImGui::MenuItem("Properties", NULL, &PropertiesWindow);
            ImGui::MenuItem("Console", NULL, &ConsoleWindow);
            ImGui::MenuItem("Game View", NULL, &GameWindow);
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
            const auto now = std::chrono::high_resolution_clock::now();
            Message InPlayModeMessage;
            InPlayModeMessage.text = "[info] In PlayMode";
            ConsoleMessages.push_back(InPlayModeMessage);
            gameObjectsForPlay.clear();
            for (auto& gameObject : currentScene.gameObjects)
            {
                gameObjectsForPlay.push_back(gameObject);
                for (auto& action : gameObject.actions)
                {
                    if (action.TypeOfActionID == 0)
                    {
                        if (action.TypeOfLogicID == 0)
                        {
                            if (now < deadline)
                            {
                                Message debug;
                                debug.text = "[Debug] " + action.PrintCode;
                                ConsoleMessages.push_back(debug);
                            }
                        }
                        if (action.TypeOfLogicID == 1)
                        {
                            if (now < deadline)
                            {
                                gameObject.Position.x += action.StepData;
                            }
                        }
                        if (action.TypeOfLogicID == 2)
                        {
                            if (now < deadline)
                            {
                                gameObject.Position.y += action.StepData;
                            }
                        }
                        if (action.TypeOfLogicID == 3)
                        {
                            if (now < deadline)
                            {
                                gameObject.Scale.x += action.StepData;
                            }
                        }
                        if (action.TypeOfLogicID == 4)
                        {
                            if (now < deadline)
                            {
                                gameObject.Scale.y += action.StepData;
                            }
                        }
                        if (action.TypeOfLogicID == 5)
                        {
                            if (now < deadline)
                            {
                                gameObject.Rotation += action.StepData;
                            }
                        }
                        if (action.TypeOfLogicID == 6)
                        {
                            if (now < deadline)
                            {
                                gameObject.color[0] = action.CodeColor[0];

                                gameObject.color[1] = action.CodeColor[1];

                                gameObject.color[2] = action.CodeColor[2];

                                gameObject.Opacity = action.CodeOpacity;
                            }
                        }
                        if (action.TypeOfLogicID == 7)
                        {
                            if (now < deadline)
                            {
                                gameObject.Scale.x = action.StepData;
                            }
                        }
                        if (action.TypeOfLogicID == 8)
                        {
                            if (now < deadline)
                            {
                                gameObject.Scale.y = action.StepData;
                            }
                        }
                        if (action.TypeOfLogicID == 9)
                        {
                            if (now < deadline)
                            {
                                gameObject.Position.x = action.StepData;
                            }
                        }
                        if (action.TypeOfLogicID == 10)
                        {
                            if (now < deadline)
                            {
                                gameObject.Position.y = action.StepData;
                            }
                        }
                        if (action.TypeOfLogicID == 11)
                        {
                            if (now < deadline)
                            {
                                gameObject.Rotation = action.StepData;
                            }
                        }
                    }
                }
            }
        }
    }
    if (IsPlaying == true)
    {

        if (ImGui::Button("Stop") && IsPlaying == true)
        {
            IsPlaying = false;
            currentScene.gameObjects.clear();
            for (auto& gameObject : gameObjectsForPlay)
            {
                currentScene.gameObjects.push_back(gameObject);
            }
        }
    }
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
            if (ImGui::Button("To bottom") && selectedGameObject->ID > 0)
            {
                std::swap(currentScene.gameObjects[selectedGameObject->ID], currentScene.gameObjects[selectedGameObject->ID - 1]);
                int ID = selectedGameObject->ID;
                selectedGameObject = &currentScene.gameObjects[ID];
            }
            ImGui::SameLine();
            if (ImGui::Button("To top") && selectedGameObject->ID < currentScene.gameObjects.size() - 1)
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
            ImGui::Separator();
            if (ImGui::CollapsingHeader("Actions"))
            {
                if (ImGui::Button("New Action"))
                {
                    BluePrints::Action ac;
                    selectedGameObject->actions.push_back(ac);
                }
                ImGui::Separator();
                for (size_t i = 0; i < selectedGameObject->actions.size(); i++) {
                    BluePrints::Action& object = selectedGameObject->actions[i];
                    //object.ID = i;
                    ImGui::PushID(i + "obj");
                    if (ImGui::Selectable(object.name.c_str(), false, ImGuiSelectableFlags_None, ImVec2(ImGui::GetWindowSize().x - 80, 20)))
                    {
                       // MainCamera.IsSelected = false;
                       selectedGameObject->selectedAction = &object;
                    }
                    ImGui::SameLine();
                    if (ImGui::Selectable("Remove")) {
                        selectedGameObject->actions.erase(selectedGameObject->actions.begin() + i);
                        i--;
                         selectedGameObject->selectedAction != &object;
                       // HasSaved = false;
                    }
                    ImGui::PopID();
                    ImGui::Separator();
                }
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

    // The node editor window
    ImGui::Begin("Actions");
    if (selectedGameObject != nullptr)
    {
        if (selectedGameObject->selectedAction != nullptr)
        {
            if (ImGui::CollapsingHeader("Settings"))
            {
                ImGui::InputText("##NameOfAction", &selectedGameObject->selectedAction->name);
                ImGui::Combo("##TypeOfAction", &selectedGameObject->selectedAction->TypeOfActionID, selectedGameObject->selectedAction->ActionTypes, IM_ARRAYSIZE(selectedGameObject->selectedAction->ActionTypes));
                if (selectedGameObject->selectedAction->TypeOfActionID == 1 || selectedGameObject->selectedAction->TypeOfActionID == 2 || selectedGameObject->selectedAction->TypeOfActionID == 3)
                {
                    ImGui::Combo("##TypeOfKey", &selectedGameObject->selectedAction->KeyID, selectedGameObject->selectedAction->KeyTypes, IM_ARRAYSIZE(selectedGameObject->selectedAction->KeyTypes));
                }
                ImGui::Separator();
                ImGui::Combo("##TypeOfLogic", &selectedGameObject->selectedAction->TypeOfLogicID, selectedGameObject->selectedAction->LogicTypes, IM_ARRAYSIZE(selectedGameObject->selectedAction->LogicTypes));

                if (selectedGameObject->selectedAction->TypeOfLogicID == 0)
                {
                    ImGui::InputText("##TextForPrint", &selectedGameObject->selectedAction->PrintCode);
                }
                if (selectedGameObject->selectedAction->TypeOfLogicID == 1 || selectedGameObject->selectedAction->TypeOfLogicID == 2 || selectedGameObject->selectedAction->TypeOfLogicID == 3  || selectedGameObject->selectedAction->TypeOfLogicID == 4 || selectedGameObject->selectedAction->TypeOfLogicID == 5 || selectedGameObject->selectedAction->TypeOfLogicID == 7 || selectedGameObject->selectedAction->TypeOfLogicID == 8 || selectedGameObject->selectedAction->TypeOfLogicID == 9 || selectedGameObject->selectedAction->TypeOfLogicID == 10)
                {
                    ImGui::SliderFloat("##Dataddd", &selectedGameObject->selectedAction->StepData, -10000, 1000);
                }
                if (selectedGameObject->selectedAction->TypeOfLogicID == 6) 
                {
                    ImGui::ColorEdit3("##ColorObject", selectedGameObject->selectedAction->CodeColor);
                    ImGui::DragFloat("##Opacity Of Object", &selectedGameObject->selectedAction->CodeOpacity, 1, 0.1, 0.1);
                }
            }
        }
    }
    ImGui::End();
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

