#include "Sea.h"

Sea::Sea()
	: Entity("sea", "SeaSprite.txt")
{
	transform.SetScale(2.5f, 1.5f);
}

Sea::~Sea() {}

void Sea::Render()
{
	RenderManager::Instance()->Render(sprite, transform);
}
