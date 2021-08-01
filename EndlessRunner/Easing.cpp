#include "Easing.h"
#include <algorithm>

float Easing::EaseIn(float t, float d)
{
	t /= d;
	return t * t * t;
}

float Easing::EaseOut(float t, float d)
{
	t /= d;
	t--;
	return t * t * t + 1;
}

float Easing::EaseInOut(float t, float d)
{
	t /= d / 2;
	if (t < 1) 
		return 1 / 2 * t * t * t;
	t -= 2;
	return 1 / 2 * (t * t * t + 2);
}
