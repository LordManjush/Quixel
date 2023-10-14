#include <vector>
#include "Camera.h"
#include <iostream>


namespace Quixel {
	namespace Scene
	{
		struct SpriteRenderer
		{
			std::string path;
			sf::Image img;
			sf::Texture texture;
		};

		struct GameObject
		{
			sf::Sprite shape;
			std::string name = "NewGameObject";
			int ID = 0;
			sf::Vector2f Position = { 500, 200 };
			sf::Vector2f Scale = { 1, 1 };
			float Rotation = 90;
			bool Properties = false;
			float color[3] = { (float)204 / 255, (float)77 / 255, (float)5 / 255 };
			float Opacity = 255;
			std::string textureName;
			std::vector<SpriteRenderer> sprites;
		};
		void DrawAll(sf::RenderTexture& rt, GameObject& gameObject);
		struct Scene
		{
			int ID;
			std::vector<GameObject> gameObjects;
		};
		struct SceneManager
		{
			std::vector<Scene> scenes;
			void ChangeScene(int ID);
		};
	}
}