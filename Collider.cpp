#include "pch.h"
#include "Collider.h"
#include "EntityManager.h"


/*Collider::Collider(sf::Sprite & body, sf::Vector2u size) :
	body(body), size(size)
{
}*/

Collider::Collider()
{

}

Collider::~Collider()
{
}

bool Collider::checkCollisionWithMario(Mario mario, std::shared_ptr<Entity> object)
{
	sf::FloatRect playerBounds = mario.m_sprite.getGlobalBounds();
	sf::FloatRect objectBounds = object->m_sprite.getGlobalBounds();

	if (object->m_type == EntityType::block) {

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

	if (object->m_type == EntityType::ladder) {

		// allow to go above the uppper platform + climb closer to the ladder
		objectBounds.top -= 33;
		objectBounds.height += 33;
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

	return false;
}

