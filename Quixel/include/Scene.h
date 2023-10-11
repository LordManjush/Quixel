#include <vector>
#include <string>
#include <iostream>
#include <Graphics.hpp>

namespace Quixel {
	namespace Scene
	{
		struct GameObject
		{
			int ID;
			std::string name;
			sf::CircleShape sprite;
			sf::Vector2f Position = {0, 0};
			sf::Vector2f Scale = {100, 100};
			float Rotation;
			float color[3] = { (float)204 / 255, (float)77 / 255, (float)5 / 255 };
			float Opacity = 100;
		};
		struct Window
		{
			sf::RenderWindow window;
		};
		struct Scene
		{
			int ID;
			std::vector<GameObject> gameObjects;
			void DrawScene(Window& window);
		};
		struct SceneManager
		{
			std::vector<Scene> scenes;
			void ChangeScene(int ID);
		};
	}
}