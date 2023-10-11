#include "Add Icon.h"

void Quixel::Icon::SetUpIcon(std::string path)
{
	sprite.loadFromFile(path);
	image.setTexture(sprite);
}
