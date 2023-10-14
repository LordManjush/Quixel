#include "SpriteRenderer.h"
#include <imgui.h>
#include <ImGuiFileDialog.h>


std::string spriteName, spritePath;
void Quixel::Compoent::SpriteRenderer(Quixel::Scene::GameObject* selectedGameObject)
{
	if (ImGuiFileDialog::Instance()->Display("SelectTexture"))
	{
		// action if OK
		if (ImGuiFileDialog::Instance()->IsOk())
		{
			spriteName = ImGuiFileDialog::Instance()->GetCurrentFileName();
			spritePath = ImGuiFileDialog::Instance()->GetFilePathName();
			Quixel::Scene::SpriteRenderer newSpriteRenderer;
			newSpriteRenderer.path = spritePath;
			newSpriteRenderer.texture.loadFromFile(newSpriteRenderer.path);
			selectedGameObject->sprites.clear();
			selectedGameObject->sprites.push_back(newSpriteRenderer);
			selectedGameObject->textureName = spriteName;

		}
		// close
		ImGuiFileDialog::Instance()->Close();

		ImGui::CloseCurrentPopup();

	}
	if (ImGui::Button("Add Image"))
	{
		ImGuiFileDialog::Instance()->OpenDialog("SelectTexture", "Select Sprite", ".png, .svg, .jpeg", "./ ");
	}
	ImGui::Text(selectedGameObject->textureName.c_str());
}
