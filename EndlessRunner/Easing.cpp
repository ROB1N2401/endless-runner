#include "Easing.h"
#include <algorithm>

float Easing::EaseInCubic(float t, float d, float c)
{
	t /= d;
	return c * t * t * t;
}

float Easing::EaseOutCubic(float t, float d, float c)
{
	t /= d;
	t--;
	return c* (t * t * t + 1);
}

float Easing::EaseInOutCubic(float t, float d, float c)
{
	t /= d / 2;
	if (t < 1) 
		return 1 / 2 * t * t * t;
	t -= 2;
	return c / 2 * (t * t * t + 2);
}

float Easing::EaseOutBounce(float t, float d, float c, float b)
{

	if (t < 1 / d) {
		return c * t * t + b;
	}
	else if (t < 2 / d) {
		return c * (t -= 1.5 / d) * t + 0.75;
	}
	else if (t < 2.5 / d) {
		return c * (t -= 2.25 / d) * t + 0.9375;
	}
	else {
		return c * (t -= 2.625 / d) * t + 0.984375;
	}
}

float Easing::EaseInOutBounce(float t, float d, float c, float b)
{
	t /= d;

	if (t < 0.5) 
		return (1 - EaseOutBounce(1 - 2 * t, d, c, b)) / 2;
	
	else if (0.5 < t < 1) 
		return (1 + EaseOutBounce(2 * t - 1, d, c, b)) / 2;
	
	else if (1 < t < 1.5) 
		return (1 + EaseOutBounce(1 - 2 * (t - 1), d, c, b)) / 2;
	
	else 
		return (1 - EaseOutBounce(- 1 + 2 * (t - 1), d, c, b)) / 2;
}
