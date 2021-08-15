#pragma once

class Collider;

class CollisionManager
{
public:
	static bool CheckCollision(Collider *lhs, Collider *rhs);
};
