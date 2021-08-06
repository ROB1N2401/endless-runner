#pragma once

#include <string>
#include "Sprite.h"
#include "Transform.h"

struct Image
{
	Sprite sprite;
	Transform transform;

    void Render();
};

class Layer
{
public:
	Layer(const float scrollRatio_in);
	Layer(const float scrollRatio_in, const std::string& texture_id_in, const std::string& spriteDataFileName_in);

	void Update(float baseSpeed_in);
	void Reset();
	void Render();

private:
	static const unsigned int m_duplicatesAmount = 3;
	const float m_scrollRatio;
	float m_trueWidth;
	Image m_images[m_duplicatesAmount];
};