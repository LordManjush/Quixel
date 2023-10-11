#include "KeyDetection.h"
#include <imgui.h>

bool Quixel::InputSystem::IsKeyPressed(ImGuiKey key)
{
    return ImGui::IsKeyPressed(key);
}
bool Quixel::InputSystem::IsKeyReleased(ImGuiKey key)
{
    return ImGui::IsKeyReleased(key);
}
bool Quixel::InputSystem::IsMouseClicked(ImGuiMouseButton button)
{
    return ImGui::IsMouseClicked(button);
}
