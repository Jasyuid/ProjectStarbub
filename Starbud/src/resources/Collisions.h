#pragma once

#include "../entities/Entity.h"
#include <SFML/Graphics.hpp>

#define COL_NONE 0
#define COL_TOP 1
#define COL_BOTTOM 2
#define COL_LEFT 3
#define COL_RIGHT 4

class Entity;

class Collisions
{
public:
	static int pixelPerfectTest(const Entity& a, const Entity& b); //Determines if sprites of two entities overlap

};