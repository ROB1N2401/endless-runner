#pragma once
#include "Entity.h"

class Enemy : public Entity
{
public:
	Enemy();
	~Enemy();

	virtual void Reset() = 0;
	void Update(const float dt);

protected:
	int m_minRange, m_maxRange;
	Helium::Vector2 m_velocity;

	const float Randomize();
};

class Opossum : public Enemy
{
public:
	Opossum();

	virtual void Reset() override;
};

class Eagle : public Enemy
{
public:
	Eagle();

	virtual void Reset() override;
};