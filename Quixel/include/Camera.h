#pragma once
#include <Graphics.hpp>
#include <string>
namespace Quixel 
{
	namespace Scene
	{
		struct Camera
		{
			sf::Vector2f Position = { 350, 150 };
			bool IsSelected = false;
			sf::Vector2f size = { 500, 500 };
			float color[3] = { (float)255 / 255, (float)255 / 255, (float)255 / 255 };
			float Opacity = 255;
			std::string name = "Main Camera";
		};
	}
}