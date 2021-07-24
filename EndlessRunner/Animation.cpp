#include "SpriteSheet.h"
#include "Animation.h"
#include <iostream>
#include <fstream>
#include <sstream>

Animation::Animation()
{
	isFirstPlayback = true;
	lastTimeUpdated = 0;
	currentFrame = 0;
	framesAmount = 0;
	direction = 1;
}

Animation::Animation(const std::string& texture_id_in, const std::string& animationName_in)
{
	isFirstPlayback = true;
	currentFrame = 0;
	lastTimeUpdated = 0;
	direction = 1;

	std::ifstream stream_;
	stream_.open(animationName_in);
	Animation animation_;

	getline(stream_, spritesheetFileName);
	spritesheet = ReadSpritesheet(texture_id_in, spritesheetFileName);

	std::string type_info_;
	std::getline(stream_, type_info_);
	int intType = std::stoi(type_info_);

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


	switch (intType)
	{
	case 1: animationType = Type::Single;
		break;
	case 2: animationType = Type::Loop;
		break;
	case 3: animationType = Type::Pingpong;
		break;
	default:
		std::cout << "ERROR: Incorrect animation type supplied";
	}
}

void Animation::SwitchFrames()
{
	currentFrame += direction;

	switch (animationType)
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
}

void Animation::Update()
{
	Uint32 ticks = SDL_GetTicks();
	Uint32 currentTime = ticks / animationSpeed;

	if (currentTime > lastTimeUpdated)
	{
		SwitchFrames();

		lastTimeUpdated = currentTime;
	}
}

