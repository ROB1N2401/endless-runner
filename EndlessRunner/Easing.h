#pragma once

/* 
This class is based on a cubic function. 
Function definitons were taken from www.gizma.com and simplified to meet the needs.
t stands for the current time, d for the easing duration, c for the desired end scale coefficient.
*/

class Easing
{
public:
	static float EaseIn(float t, float d, float c);
	static float EaseOut(float t, float d, float c);
	static float EaseInOut(float t, float d, float c);
};