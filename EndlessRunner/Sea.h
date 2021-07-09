#pragma once

#include "Entity.h"

struct Sea : public Entity
{
	Sea();
	~Sea();

	virtual void Render() final;
};