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
	if (!mTextureMarioRight.loadFromFile("Media/Textures/face_right.png")) 
	{
		std::printf("ERROR : Loading mario right texture");
	}
	mSizeMarioRight = mTextureMarioRight.getSize();
	mSpriteMarioRight.setTexture(mTextureMarioRight);

	if (!mTextureMarioLeft.loadFromFile("Media/Textures/face_left.png"))
	{
		std::printf("ERROR : Loading mario left texture");
	}
	mSizeMarioLeft = mTextureMarioLeft.getSize();
	mSpriteMarioLeft.setTexture(mTextureMarioLeft);

	if (!mTextureMarioUp.loadFromFile("Media/Textures/climbing.png"))
	{
		std::printf("ERROR : Loading mario up texture");
	}
	mSizeMarioUp = mTextureMarioUp.getSize();
	mSpriteMarioUp.setTexture(mTextureMarioUp);

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
	mSizeCoin = mTextureCoin.getSize();
	mSpriteCoin.setTexture(mTextureCoin);

	// Loading barrels texture
	/*if (!mTextureBarrel.loadFromFile("Media/Textures/???.png")) {
		std::printf("ERROR : Loading barrel texture");
	}*/


}


RessourceManager::~RessourceManager()
{
}
