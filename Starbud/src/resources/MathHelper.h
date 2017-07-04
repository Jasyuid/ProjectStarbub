#pragma once

#include <math.h>
#define PI 3.14159265358979323846

class Math
{
public:
	static float degToRad(float degrees)
	{
		return degrees * ((float)PI / 180.0f);
	}

	static float radToDeg(float radians)
	{
		return radians * (180.0f / (float)PI);
	}

};