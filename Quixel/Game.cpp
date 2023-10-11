#include "Quixel.h"

Quixel::Scene::SceneManager sceneManager;
Quixel::Scene::Scene scene1;

Quixel::Scene::GameObject object;
Quixel::Scene::GameObject object2;
void Quixel::Start(Scene::Window& window)
{
	window.window.create(sf::VideoMode(500, 500), "Cool Game", sf::Style::Close);
	scene1.gameObjects.push_back(object);
	object2.Position.x = 150;
	scene1.gameObjects.push_back(object2);
}
void Quixel::Update(Scene::Window& window)
{


	scene1.DrawScene(window);

}

