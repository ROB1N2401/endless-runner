#pragma once

#include <string>
#include <vector>
#include "Spritesheet.h"
#include "SDL.h"

class Animation
{
public:
	Animation(const Uint32 animationSpeed_in);
	Animation(const Uint32 animationSpeed_in, const std::string& texture_id_in, const std::string& animationName_in);

	void Update();
	void SwitchFrames();
	
	std::vector<Sprite> frames;
	Uint32 currentFrame;
	
private:
	const Uint32 m_animationSpeed; //Higher the number, slower the animation is. 
	Uint32 lastTimeUpdated; 
	int framesAmount;
	
};

