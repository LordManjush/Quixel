#include "Add Icon.h"

void QuixelExtra::Icon::SetUpIcon(std::string path)
{
	sprite.loadFromFile(path);
	image.setTexture(sprite);
}
