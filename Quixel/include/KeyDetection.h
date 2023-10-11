#pragma once
#include <imgui.h>
namespace Quixel
{
	namespace InputSystem
	{
		bool IsKeyPressed(ImGuiKey key);
		bool IsKeyReleased(ImGuiKey key);
		bool IsMouseClicked(ImGuiMouseButton button);
	}
}