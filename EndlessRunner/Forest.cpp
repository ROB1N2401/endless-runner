#include "Forest.h"

Forest::Forest()
	: Entity("forest", "ForestSprite.txt")
{
	transform.SetScale(2.5f, 1.5f);
}

Forest::~Forest() {}
