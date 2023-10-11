#pragma once
#include <Graphics.hpp>
namespace Quixel
{
	struct Icon
	{
	private:
		sf::Texture sprite;
	public:
		sf::Sprite image;
		void SetUpIcon(std::string path);
	};
}


