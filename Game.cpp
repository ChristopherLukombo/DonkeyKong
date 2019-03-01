#include "pch.h"
#include "StringHelpers.h"
#include "Game.h"
#include "EntityManager.h"

const sf::Time Game::TimePerFrame = sf::seconds(1.f / 60.f);

Game::Game()
	: mWindow("Donkey Kong 1981", sf::Vector2u(840, 600))
	, mStatisticsText()
	, mStatisticsUpdateTime()
	, mStatisticsNumFrames(0)
	, mCollider()
{
	mPlayer = mEntityManager.GetMario();

	// Draw Statistic Font 
	mFont.loadFromFile("Media/Sansation.ttf");
	mStatisticsText.setString("Welcome to Donkey Kong 1981");
	mStatisticsText.setFont(mFont);
	mStatisticsText.setPosition(5.f, 5.f);
	mStatisticsText.setCharacterSize(10);


	//Adding bindings events
	mWindow.GetEventManager()->AddCallback("Move", &Game::MoveSprite, this);

}

void Game::run()
{
	sf::Time timeSinceLastUpdate = sf::Time::Zero;
	while ( !mWindow.isDone() )
	{
		RestartClock();
		timeSinceLastUpdate += mElapsed;
		while (timeSinceLastUpdate > TimePerFrame)
		{
			timeSinceLastUpdate -= TimePerFrame;

			processEvents();
			update(TimePerFrame);
		}
		updateStatistics(mElapsed);
		render();
	}
}

void Game::processEvents()
{
	sf::Event event;
	while (mWindow.GetRenderWindow()->pollEvent(event)) 
	{
		switch (event.type) 
{
		case sf::Event::KeyPressed:
			mPlayer.handlePlayerInput(event.key.code, true);
			break;

		case sf::Event::KeyReleased:
			mPlayer.handlePlayerInput(event.key.code, false);
			break;

		case sf::Event::LostFocus:
			mWindow.SetFocus(false);
			mWindow.GetEventManager()->SetFocus(false);
			break;

		case sf::Event::GainedFocus:
			mWindow.SetFocus(true);
			mWindow.GetEventManager()->SetFocus(true);
			break;
		}

		mWindow.GetEventManager()->HandleEvent(event);
	}

	mWindow.GetEventManager()->Update();
}

void Game::update(sf::Time elapsedTime)
{
	if (mPlayer._movingUp)
		mPlayer.MoveUp(elapsedTime, mEntityManager.GetRessourceManager().mSpriteMarioUp, mEntityManager.GetRessourceManager().mSizeMarioUp);
	if (mPlayer._movingDown)
		mPlayer.MoveDown(elapsedTime, mEntityManager.GetRessourceManager().mSpriteMarioUp, mEntityManager.GetRessourceManager().mSizeMarioUp);
	if (mPlayer._movingLeft)
		mPlayer.MoveLeft(elapsedTime, mEntityManager.GetRessourceManager().mSpriteMarioLeft, mEntityManager.GetRessourceManager().mSizeMarioLeft);
	if (mPlayer._movingRight)
		mPlayer.MoveRight(elapsedTime, mEntityManager.GetRessourceManager().mSpriteMarioRight, mEntityManager.GetRessourceManager().mSizeMarioRight);

	sf::Vector2f movement(0.f, 0.f);
	if (!mPlayer._onBlock && !mPlayer._onLadder) {
		movement.y = 100.0f;
	}

	mPlayer.m_sprite.move(movement * elapsedTime.asSeconds());

}

void Game::render()
{
	mWindow.BeginDraw();

	for (std::shared_ptr<Entity> entity : EntityManager::m_Entities)
	{
		if (entity->m_enabled == false)
		{
			continue;
		}

		mWindow.Draw(entity->m_sprite);
	}
	mWindow.Draw(mPlayer.m_sprite);
	mWindow.Draw(mStatisticsText);
	mWindow.EndDraw();
}

void Game::updateStatistics(sf::Time elapsedTime)
{
	mStatisticsUpdateTime += elapsedTime;
	mStatisticsNumFrames += 1;

	if (mStatisticsUpdateTime >= sf::seconds(1.0f))
	{
		mStatisticsText.setString(
			"Frames / Second = " + toString(mStatisticsNumFrames) + "\n" +
			"Time / Update = " + toString(mStatisticsUpdateTime.asMicroseconds() / mStatisticsNumFrames) + "us\n" +
			"Gravity on ? = " + toString(!mPlayer._onBlock));

		mStatisticsUpdateTime -= sf::seconds(1.0f);
		mStatisticsNumFrames = 0;
	}

	//
	// Handle collision
	//

	if (mStatisticsUpdateTime >= sf::seconds(0.050f))
	{
		handleCollisionLadder();
		handleCollisionBlock();
	}
}

void Game::handleCollisionBlock()
{
		for (std::shared_ptr<Entity> block : EntityManager::m_Entities)
		{
			if (block->m_type != EntityType::block)
			{
				continue;
			}

			if (block->m_enabled == false)
			{
				continue;
			}

			mPlayer._onBlock = mCollider.checkCollisionWithMario(mPlayer, block);
			if (mPlayer._onBlock)
			{
				break;
			}
		}

	return;
}

void Game::handleCollisionLadder()
{
		for (std::shared_ptr<Entity> ladder : EntityManager::m_Entities)
		{
			if (ladder->m_type != EntityType::ladder)
			{
				continue;
			}

			if (ladder->m_enabled == false)
			{
				continue;
			}

			mPlayer._onLadder = mCollider.checkCollisionWithMario(mPlayer, ladder);
			if (mPlayer._onLadder)
			{
				break;
			}
		}

	return;
}

void Game::MoveSprite(EventDetails* l_details)
{
	sf::Vector2i mousepos = mWindow.GetEventManager()->GetMousePosition(mWindow.GetRenderWindow());
	mPlayer.m_sprite.setPosition(mousepos.x, mousepos.y);

	std::cout <<"Moving sprite to : "
		<< mousepos.x << ":" 
		<< mousepos.y << std::endl;

}