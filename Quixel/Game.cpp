#include "Quixel.h"

Quixel::Scene::SceneManager sceneManager;
Quixel::Scene::Scene scene1;

Quixel::Scene::GameObject object;

void Quixel::Start(Scene::Window& window)
{
	window.window.create(sf::VideoMode(200, 300), "Cool Game");
}
void Quixel::Update(Scene::Window& window)
{
	scene1.DrawScene(window);
	if (Quixel::InputSystem::IsKeyPressed(ImGuiKey_A))
	{
		printf("Shit");
	}



	window.window.clear(sf::Color(255, 0,0, 255));
}

