#include "Entity.h"

Entity::Entity() {}

Entity::Entity(const std::string& id_in, const std::string& spritesheetName_in)
	: sprite(id_in, spritesheetName_in)
{
}

void Entity::Render()
{
	RenderManager::Instance()->Render(sprite, transform);
}

void Entity::Update(float dt)
{

}
