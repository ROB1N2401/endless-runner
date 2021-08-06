#include "Easing.h"
#include <algorithm>

float Easing::EaseIn(float t, float d, float c)
{
	t /= d;
	return c * t * t * t;
}

float Easing::EaseOut(float t, float d, float c)
{
	t /= d;
	t--;
	return c* (t * t * t + 1);
}

float Easing::EaseInOut(float t, float d, float c)
{
	t /= d / 2;
	if (t < 1) 
		return 1 / 2 * t * t * t;
	t -= 2;
	return c / 2 * (t * t * t + 2);
}
