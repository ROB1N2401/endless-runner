#pragma once
#include "HeliumMath.h"

enum class PivotPoint
{
	DEFAULT, //Top left corner
	CENTERED
};

struct Transform
{
public:
	PivotPoint pivotPoint;

	Transform();
	Transform(PivotPoint pivot_in);
	~Transform();

	void SetPosition(Helium::Vector2& vector);
	void SetPosition(const float x, const float y);
	void SetScale(const float c);
	void SetScale(const float x, const float y);
	void SetRotation(const float c);

	void ChangePosition(Helium::Vector2& vector);
	void ChangePosition(const float x, const float y);
	void ChangeScale(const float x, const float y);

	Helium::Vector2 GetPosition() const;
	Helium::Vector2 GetScale() const;
	float GetRotation() const;

private:
	Helium::Vector2 position;
	Helium::Vector2 scale;
	float rotation;
};
