#include "pch.h"
#include "Mario.h"

const float Mario::PlayerSpeed = 150.f;


Mario::Mario() :
	mMovingUp(false), mMovingDown(false), mMovingLeft(false), mMovingRight(false), mJumping(false), mOnBlock(false), mOnLadder(false), mIsJumping(false)
{
	mType = EntityType::player;
}


Mario::~Mario()
{
}

void Mario::handlePlayerInput(sf::Keyboard::Key key, bool isPressed)
{
	if (key == sf::Keyboard::Up)
	{
		mMovingUp = isPressed; // && _onLadder ? true : false;
	}
	else if (key == sf::Keyboard::Down)
	{
		mMovingDown = isPressed; // && _onLadder ? true : false;
	}
	else if (key == sf::Keyboard::Left)
	{
		mMovingLeft = isPressed;
	}
	else if (key == sf::Keyboard::Right)
	{
		mMovingRight = isPressed;
	}

	if (key == sf::Keyboard::Space)
	{
		mJumping = isPressed;
		mIsJumping = true;
	}

}

void Mario::MoveUp(sf::Time elapsedTime, sf::Sprite sprite, sf::Vector2u size)
{
	if (mOnLadder)
	{
		SetMarioSprite(sprite, size);
		sf::Vector2f movement(0.f, 0.f);
		movement.y -= PlayerSpeed;
		mSprite.move(movement * elapsedTime.asSeconds());
	}
}

void Mario::MoveDown(sf::Time elapsedTime, sf::Sprite sprite, sf::Vector2u size)
{
	if (mOnLadder)
	{
		SetMarioSprite(sprite, size);
		sf::Vector2f movement(0.f, 0.f);
		movement.y += PlayerSpeed;
		mSprite.move(movement * elapsedTime.asSeconds());
	}
}

void Mario::MoveLeft(sf::Time elapsedTime, sf::Sprite sprite, sf::Vector2u size)
{
	if (!mOnLadder) {
		SetMarioSprite(sprite, size);
		sf::Vector2f movement(0.f, 0.f);
		movement.x -= PlayerSpeed;
		mSprite.move(movement * elapsedTime.asSeconds());
	}
}

void Mario::MoveRight(sf::Time elapsedTime, sf::Sprite sprite, sf::Vector2u size)
{
	if (!mOnLadder) {
		SetMarioSprite(sprite, size);
		sf::Vector2f movement(0.f, 0.f);
		movement.x += PlayerSpeed;
		mSprite.move(movement * elapsedTime.asSeconds());
	}
}

void Mario::Jump(sf::Time elapsedTime)
{
	if (!mOnLadder && mIsJumping)
	{
		mIsJumping = false;
		//SetMarioSprite(sprite, size);
		sf::Vector2f movement(0.f, 0.f);
		movement.y -= PlayerSpeed * 10;
		mSprite.move(movement * elapsedTime.asSeconds());
	}
}

void Mario::SetMarioSprite(sf::Sprite sprite, sf::Vector2u size)
{
	sf::Sprite tmp = mSprite;
	mSprite = sprite;
	mSprite.setPosition(tmp.getPosition());
	mSize = size;
}
