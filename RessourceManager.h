#pragma once

class RessourceManager
{
public:
	RessourceManager();
	~RessourceManager();

public:
	sf::Texture		mTextureBlock;
	sf::Texture		mTextureLadder;
	sf::Texture		mTextureMario;
	sf::Texture		mTextureDonkeyKong;
	sf::Texture		mTexturePeach;
	sf::Texture		mTextureCoin;
	sf::Texture		mTextureBarrel;

	sf::Sprite		mSpriteMario;

	sf::Vector2u	mSizeBlock;
	sf::Vector2u	mSizeLadder;
	sf::Vector2u	mSizeMario;
};

