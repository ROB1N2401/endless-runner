#include "Easing.h"

float Easing::EaseOutCubic(float t, float d, float c)
{
	t /= d;
	t--;
	return c* (t * t * t + 1);
}

float Easing::EaseOutBounce(float t, float d, float c, float b)
{

	if (t < 1 / d) {
		return c * t * t + b;
	}
	else if (t < 2 / d) {
		return c * (t -= 1.5f / d) * t + 0.75f;
	}
	else if (t < 2.5 / d) {
		return c * (t -= 2.25f / d) * t + 0.9375f;
	}
	else {
		return c * (t -= 2.625f / d) * t + 0.984375f;
	}
}

float Easing::EaseInOutBounce(float t, float d, float c, float b)
{
	t /= d;

	if (t < 0.5) 
		return (1 - EaseOutBounce(1 - 2 * t, d, c, b)) / 2;
	else 
		return (1 + EaseOutBounce(2 * t - 1, d, c, b)) / 2;
}
