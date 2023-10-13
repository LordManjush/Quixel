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

void Quixel::Scene::DrawAll(sf::RenderTexture& rt, GameObject& gameObject)
{
	gameObject.shape.setPosition(sf::Vector2f(gameObject.Position.x, gameObject.Position.y));
	gameObject.shape.setSize(sf::Vector2f(gameObject.Scale.x, gameObject.Scale.y));
	gameObject.shape.setRotation(gameObject.Rotation);
	gameObject.shape.setFillColor(sf::Color((int)(gameObject.color[0] * 255),
		(int)(gameObject.color[1] * 255),
		(int)(gameObject.color[2] * 255),
		gameObject.Opacity));
	gameObject.shape.setOutlineColor(sf::Color((int)(gameObject.BorderColor[0] * 255),
		(int)(gameObject.BorderColor[1] * 255),
		(int)(gameObject.BorderColor[2] * 255),
		gameObject.BorderOpacity));
	gameObject.shape.setOutlineThickness(gameObject.BorderThickness);

	rt.draw(gameObject.shape);
}


