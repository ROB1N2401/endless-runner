#include "Animation.h"
#include "SpriteSheet.h"
#include <iostream>
#include <fstream>
#include <sstream>

Animation::Animation(const Uint32 animationSpeed_in) : m_animationSpeed(animationSpeed_in)
{
	m_lastTimeUpdated = 0;
	m_framesAmount = 0;
	currentFrame = 0;
}

Animation::Animation(const Uint32 animationSpeed_in, const std::string& texture_id_in, const std::string& animationName_in) : 
	m_animationSpeed(animationSpeed_in)
{
	currentFrame = 0;
	m_lastTimeUpdated = 0;

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
		frames.push_back(spritesheet.sprites[i]);
	m_framesAmount = static_cast<int>(frames.size());
}

void Animation::SwitchFrames()
{
	currentFrame += 1;

	if (currentFrame == m_framesAmount)
		currentFrame = 0;
}

void Animation::Update()
{
	Uint32 ticks = SDL_GetTicks();
	Uint32 currentTime = ticks / m_animationSpeed;

	if (currentTime > m_lastTimeUpdated)
	{
		SwitchFrames();
		m_lastTimeUpdated = currentTime;
	}
}