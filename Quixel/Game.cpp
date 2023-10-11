#include "Quixel.h"

Quixel::Scene::SceneManager sceneManager;
Quixel::Scene::Scene scene1;
void Quixel::Start()
{
	
}
void Quixel::Update()
{
	if (Quixel::InputSystem::IsKeyPressed(ImGuiKey_A))
	{
		printf("Shit");
	}
}

