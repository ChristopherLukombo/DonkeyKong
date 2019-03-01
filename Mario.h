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
	void SetMarioSprite(sf::Sprite sprite, sf::Vector2u size);

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

