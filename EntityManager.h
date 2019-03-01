#pragma once

#include "RessourceManager.h"
#include "Entity.h"
#include "Block.h"
#include "Ladder.h"
#include "Mario.h"


#define ECHELLE_COUNT 4
#define BLOCK_COUNT_X 8
#define BLOCK_COUNT_Y 5
#define BLOCK_SPACE 110.f


class EntityManager
{
public:
	EntityManager();
	~EntityManager();

public:
	static std::vector<std::shared_ptr<Entity>> m_Entities;
	Mario GetMario();

private:
	RessourceManager	mRessourceManager;
	Mario mario;
};

