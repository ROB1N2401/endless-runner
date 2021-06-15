#pragma once

#include <string>
#include <vector>
#include "Spritesheet.h"
#include "SDL.h"

enum class Type 
{ 
	Single, 
	Pingpong, 
	Loop 
};

struct Animation
{
	Animation();
	Animation(std::string animationName_in);

	//In the animation .txt files: 1 for single, 2 for loop, 3 for pingpong
	std::vector<Sprite> frames;
	std::string spritesheetFileName;
	SpriteSheet spritesheet;
	Uint32 currentFrame = 0;
	int direction = 1;
	int timesPlayed = 0;
	int framesAmount = 0;
	
	Type animationType = Type::Single;
};

Animation UpdateSprite(Animation animation_in);