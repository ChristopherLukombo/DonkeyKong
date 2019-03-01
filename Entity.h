#pragma once

enum EntityType
{
	player,
	donkey_kong,
	peach,
	block,
	coin,
	ladder,
	barrel

};

class Entity
{
public:
	Entity() { };
	~Entity() { };

	sf::Vector2f GetPosition() { return mPosition;  }

public:
	sf::Sprite mSprite;
	sf::Vector2u mSize;
	sf::Vector2f mPosition;
	EntityType mType;
	bool mEnabled = true;

	// Enemy only
	bool mBLeftToRight = true;
	int mTimes = 0;
};

