#include "pch.h"
#include "RessourceManager.h"

RessourceManager::RessourceManager()
{
	// Loading blocks texture
	if (!mTextureBlock.loadFromFile("Media/Textures/Block.png")) 
	{
		std::printf("ERROR : Loading block texture");
	}
	mSizeBlock = mTextureBlock.getSize();

	// Loading ladders texture
	if (!mTextureLadder.loadFromFile("Media/Textures/Echelle.png")) 
	{
		std::printf("ERROR : Loading ladder texture");
	}
	mSizeLadder = mTextureLadder.getSize();

	// Loading mario texture
	if (!mTextureMario.loadFromFile("Media/Textures/Mario_small_transparent.png")) 
	{
		std::printf("ERROR : Loading ladder texture");
	}
	mSizeMario = mTextureMario.getSize();

	// Loading donkey kong texture
	/* (!mTextureDonkeyKong.loadFromFile("Media/Textures/???.png")) {
		std::printf("ERROR : Loading Donkey Kong texture");
	}*/

	// Loading Peach
	/*if (!mTexturePeach.loadFromFile("Media/Textures/???.png")) {
		std::printf("ERROR : Loading Peach texture");
	}*/

	// Loading coins texture
	if (!mTextureCoin.loadFromFile("Media/Textures/Piece.png")) {
		std::printf("ERROR : Loading coin texture");
	}

	// Loading barrels texture
	/*if (!mTextureBarrel.loadFromFile("Media/Textures/???.png")) {
		std::printf("ERROR : Loading barrel texture");
	}*/


}


RessourceManager::~RessourceManager()
{
}
