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
			std::string name = "Main Camera";
		};
	}
}