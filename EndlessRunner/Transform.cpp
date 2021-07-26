#include "Transform.h"

Transform::Transform()
{
	position = Helium::Vector2(0.0f, 0.0f);
	scale = Helium::Vector2(1.0f, 1.0f);
}

Transform::~Transform() {}

void Transform::SetPosition(const float x, const float y)
{
	position.x_ = x;
	position.y_ = y;
}

void Transform::SetScale(const float x, const float y)
{
	scale.x_ = x;
	scale.y_ = y;
}

void Transform::ChangePosition(Helium::Vector2& vector)
{
	position = position + vector;
}

void Transform::ChangePosition(const float x, const float y)
{
	position.x_ += x;
	position.y_ += y;
}

void Transform::ChangeScale(const float x, const float y)
{
	scale.x_ = +x;
	scale.y_ = +y;
}

Helium::Vector2 Transform::GetPosition() const
{
	return position;
}

Helium::Vector2 Transform::GetScale() const
{
	return scale;
}
