#include "pch.h"
#include "EntityManager.h"

std::vector<std::shared_ptr<Entity>> EntityManager::m_Entities;

EntityManager::EntityManager() :
	mRessourceManager()
{
	// Draw blocks

	for (int i = 0; i < BLOCK_COUNT_X; i++)
	{
		for (int j = 0; j < BLOCK_COUNT_Y; j++)
		{
			std::shared_ptr<Block> block = std::make_shared<Block>();
			block->m_sprite.setTexture(mRessourceManager.mTextureBlock);
			block->m_sprite.setPosition(100.f + 70.f * (i + 1), 0.f + BLOCK_SPACE * (j + 1));
			block->m_size = mRessourceManager.mSizeBlock;
			block->m_position = block->m_sprite.getPosition();
			m_Entities.push_back(block);
		}
	}

	// Draw Echelles

	for (int i = 0; i < ECHELLE_COUNT; i++)
	{
		std::shared_ptr<Ladder> ladder = std::make_shared<Ladder>();
		ladder->m_sprite.setTexture(mRessourceManager.mTextureLadder);
		ladder->m_sprite.setPosition(100.f + 70.f * (i + 1), 0.f + BLOCK_SPACE * (i + 1) + mRessourceManager.mSizeBlock.y);
		ladder->m_size = mRessourceManager.mSizeLadder;
		ladder->m_position = ladder->m_sprite.getPosition();
		m_Entities.push_back(ladder);
	}


	// Draw Mario
	mario.m_sprite.setTexture(mRessourceManager.mTextureMario);
	mario.m_size = mRessourceManager.mSizeMario;
	mario.m_sprite.setPosition(100.f + 70.f, BLOCK_SPACE * 5 - mRessourceManager.mSizeMario.y);
	mario.m_position = mario.m_sprite.getPosition();

	//m_Entities.push_back(mario);

}


EntityManager::~EntityManager()
{
}

Mario EntityManager::GetMario()
{
	return mario;
}

