#pragma once

#include <string>
#include <vector>
#include "Sprite.h"
#include "SDL.h"

struct SpriteSheet
{
	std::string imageFileName;
	std::vector<Sprite> sprites;
};

SpriteSheet ReadSpritesheet(const std::string& texture_id_in, const std::string& spritesheetName_in);