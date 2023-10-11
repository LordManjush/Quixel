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
			sf::Vector2f Position;
			sf::Vector2f Scale;
			float Rotation;
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