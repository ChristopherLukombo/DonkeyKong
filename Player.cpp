#include "pch.h"
#include "Player.h"

const float Player::PlayerSpeed = 150.f;


Player::Player() :
	_movingUp(false), _movingDown(false), _movingLeft(false), _movingRight(false), _jumping(false), _onBlock(false), _onLadder(false)
{
}


Player::~Player()
{
}

void Player::handlePlayerInput(sf::Keyboard::Key key, bool isPressed)
{
	if (key == sf::Keyboard::Up)
	{
		_movingUp = isPressed && _onLadder ? true : false;
	}
	else if (key == sf::Keyboard::Down)
	{
		_movingDown = isPressed && _onLadder ? true : false;
	}
	else if (key == sf::Keyboard::Left)
	{
		_movingLeft = isPressed;
	}
	else if (key == sf::Keyboard::Right)
	{
		_movingRight = isPressed;
	}

	// moving free
	/*if ( key == sf::Keyboard::Up)
	{
		_movingUp;
	}
	else if (key == sf::Keyboard::Down)
	{
		_movingDown;
	}
	else if (key == sf::Keyboard::Left)
	{
		_movingLeft;
	}
	else if (key == sf::Keyboard::Right)
	{
		_movingRight;
	}*/


	if (key == sf::Keyboard::Space)
	{
	}

}
