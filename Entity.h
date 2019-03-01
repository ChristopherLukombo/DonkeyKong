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

	sf::Vector2f GetPosition() { return m_position;  }

public:
	sf::Sprite m_sprite;
	sf::Vector2u m_size;
	sf::Vector2f m_position;
	EntityType m_type;
	bool m_enabled = true;

	// Enemy only
	bool m_bLeftToRight = true;
	int m_times = 0;
};

