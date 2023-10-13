#include <vector>
#include "Camera.h"

#include <iostream>


namespace Quixel {
	namespace Scene
	{
		struct GameObject
		{
			sf::RectangleShape shape;
			std::string name = "NewGameObject";
			int ID = 0;
			sf::Vector2f Position = { 400, 100 };
			sf::Vector2f Scale = { 50, 50 };
			float Rotation = 90;
			bool Properties = false;
			float color[3] = { (float)204 / 255, (float)77 / 255, (float)5 / 255 };
			float Opacity = 255;
			float BorderColor[3] = { (float)204 / 255, (float)77 / 255, (float)5 / 255 };
			float BorderOpacity = 255;
			float BorderThickness = 0;
			bool IsSelected = false;
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