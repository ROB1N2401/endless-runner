#pragma once

#include "Entity.h"

class Enemy : public Entity
{
public:
	Enemy();
	~Enemy();

	virtual void Update(const float dt) final;

protected:
	int Randomize();

	int m_minRange, m_maxRange;
	Helium::Vector2 m_velocity;
};

class Opossum : public Enemy
{
public:
	Opossum();
};

class Eagle : public Enemy
{
public:
	Eagle();
};