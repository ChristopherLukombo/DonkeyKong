#pragma once

class RessourceManager
{
public:
	RessourceManager();
	~RessourceManager();

public:
	sf::Texture		mTextureBlock;
	sf::Texture		mTextureLadder;
	sf::Texture		mTextureMarioRight;
	sf::Texture		mTextureMarioLeft;
	sf::Texture		mTextureMarioUp;
	sf::Texture		mTextureDonkeyKong;
	sf::Texture		mTexturePeach;
	sf::Texture		mTextureCoin;
	sf::Texture		mTextureBarrel;

	
	sf::Sprite		mSpriteMarioRight;
	sf::Sprite		mSpriteMarioLeft;
	sf::Sprite		mSpriteMarioUp;

	sf::Vector2u	mSizeBlock;
	sf::Vector2u	mSizeLadder;
	sf::Vector2u	mSizeMarioRight;
	sf::Vector2u	mSizeMarioLeft;
	sf::Vector2u	mSizeMarioUp;
};

