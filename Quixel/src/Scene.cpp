#include <Quixel.h>
void Quixel::Scene::SceneManager::ChangeScene(int ID)
{
	for (auto& scene : scenes)
	{
		if (scene.ID == ID)
		{
			printf("OK");
		}
	}
}

void Quixel::Scene::Scene::DrawScene(Window& window)
{
	for (auto& gameObject : gameObjects)
	{
		gameObject.sprite.setPosition(gameObject.Position);
		gameObject.sprite.setRadius(gameObject.Scale.x);
		gameObject.sprite.setFillColor(sf::Color((int)(gameObject.color[0] * 255),
			(int)(gameObject.color[1] * 255),
			(int)(gameObject.color[2] * 255),
			gameObject.Opacity));
		window.window.draw(gameObject.sprite);
	}
}

