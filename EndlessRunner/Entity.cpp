#include "Entity.h"

Entity::Entity() : animation(), collider() {}

Entity::Entity(const std::string& id_in, const std::string& spritesheetName_in)
	: animation(new Animation(100, id_in, spritesheetName_in)), collider(new Collider()) {}

void Entity::Render()
{
	RenderManager::Instance()->Render(animation->frames[animation->currentFrame], transform);
	//RenderManager::Instance()->Render(&collider->rect);
}
