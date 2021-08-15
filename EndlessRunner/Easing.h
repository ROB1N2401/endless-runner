/* 
This class is based on a cubic function. 
Function definitons were taken from www.gizma.com and simplified to meet the needs.
t stands for the current time, d for the easing duration, c for the desired end scale coefficient,
b for the starting point.
*/

class Easing
{
public:
	static float EaseOutCubic(float t, float d, float c);
	static float EaseOutBounce(float t, float d, float c, float b);
	static float EaseInOutBounce(float t, float d, float c, float b);
};