#include <vector>
#include "Camera.h"
#include <iostream>
#include <fstream>
#include <json.hpp>
#include <Editor/Blueprints.h>
#include <imgui.h>



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
			float Rotation = 0;
			bool Properties = false;
			float color[3] = { (float)255 / 255, (float)255 / 255, (float)255 / 255 };
			float Opacity = 255;
			bool UseLogic = false;
			std::string textureName;
			std::vector<SpriteRenderer> sprites;
			BluePrints::Action* selectedAction = nullptr;
			std::vector<BluePrints::Action> actions;

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
		struct Save_Load {
			void SaveGameObject(const Quixel::Scene::GameObject& object, const std::string& filename);
			void LoadGameObject(const std::string& filename, std::vector<GameObject> gameObjects);
		};
	}
}