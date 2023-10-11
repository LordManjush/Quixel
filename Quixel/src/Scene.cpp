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
		window.window.draw(gameObject.sprite);
	}
}

