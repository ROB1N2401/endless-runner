#pragma once
#include <vector>
#include "RenderManager.h"
#include "Sprite.h"
#include "Transform.h"

//A base for the most of other structes 

class Entity
{
public:
	Entity();
	Entity(const std::string& id_in, const std::string& spritesheetName_in);

	//virtual void Initialize();
	virtual void Render();
	virtual void Update(float dt);

	Sprite sprite;
	Transform transform;
};