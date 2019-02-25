#pragma once

#include "Player.h"
#include "Window.h"

#define ECHELLE_COUNT 4
#define BLOCK_COUNT_X 8
#define BLOCK_COUNT_Y 5
#define BLOCK_SPACE 110.f

class Game
{
public:
	Game();
	~Game() { };
	void run();


public :
	Window* GetWindow() { return &m_window; };

	void RestartClock();

private:
	void processEvents();
	void update(sf::Time elapsedTime);
	void render();

	void updateStatistics(sf::Time elapsedTime);
	void handleCollisionBlock();
	void handleCollisionLadder();

	void MoveSprite(EventDetails* l_details);


private:
	static const float		PlayerSpeed;
	static const sf::Time	TimePerFrame;

	Window m_window;
	sf::Texture	mTexture;
	Player	mPlayer;
	sf::Font	mFont;
	sf::Text	mStatisticsText;
	sf::Time	mStatisticsUpdateTime;

	std::size_t	mStatisticsNumFrames;

	sf::Clock m_clock;
	sf::Time m_elapsed;

	sf::Texture	_TextureEchelle;
	sf::Sprite	_Echelle[ECHELLE_COUNT];
	sf::Texture	_TextureBlock;
	sf::Sprite	_Block[BLOCK_COUNT_X][BLOCK_COUNT_Y];
	sf::Texture	_TextureWeapon;
	sf::Sprite	_Weapon;
	sf::Vector2u _sizeBlock;
	sf::Vector2u _sizeLadder;
	sf::Vector2u _sizeMario;
};

