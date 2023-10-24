#pragma once
#include <Graphics.hpp>

namespace Quixel
{
	namespace Editor
	{

		struct Editor
		{
			void InitEditor();
			void SceneViewPort(sf::RenderTexture& rt, sf::View& SceneView);
			void GameViewPort(sf::RenderTexture& rt, sf::View& GameView);
			void SceneHierarchy(sf::RenderTexture& rt);
			void ProperitesPanel();
			void BluePrintEditor();
			void Console();
			void DrawAll(sf::RenderTexture& rt1, sf::RenderTexture& rt2);

		};
	}
}
