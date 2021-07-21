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

class Animation
{
public:
	Animation();
	Animation(const std::string& texture_id_in, const std::string& animationName_in);

	void Update();

	//In the animation .txt files: 1 for single, 2 for loop, 3 for pingpong
	std::vector<Sprite> frames;
	std::string spritesheetFileName;
	SpriteSheet spritesheet;
	Uint32 currentFrame;
	Uint32 lastTimeUpdated; 
	const Uint32 animationSpeed = 100; //Higher the number, slower the animation is. 
	bool isFirstPlayback; //Todo: find a better way to handle single animations as this variable is redundant in other cases
	int direction; //flips the direction of animation's playback. Is either 1 or -1
	int framesAmount;
	
private:
	Type animationType = Type::Single;
	void SwitchFrames();
};

