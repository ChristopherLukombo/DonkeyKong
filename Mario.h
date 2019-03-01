#pragma once
#include "pch.h"
#include "Entity.h"


class Mario : public Entity
{
public:
	Mario();
	~Mario();

	void handlePlayerInput(sf::Keyboard::Key key, bool isPressed);
	void MoveUp(sf::Time elapsedTime, sf::Sprite sprite, sf::Vector2u size);
	void MoveDown(sf::Time elapsedTime, sf::Sprite sprite, sf::Vector2u size);
	void MoveLeft(sf::Time elapsedTime, sf::Sprite sprite, sf::Vector2u size);
	void MoveRight(sf::Time elapsedTime, sf::Sprite sprite, sf::Vector2u size);
	void Jump(sf::Time elapsedTime);
	void SetMarioSprite(sf::Sprite sprite, sf::Vector2u size);

public :
	static const float PlayerSpeed;

	bool mMovingUp;
	bool mMovingDown;
	bool mMovingRight;
	bool mMovingLeft; 
	bool mJumping;
	bool mOnLadder;
	bool mOnBlock;
	bool mIsJumping;
	bool mCollideCoin;
};

