#pragma once
#include <Graphics.hpp>

#include <imnodes.h>
namespace Quixel
{
	namespace Editor
	{
		struct Editor
		{
			void SceneViewPort(sf::RenderTexture& rt, sf::View& SceneView, ImVec2 Size);
			void GameViewPort(sf::RenderTexture& rt, sf::View& GameView, ImVec2 Size);
			void SceneHierarchy(sf::RenderTexture& rt);
			void ProperitesPanel();
			void BluePrintEditor();
			void DrawAll(sf::RenderTexture& rt1, sf::RenderTexture& rt2);
		};
	}
}