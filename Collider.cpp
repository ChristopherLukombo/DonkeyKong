#include "pch.h"
#include "Collider.h"
#include "EntityManager.h"


Collider::Collider()
{

}

Collider::~Collider()
{
}

bool Collider::checkCollisionWithMario(Mario mario, std::shared_ptr<Entity> object)
{
	sf::FloatRect playerBounds = mario.mSprite.getGlobalBounds();
	sf::FloatRect objectBounds = object->mSprite.getGlobalBounds();

	if (object->mType == EntityType::block) {

		if (playerBounds.intersects(objectBounds) == true)
		{
			//std::cout << "COLLIDE BLOCK" << std::endl;
			return true;
		}
		else
		{
			//std::cout << "DONT COLLIDE BLOCK" << std::endl;
			return false;
		}

	}

	if (object->mType == EntityType::ladder) {

		// allow to go above the uppper platform + climb closer to the ladder
		objectBounds.top -= 33;
		
		objectBounds.height += 5;
		objectBounds.left += 15;
		objectBounds.width -= 25;

		if (playerBounds.intersects(objectBounds) == true)
		{
			std::cout << "COLLIDE LADDER" << std::endl;
			return true;
		}
		else
		{
			std::cout << "DONT COLLIDE LADDER" << std::endl;
			return false;
		}
	}

	if (object->mType == EntityType::coin) {

		if (playerBounds.intersects(objectBounds) == true)
		{
			//std::cout << "COLLIDE BLOCK" << std::endl;
			object->mEnabled = false;
			return true;
		}
		else
		{
			//std::cout << "DONT COLLIDE BLOCK" << std::endl;
			return false;
		}

	}

	return false;
}

