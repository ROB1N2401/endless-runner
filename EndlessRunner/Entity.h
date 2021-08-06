#pragma once
#include <vector>
#include "RenderManager.h"
#include "Collider.h"
#include "Animation.h"
#include "Transform.h"

//A base for the most of other structes 

class Entity
{
public:
	Entity();
	Entity(const std::string& id_in, const std::string& spritesheetName_in);

	virtual void Render();
	virtual void Reset() = 0;
	virtual void Update(float dt) = 0;

	Animation* animation;
	Collider* collider;
	Transform transform;
};