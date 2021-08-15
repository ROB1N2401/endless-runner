#pragma once
#include <string>
#include <vector>
#include "Sprite.h"

struct SpriteSheet { std::vector<Sprite> sprites; };

SpriteSheet ReadSpritesheet(const std::string& texture_id_in, const std::string& spritesheetName_in);