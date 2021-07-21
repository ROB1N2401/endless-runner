#pragma once

#include "Entity.h"
#include "Animation.h"

class Player : public Entity
{
public:
	Player();
	~Player();

	virtual void Render() final;
	virtual void Update(float dt) final;

private:
	Animation* m_animation;
};