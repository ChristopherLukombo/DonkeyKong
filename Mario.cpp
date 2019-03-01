#include "pch.h"
#include "Mario.h"

const float Mario::PlayerSpeed = 150.f;


Mario::Mario() :
	_movingUp(false), _movingDown(false), _movingLeft(false), _movingRight(false), _jumping(false), _onBlock(false), _onLadder(false)
{
	m_type = EntityType::player;
}


Mario::~Mario()
{
}

void Mario::handlePlayerInput(sf::Keyboard::Key key, bool isPressed)
{
	if (key == sf::Keyboard::Up)
	{
		_movingUp = isPressed; // && _onLadder ? true : false;
	}
	else if (key == sf::Keyboard::Down)
	{
		_movingDown = isPressed; // && _onLadder ? true : false;
	}
	else if (key == sf::Keyboard::Left)
	{
		_movingLeft = isPressed;
	}
	else if (key == sf::Keyboard::Right)
	{
		_movingRight = isPressed;
	}

	if (key == sf::Keyboard::Space)
	{
		_jumping = isPressed;
	}

}

void Mario::MoveUp(sf::Time elapsedTime, sf::Sprite sprite, sf::Vector2u size)
{
	if (_onLadder)
	{
		SetMarioSprite(sprite, size);
		sf::Vector2f movement(0.f, 0.f);
		movement.y -= PlayerSpeed;
		m_sprite.move(movement * elapsedTime.asSeconds());
	}
}

void Mario::MoveDown(sf::Time elapsedTime, sf::Sprite sprite, sf::Vector2u size)
{
	if (_onLadder)
	{
		SetMarioSprite(sprite, size);
		sf::Vector2f movement(0.f, 0.f);
		movement.y += PlayerSpeed;
		m_sprite.move(movement * elapsedTime.asSeconds());
	}
}

void Mario::MoveLeft(sf::Time elapsedTime, sf::Sprite sprite, sf::Vector2u size)
{
		SetMarioSprite(sprite, size);
		sf::Vector2f movement(0.f, 0.f);
		movement.x -= PlayerSpeed;
		m_sprite.move(movement * elapsedTime.asSeconds());
}

void Mario::MoveRight(sf::Time elapsedTime, sf::Sprite sprite, sf::Vector2u size)
{
		SetMarioSprite(sprite, size);
		sf::Vector2f movement(0.f, 0.f);
		movement.x += PlayerSpeed;
		m_sprite.move(movement * elapsedTime.asSeconds());
}

void Mario::SetMarioSprite(sf::Sprite sprite, sf::Vector2u size)
{
	sf::Sprite tmp = m_sprite;
	m_sprite = sprite;
	m_sprite.setPosition(tmp.getPosition());
	m_size = size;
}
