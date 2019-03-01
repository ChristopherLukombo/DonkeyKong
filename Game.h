#pragma once

#include "Mario.h"
#include "Window.h"
#include "Collider.h"
#include "EntityManager.h"
class Game
{
public:
	Game();
	~Game() { };
	void run();


public :
	Window* GetWindow() { return &mWindow; };

	void RestartClock() { mElapsed = mClock.restart(); };

private:
	void processEvents();
	void update(sf::Time elapsedTime);
	void render();

	void updateStatistics(sf::Time elapsedTime);
	void handleCollisionBlock();
	void handleCollisionLadder();

	void MoveSprite(EventDetails* l_details);


private:
	static const sf::Time	TimePerFrame;

	Window				mWindow;
	EntityManager		mEntityManager;
	Mario				mPlayer;
	sf::Text			mStatisticsText;
	sf::Time			mStatisticsUpdateTime;
	Collider			mCollider;

	std::size_t			mStatisticsNumFrames;

	sf::Clock			mClock;
	sf::Time			mElapsed;

	sf::Font			mFont;
	sf::Sprite			mEchelle[ECHELLE_COUNT];
	sf::Sprite			mBlock[BLOCK_COUNT_X][BLOCK_COUNT_Y];
};

