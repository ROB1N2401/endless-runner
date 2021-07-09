#include "SpriteSheet.h"
#include "Animation.h"
#include <iostream>
#include <fstream>
#include <sstream>

Animation::Animation()
{

}

Animation::Animation(const std::string& animationName_in)
{
	std::ifstream stream_;
	stream_.open(animationName_in);
	Animation animation_;

	getline(stream_, spritesheetFileName);
	spritesheet = ReadSpritesheet(spritesheetFileName);

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

Animation UpdateSprite(Animation& animation_in)
{
	if (animation_in.animationType == Type::Single)
	{
		if (animation_in.timesPlayed == 0)
		{
			animation_in.currentFrame += animation_in.direction;

			if (animation_in.currentFrame == animation_in.framesAmount - 1)
			{
				animation_in.currentFrame = 0;
				animation_in.timesPlayed++;
			}
		}
	}

	else if (animation_in.animationType == Type::Loop)
	{
		animation_in.currentFrame += animation_in.direction;

		if (animation_in.currentFrame == animation_in.framesAmount - 1)
		{
			animation_in.currentFrame = 0;
			animation_in.timesPlayed++;
		}
	}

	else if (animation_in.animationType == Type::Pingpong)
	{
		animation_in.currentFrame += animation_in.direction;

		if (animation_in.currentFrame == 0 || animation_in.currentFrame == animation_in.framesAmount - 1)
		{
			animation_in.timesPlayed++;
			animation_in.direction = -animation_in.direction;
		}
	}

	return animation_in;
};

