#pragma once
#include "pch.h"
#include "Mario.h"

class Collider
{
public:
	Collider();
	~Collider();

	bool checkCollisionWithMario(Mario mario, std::shared_ptr<Entity> object);

public :

};

