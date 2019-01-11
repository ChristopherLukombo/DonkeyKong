#include "pch.h"
#include "Collider.h"


Collider::Collider(sf::Sprite & body, sf::Vector2u size) :
	body(body), size(size)
{
}

Collider::~Collider()
{
}

bool Collider::checkCollision(Collider & other, float push)
{
	sf::Vector2f otherPosition = other.GetPosition();
	sf::Vector2f otherHalfSize = other.GetHalfSize();
	sf::Vector2f bodyPosition = GetPosition();
	sf::Vector2f bodyHalfSize = GetHalfSize();

	float deltaX = otherPosition.x - bodyPosition.x; // DeltaX is the disrance between the x of the two object
	float deltaY = otherPosition.y - bodyPosition.y; // DeltaY is the distance between the y of the two object

	// abs(delta) - 
	float intersectX = abs(deltaX) - (otherHalfSize.x + bodyHalfSize.x);
	float intersectY = abs(deltaY) - (otherHalfSize.y + bodyHalfSize.y);

	if (intersectX < 0.0f && intersectY < 0.0f)
	{
		push = std::min(std::max(push, 0.0f), 1.0f);

		if (intersectX > intersectY)
		{
			// x axis
			if (deltaX > 0.0f)
			{
				Move(intersectX * (1.0f - push), 0.0f);
				other.Move(-intersectX * push, 0.0f);
			}
			else
			{
				Move(-intersectX * (1.0f - push), 0.0f);
				other.Move(intersectX * push, 0.0f);
			}
		}
		else
		{
			// y axis
			if (deltaY > 0.0f)
			{
				Move(0.0f, intersectY * (1.0f - push));
				other.Move(0.0f, -intersectY * push);
			}
			else
			{
				Move(0.0f , -intersectY * (1.0f - push));
				other.Move(0.0f, intersectY * push);
			}
		}

		return true;
	}

	return false;
}
