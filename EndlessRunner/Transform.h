#pragma once
#include "HeliumMath.h"

struct Transform
{
public:
	Transform();
	~Transform();

	void SetPosition(const float x, const float y);
	void SetScale(const float x, const float y);

	void ChangePosition(const float x, const float y);
	void ChangeScale(const float x, const float y);

	Helium::Vector2 GetPosition() const;
	Helium::Vector2 GetScale() const;

private:
	Helium::Vector2 position;
	Helium::Vector2 scale;
};