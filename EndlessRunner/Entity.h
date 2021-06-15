#pragma once
#include "RenderManager.h"
#include "Sprite.h"
#include "Transform.h"

//A base for the most of other structes 

struct Entity
{
	Sprite sprite;
	Transform transform;

	//virtual void Initialize();
	//virtual void Render(RenderManager& renderManager);
	//virtual void Update(float dt);
};