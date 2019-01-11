#pragma once
#include "pch.h"

class Collider
{
public:
	Collider(sf::Sprite& body, sf::Vector2u size);
	~Collider();

	void Move(float dx, float dy) { body.move(dx, dy); } //deltX && deltaY

	bool checkCollision(Collider & other, float push); // if we want to push object should be positive
	sf::Vector2f GetPosition() { return body.getPosition(); }
	sf::Vector2f GetHalfSize() { return size / 2.0f; }

public :
	sf::Sprite& body;
	sf::Vector2f size;

};

