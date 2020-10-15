#include "PowBlock.h"
#include <string>
#include <iostream>

using namespace std;

PowBlock::PowBlock(SDL_Renderer* renderer, LevelMap* map, Vector2D pos) {
	string imagePath = "Images/PowBlock.png";
	mRenderer = renderer;
	mTexture = new Texture2D(mRenderer);
	if (!mTexture->LoadFromFile(imagePath.c_str()))
	{
		cerr << "Could not load image from file" << imagePath << endl;
		return;
	}
	mLevelMap = map;
	singleSpriteWidth = mTexture->GetWidth() / 3; // because there are 3 sprites in a row
	singleSpriteHeight = mTexture->GetHeight();
	hitsLeft = 3;
	mPos = pos;
}

PowBlock::~PowBlock() {
	mRenderer = NULL;
	delete mTexture;
}

void PowBlock::Render() {
	if (hitsLeft > 0)
	{
		int left = (int)singleSpriteWidth*(hitsLeft - 1);
		SDL_Rect portionOfSpriteSheet = { left, 0, (int)singleSpriteWidth, (int)singleSpriteHeight };
		SDL_Rect destRect = { (int)mPos.x, (int)mPos.y, (int)singleSpriteWidth, (int)singleSpriteHeight };
		mTexture->Render(portionOfSpriteSheet, destRect, SDL_FLIP_NONE, 0);
	}
}

Rect2D PowBlock::GetCollisonBox() {
	return Rect2D(mPos.x, mPos.y, singleSpriteWidth, singleSpriteHeight);
}

void PowBlock::TakeHit() {
	hitsLeft -= 1;
	soundManager->LoadMusic(2, hit, "Music/Hit.wav", 0);
	if (hitsLeft <= 0)
	{
		//if the block is destroyed, change this tile so it has no collision
		mLevelMap->ChangeTileAt(8, 7, 0);
		mLevelMap->ChangeTileAt(8, 8, 0);
	}
}