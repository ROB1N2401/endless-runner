#include "Animation.h"
#include "SpriteSheet.h"
#include <iostream>
#include <fstream>
#include <sstream>

Animation::Animation(const Uint32 animationSpeed_in) : m_animationSpeed(animationSpeed_in)
{
	lastTimeUpdated = 0;
	currentFrame = 0;
	framesAmount = 0;
}

Animation::Animation(const Uint32 animationSpeed_in, const std::string& texture_id_in, const std::string& animationName_in) : 
	m_animationSpeed(animationSpeed_in)
{
	currentFrame = 0;
	lastTimeUpdated = 0;

	std::ifstream stream_;
	stream_.open(animationName_in);

	std::string spritesheetFileName;
	getline(stream_, spritesheetFileName);
	SpriteSheet spritesheet = ReadSpritesheet(texture_id_in, spritesheetFileName);

	std::string frame_info_;
	std::getline(stream_, frame_info_);
	std::stringstream ss(frame_info_);
	std::string frame_;
	std::vector<int> frames_;

	while (ss >> frame_) frames_.push_back(stoi(frame_));
	for (int i : frames_)
	{
		frames.push_back(spritesheet.sprites[i]);
	}
	framesAmount = frames.size();
}

void Animation::SwitchFrames()
{
	currentFrame += 1;

	if (currentFrame == framesAmount)
		currentFrame = 0;
}

void Animation::Update()
{
	Uint32 ticks = SDL_GetTicks();
	Uint32 currentTime = ticks / m_animationSpeed;

	if (currentTime > lastTimeUpdated)
	{
		SwitchFrames();

		lastTimeUpdated = currentTime;
	}
}

/*
switch (m_animationType)
	{
		case Type::Single:
			if (isFirstPlayback && currentFrame == framesAmount - 1)
				isFirstPlayback = false;
			break;

		case Type::Loop:
			if (currentFrame == framesAmount - 1)
				currentFrame = 0;
			break;

		case Type::Pingpong:
			if (currentFrame == 0 || currentFrame == framesAmount - 1)
				direction = -direction;
			break;
	}
*/