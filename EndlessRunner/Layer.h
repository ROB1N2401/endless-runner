#pragma once
#include <string>
#include "Sprite.h"
#include "Transform.h"

struct Image
{
    void Render();
	
	Sprite sprite;
	Transform transform;
};

class Layer
{
public:
	Layer();
	Layer(const float scrollRatio_in, const std::string& texture_id_in, const std::string& spriteDataFileName_in);

private:
	friend class Parallax;

	static const unsigned int m_duplicatesAmount = 3;
	const float m_baseScale;
	const float m_scrollRatio;
	float m_trueWidth;
	Image m_images[m_duplicatesAmount];

	void Update(float baseSpeed_in);
	void Reset();
	void Render();
};