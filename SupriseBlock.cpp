#include "SupriseBlock.h"
#include <iostream>
using namespace::std;

SupriseBlock::SupriseBlock(SDL_Renderer* renderer, LevelMap* map, Vector2D pos)
{
	string imagePath = "Images/Suprise_Block.png";
	mRenderer = renderer;
	mTexture = new Texture2D(mRenderer);
	if (!mTexture->LoadFromFile(imagePath.c_str()))
	{
		cerr << "Could not load image from file" << imagePath << endl;
		return;
	}
	mLevelMap = map;
	mPos = pos;
	left = 0;
	isAvaliable = true;
}

SupriseBlock::~SupriseBlock()
{
	mRenderer = NULL;
	delete mTexture;
}

void SupriseBlock::Render()
{
	SDL_Rect srcRect = { left, 0,  mTexture->GetWidth() / 2, mTexture->GetHeight() };
	SDL_Rect destRect = { (int)mPos.x, (int)mPos.y,  mTexture->GetWidth() / 2, mTexture->GetHeight() };
	mTexture->Render(srcRect, destRect, SDL_FLIP_NONE, 0);
}

Rect2D SupriseBlock::GetCollisonBox()
{
	return Rect2D(mPos.x, mPos.y, mTexture->GetWidth() / 2, mTexture->GetHeight());
}
void SupriseBlock::TakeHit() {
	soundManager->LoadMusic(2, hit, "Music/Hit.wav", 0);
	//if the block is destroyed, change this tile so it has no collision
	left = 32;
	mLevelMap->ChangeTileAt(8, 3, 1);
	isAvaliable = false;
}