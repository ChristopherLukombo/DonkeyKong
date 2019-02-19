#pragma once
#include "pch.h"
#include "Entity.h"


class Player : public Entity
{
public:
	Player();
	~Player();

public :
	bool _movingUp;
	bool _movingDown;
	bool _movingRight;
	bool _movingLeft; 
	bool _jumping;
	bool _onLadder;
	bool _onBlock;
};

