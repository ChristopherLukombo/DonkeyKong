#pragma once
#include "pch.h"
#include "Entity.h"


class Player : public Entity
{
public:
	Player();
	~Player();

	void handlePlayerInput(sf::Keyboard::Key key, bool isPressed);
public :
	static const float PlayerSpeed;

	bool _movingUp;
	bool _movingDown;
	bool _movingRight;
	bool _movingLeft; 
	bool _jumping;
	bool _onLadder;
	bool _onBlock;
};

