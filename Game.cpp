#include "pch.h"
#include "StringHelpers.h"
#include "Game.h"
#include "EntityManager.h"

const float Game::PlayerSpeed = 10.f;
const sf::Time Game::TimePerFrame = sf::seconds(1.f / 60.f);

Game::Game()
	: m_window("Donkey Kong 1981", sf::Vector2u(840, 600))
	, mTexture()
	, mPlayer()
	, mFont()
	, mStatisticsText()
	, mStatisticsUpdateTime()
	, mStatisticsNumFrames(0) 
{

	// Draw blocks

	if (!_TextureBlock.loadFromFile("Media/Textures/Block.png"))
	{
		// Handle loading error
	}
	
	_sizeBlock = _TextureBlock.getSize();

	for (int i = 0; i < BLOCK_COUNT_X; i++)
	{
		for (int j = 0; j < BLOCK_COUNT_Y; j++)
		{
			_Block[i][j].setTexture(_TextureBlock);
			_Block[i][j].setPosition(100.f + 70.f * (i + 1), 0.f + BLOCK_SPACE * (j + 1));

			std::shared_ptr<Entity> se = std::make_shared<Entity>();
			se->m_sprite = _Block[i][j];
			se->m_type = EntityType::block;
			se->m_size = _TextureBlock.getSize();
			se->m_position = _Block[i][j].getPosition();
			se->m_sprite.setOrigin( (sf::Vector2f)_sizeBlock / 2.0f);
			EntityManager::m_Entities.push_back(se);
		}
	}

	// Draw Echelles

	if (!_TextureEchelle.loadFromFile("Media/Textures/Echelle.png"))
	{
		// Handle loading error
	}
	
	_sizeLadder = _TextureEchelle.getSize();
	for (int i = 0; i < ECHELLE_COUNT; i++)
	{
		_Echelle[i].setTexture(_TextureEchelle);
		_Echelle[i].setPosition(100.f + 70.f * (i + 1), 0.f + BLOCK_SPACE * (i + 1) + _sizeBlock.y );

		std::shared_ptr<Entity> se = std::make_shared<Entity>();
		se->m_sprite = _Echelle[i];
		se->m_type = EntityType::ladder;
		se->m_size = _TextureEchelle.getSize();
		se->m_position = _Echelle[i].getPosition();
		se->m_sprite.setOrigin((sf::Vector2f)_sizeLadder / 2.0f);
		EntityManager::m_Entities.push_back(se);
	}

	// Draw Mario

	if (!mTexture.loadFromFile("Media/Textures/Mario_small_transparent.png")) // Mario_small.png");
	{
		//Handle loading error
	}


	mPlayer.m_sprite.setTexture(mTexture);
	mPlayer.m_size = mTexture.getSize();
	mPlayer.m_position.x = 100.f + 70.f;
	mPlayer.m_position.y = BLOCK_SPACE * 5 - mPlayer.m_size.y;
	mPlayer.m_sprite.setPosition(mPlayer.m_position);
	mPlayer.m_sprite.setOrigin((sf::Vector2f)mTexture.getSize() / 2.0f);


	std::shared_ptr<Entity> player = std::make_shared<Entity>();
	*player = mPlayer;
	EntityManager::m_Entities.push_back(player);

	// Draw Statistic Font 

	mFont.loadFromFile("Media/Sansation.ttf");
	mStatisticsText.setString("Welcome to Donkey Kong 1981");
	mStatisticsText.setFont(mFont);
	mStatisticsText.setPosition(5.f, 5.f);
	mStatisticsText.setCharacterSize(10);
}

void Game::run()
{
	sf::Time timeSinceLastUpdate = sf::Time::Zero;

	while ( !m_window.isDone() )
	{
		RestartClock();
		timeSinceLastUpdate += m_elapsed;
		
		while (timeSinceLastUpdate > TimePerFrame)
		{
			timeSinceLastUpdate -= TimePerFrame;
			HandleInput();
			m_window.Update();
			update(TimePerFrame);
		}
		updateStatistics(m_elapsed);
		render();
	}

}

void Game::HandleInput()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
		mPlayer._movingUp = true && mPlayer._onLadder ? true : false;
	} 
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
		mPlayer._movingDown = true && mPlayer._onLadder ? true : false;
	}
	else {
		mPlayer._movingUp = false;
		mPlayer._movingDown = false;
	}


	 if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		mPlayer._movingLeft = true;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		mPlayer._movingRight = true;
	 }
	else {
		 mPlayer._movingLeft = false;
		 mPlayer._movingRight = false;
	 }

	 if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
	 {
	 }
}

void Game::RestartClock()
{
	m_elapsed = m_clock.restart();
}

void Game::update(sf::Time elapsedTime)
{
	sf::Vector2f movement(0.f, 0.f);

	if (!mPlayer._onBlock)
	{
		movement.y = 5.0f;
	}



	if (mPlayer._movingUp)
		movement.y -= PlayerSpeed;
	if (mPlayer._movingDown)
		movement.y += PlayerSpeed;
	if (mPlayer._movingLeft)
		movement.x -= PlayerSpeed;
	if (mPlayer._movingRight)
		movement.x += PlayerSpeed;

	for (std::shared_ptr<Entity> entity : EntityManager::m_Entities)
	{
		if (entity->m_enabled == false)
		{
			continue;
		}

		if (entity->m_type != EntityType::player)
		{
			continue;
		}

		entity->m_sprite.move(movement * elapsedTime.asSeconds());
	}
}

void Game::render()
{
	m_window.BeginDraw();

	for (std::shared_ptr<Entity> entity : EntityManager::m_Entities)
	{
		if (entity->m_enabled == false)
		{
			continue;
		}

		m_window.Draw(entity->m_sprite);
	}

	m_window.Draw(mStatisticsText);
	m_window.EndDraw();
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

			sf::FloatRect playerBounds = EntityManager::GetPlayer()->m_sprite.getGlobalBounds();
			sf::FloatRect blockBounds = block->m_sprite.getGlobalBounds();

			if (playerBounds.intersects(blockBounds) == true)
			{
				std::cout << "COLLIDE" << std::endl;
				mPlayer._onBlock = true;
				break;
			}
			else
			{
				std::cout << "DONT COLLIDE" << std::endl;
				mPlayer._onBlock = false;
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


			sf::FloatRect playerBounds = EntityManager::GetPlayer()->m_sprite.getGlobalBounds();
			sf::FloatRect ladderBounds = ladder->m_sprite.getGlobalBounds();

			if (playerBounds.intersects(ladderBounds))
			{
				std::cout << "COLLIDE LADDER" << std::endl;
				mPlayer._onLadder = true;
				break;
			}
			else 
			{
				std::cout << "DONT COLLIDE LADDER" << std::endl;
				mPlayer._onLadder = false;
			}
		}
	return;
}



void Game::handlePlayerInput(sf::Keyboard::Key key, bool isPressed)
{
	if (key == sf::Keyboard::Up && mPlayer._onLadder == true)
	{
		mPlayer._movingUp = isPressed;
	}
	else if (key == sf::Keyboard::Up && mPlayer._onLadder == false)
	{
		mPlayer._movingUp = false;
	}
	else if (key == sf::Keyboard::Down && mPlayer._onLadder == true)
	{
		mPlayer._movingDown = isPressed;
	}
	else if (key == sf::Keyboard::Down && mPlayer._onLadder == false)
	{
		mPlayer._movingDown = false;
	}
	else if (key == sf::Keyboard::Left)
	{
		mPlayer._movingLeft = isPressed;
	}
	else if (key == sf::Keyboard::Right)
	{
		mPlayer._movingRight = isPressed;
	}

	// moving free
	/*if (key == sf::Keyboard::Up)
	{
		mPlayer.SetMovingUp(isPressed);
	}
	else if (key == sf::Keyboard::Down)
	{
		mPlayer.SetMovingDown(isPressed);
	}
	else if (key == sf::Keyboard::Left)
	{
		mPlayer.SetMovingLeft(isPressed);
	}
	else if (key == sf::Keyboard::Right)
	{
		mPlayer.SetMovingRight(isPressed);
	}*/


	if (key == sf::Keyboard::Space)
	{
	}
}

