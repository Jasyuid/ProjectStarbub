#include "Collisions.h"

Collisions::Side Collisions::pixelPerfectTest(const Entity& a, const Entity& b)
{
	//Rectangles around each entity
	sf::IntRect rectA = a.getTextureRect();
	rectA.width = (int)(rectA.width * a.getScale().x);
	rectA.height = (int)(rectA.height * a.getScale().y);
	rectA.left = (int)(a.getPosition().x - a.getOrigin().x);
	rectA.top = (int)(a.getPosition().y - a.getOrigin().y);
	sf::IntRect rectB = b.getTextureRect();
	rectB.width = (int)(rectB.width * b.getScale().x);
	rectB.height = (int)(rectB.height * b.getScale().y);
	rectB.left = (int)(b.getPosition().x - b.getOrigin().x);
	rectB.top = (int)(b.getPosition().y - b.getOrigin().y);

	sf::IntRect overlap;

	//Collision direction calculation
	if (rectA.intersects(rectB, overlap))
	{
		if (overlap.width > overlap.height)
		{
			return VERTICAL;
		}
		else
		{
			return HORIZONTAL;
		}
	}

	return NONE;
}
