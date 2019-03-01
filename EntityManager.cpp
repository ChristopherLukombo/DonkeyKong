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
			block->mSprite.setTexture(mRessourceManager.mTextureBlock);
			block->mSprite.setPosition(100.f + 70.f * (i + 1), 0.f + BLOCK_SPACE * (j + 1));
			block->mSize = mRessourceManager.mSizeBlock;
			block->mPosition = block->mSprite.getPosition();
			m_Entities.push_back(block);
		}
	}

	// Draw Echelles

	for (int i = 0; i < ECHELLE_COUNT; i++)
	{
		std::shared_ptr<Ladder> ladder = std::make_shared<Ladder>();
		ladder->mSprite.setTexture(mRessourceManager.mTextureLadder);
		ladder->mSprite.setPosition(100.f + 70.f * (i + 1), 0.f + BLOCK_SPACE * (i + 1) + mRessourceManager.mSizeBlock.y);
		ladder->mSize = mRessourceManager.mSizeLadder;
		ladder->mPosition = ladder->mSprite.getPosition();
		m_Entities.push_back(ladder);
	}


	// Draw Mario
	mario.mSprite.setTexture(mRessourceManager.mTextureMarioRight);
	mario.mSize = mRessourceManager.mSizeMarioRight;
	mario.mSprite.setPosition(100.f + 70.f, BLOCK_SPACE * 5 - mRessourceManager.mSizeMarioRight.y -12 );
	mario.mPosition = mario.mSprite.getPosition();

	//m_Entities.push_back(mario);

}


EntityManager::~EntityManager()
{
}

Mario EntityManager::GetMario()
{
	return mario;
}

RessourceManager EntityManager::GetRessourceManager()
{
	return mRessourceManager;
}

