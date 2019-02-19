#include "pch.h"
#include "Player.h"


Player::Player() :
	_movingUp(false), _movingDown(false), _movingLeft(false), _movingRight(false), _jumping(false), _onBlock(false), _onLadder(false)
{
}


Player::~Player()
{
}
