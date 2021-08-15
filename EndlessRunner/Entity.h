#pragma once
#include "Collider.h"
#include "Animation.h"
#include "Transform.h"

//A base for the most of other structes 

class Entity
{
public:
	Entity();
	Entity(const std::string& id_in, const std::string& spritesheetName_in);

	Animation* animation;
	Collider* collider;
	Transform transform;

	virtual void Render();
	virtual void Reset() = 0;
	virtual void Update(float dt) = 0;
};