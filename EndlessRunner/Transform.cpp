#include "Transform.h"

Transform::Transform()
{
	pivotPoint = PivotPoint::DEFAULT;
	position = Helium::Vector2(0.0f, 0.0f);
	scale = Helium::Vector2(1.0f, 1.0f);
	rotation = 0.0f;
}

Transform::Transform(PivotPoint pivot_in)
{
	pivotPoint = pivot_in;
	position = Helium::Vector2(0.0f, 0.0f);
	scale = Helium::Vector2(1.0f, 1.0f);
	rotation = 0.0f;
}

Transform::~Transform() {}

void Transform::SetPosition(Helium::Vector2& vector) { position = vector; }

void Transform::SetPosition(const float x, const float y)
{
	position.x_ = x;
	position.y_ = y;
}

void Transform::SetScale(const float c)
{
	scale.x_ = c;
	scale.y_ = c;
}

void Transform::SetScale(const float x, const float y)
{
	scale.x_ = x;
	scale.y_ = y;
}

void Transform::SetRotation(const float c) { rotation = c; }

void Transform::ChangePosition(Helium::Vector2& vector) { position = position + vector; }

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

Helium::Vector2 Transform::GetPosition() const { return position; }

Helium::Vector2 Transform::GetScale() const { return scale; }

float Transform::GetRotation() const { return rotation; }
