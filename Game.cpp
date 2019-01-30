#include "pch.h"
#include "StringHelpers.h"
#include "Game.h"
#include "EntityManager.h"

const float Game::PlayerSpeed = 100.f;
const sf::Time Game::TimePerFrame = sf::seconds(1.f / 60.f);

Game::Game()
	: mWindow(sf::VideoMode(840, 600), "Donkey Kong 1981", sf::Style::Close)
	, mTexture()
	, mPlayer()
	, mFont()
	, mStatisticsText()
	, mStatisticsUpdateTime()
	, mStatisticsNumFrames(0)
	, mIsMovingUp(false)
	, mIsMovingDown(false)
	, mIsMovingRight(false)
	, mIsMovingLeft(false)
	, mIsJumping(false)
	, mIsOnLadder(false)
	, mIsOnBlock(false)
{
	mWindow.setFramerateLimit(160);

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

	// Draw Coins

	_TextureCoin.loadFromFile("Media/Textures/Piece.PNG");

	_sizeCoin = _TextureCoin.getSize();
	for (int i = 0; i < COIN_COUNT_X; i++)
	{
		for (int j = 0; j < COIN_COUNT_Y; j++)
		{
			_Coin[i][j].setTexture(_TextureCoin);
			_Coin[i][j].setPosition(100.f + 150.f * (i + 1), 0.f + BLOCK_SPACE * (i + 1) - _sizeBlock.y);

			std::shared_ptr<Entity> se = std::make_shared<Entity>();
			se->m_sprite = _Coin[i][j];
			se->m_type = EntityType::coin;
			se->m_size = _TextureCoin.getSize();
			se->m_position = _Coin[i][j].getPosition();
			se->m_sprite.setOrigin((sf::Vector2f)_sizeCoin / 2.0f);
			EntityManager::m_Entities.push_back(se);
		}
	}

	// Draw Mario

	if (!mTexture.loadFromFile("Media/Textures/Mario_small_transparent.png")) // Mario_small.png");
	{
		//Handle loading error
	}
	_sizeMario = mTexture.getSize();
	mPlayer.setTexture(mTexture);
	sf::Vector2f posMario;
	posMario.x = 100.f + 70.f;
	posMario.y = BLOCK_SPACE * 5 - _sizeMario.y;

	mPlayer.setPosition(posMario);

	std::shared_ptr<Entity> player = std::make_shared<Entity>();
	player->m_sprite = mPlayer;
	player->m_type = EntityType::player;
	player->m_size = mTexture.getSize();
	player->m_position = mPlayer.getPosition();
	player->m_sprite.setOrigin((sf::Vector2f)mTexture.getSize() / 2.0f);
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
	sf::Clock clock;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;
	while (mWindow.isOpen())
	{
		sf::Time elapsedTime = clock.restart();
		timeSinceLastUpdate += elapsedTime;

		
		while (timeSinceLastUpdate > TimePerFrame)
		{
			timeSinceLastUpdate -= TimePerFrame;
			
			processEvents();
			update(TimePerFrame);
		}
		updateStatistics(elapsedTime);
		render();
	}
}

void Game::processEvents()
{
	sf::Event event;
	while (mWindow.pollEvent(event))
	{
		switch (event.type)
		{
		case sf::Event::KeyPressed:
			handlePlayerInput(event.key.code, true);
			break;

		case sf::Event::KeyReleased:
			handlePlayerInput(event.key.code, false);
			break;

		case sf::Event::Closed:
			mWindow.close();
			break;
		}
	}


}

void Game::update(sf::Time elapsedTime)
{
	sf::Vector2f movement(0.f, 0.f);

	if (!mIsOnBlock)
	{
		movement.y = 50.0f;
	}

	if (mIsMovingUp)
		movement.y -= PlayerSpeed;
	if (mIsMovingDown)
		movement.y += PlayerSpeed;
	if (mIsMovingLeft)
		movement.x -= PlayerSpeed;
	if (mIsMovingRight)
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
	mWindow.clear();

	for (std::shared_ptr<Entity> entity : EntityManager::m_Entities)
	{
		if (entity->m_enabled == false)
		{
			continue;
		}

		mWindow.draw(entity->m_sprite);
	}

	mWindow.draw(mStatisticsText);
	mWindow.display();
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
			"Gravity on ? = " + toString(!mIsOnBlock));

		mStatisticsUpdateTime -= sf::seconds(1.0f);
		mStatisticsNumFrames = 0;
	}

	//
	// Handle collision
	//

	if (mStatisticsUpdateTime >= sf::seconds(0.050f))
	{
		// Handle collision mario and ladder

		for (std::shared_ptr<Entity> player : EntityManager::m_Entities)
		{
			if (player->m_type != EntityType::player)
			{
				continue;
			}

			if (player->m_enabled == false)
			{
				continue;
			}

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

/*
				sf::FloatRect playerBounds = player->m_sprite.getGlobalBounds();
				sf::FloatRect blockBounds = block->m_sprite.getGlobalBounds();

				if (playerBounds.intersects(blockBounds))
				{
					std::cout << "COLLIDE" << std::endl;
					mIsOnBlock = true;

				}
				else
				{
					std::cout << "DONT COLLIDE" << std::endl;
					mIsOnBlock = false;
				}
*/

				// Collision with the platform of blocks
				Collider col = block->GetCollider();
				mIsOnBlock  = player->GetCollider().checkCollision(col, 0.0f);



								
			}
		
		
		}
	}
}

void Game::handlePlayerInput(sf::Keyboard::Key key, bool isPressed)
{
	if (key == sf::Keyboard::Up && mIsOnLadder == true) 
	{
		mIsMovingUp = isPressed;
		mTexture.loadFromFile("Media/Textures/Mario1.png");
	}
	else if (key == sf::Keyboard::Up && mIsOnLadder == false)
	{
		mIsMovingUp = false;
	}
	else if (key == sf::Keyboard::Down && mIsOnLadder == true)
	{
		mIsMovingDown = isPressed;
		mTexture.loadFromFile("Media/Textures/Mario1.png");
	}
	else if (key == sf::Keyboard::Down && mIsOnLadder == false)
	{
		mIsMovingDown = false;
	}
	else if (key == sf::Keyboard::Left)
	{
		mIsMovingLeft = isPressed;
		mTexture.loadFromFile("Media/Textures/MarioLeft.png");
	}
	else if (key == sf::Keyboard::Right)
	{
		mIsMovingRight = isPressed;
		mTexture.loadFromFile("Media/Textures/Mario_small_transparent.png");
	}


	if (key == sf::Keyboard::Space)
	{
		mTexture.loadFromFile("Media/Textures/Mario1.png");
	}
}
