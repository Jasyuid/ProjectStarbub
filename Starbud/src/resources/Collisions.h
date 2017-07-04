#pragma once

#include "../entities/Entity.h"
#include <SFML/Graphics.hpp>

class Entity;

class Collisions
{
public:
	//Collision states
	enum Side {
		NONE, HORIZONTAL, VERTICAL
	};

	static Side pixelPerfectTest(const Entity& a, const Entity& b); //Determines if sprites of two entities overlap

};