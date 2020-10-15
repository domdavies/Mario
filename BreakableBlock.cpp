#include "BreakableBlock.h"
#include <iostream>

using namespace::std;

BreakableBlock::BreakableBlock(SDL_Renderer* renderer, LevelMap* map, Vector2D pos)
{
	string imagePath = "Images/Breakable_Block.png";
	mRenderer = renderer;
	mTexture = new Texture2D(mRenderer);
	if (!mTexture->LoadFromFile(imagePath.c_str()))
	{
		cerr << "Could not load image from file" << imagePath << endl;
		return;
	}
	mLevelMap = map;
	mPos = pos;
	isAvaliable = true;
}

BreakableBlock::~BreakableBlock()
{
	mRenderer = NULL;
	delete mTexture;
}

void BreakableBlock::Render()
{
	SDL_Rect srcRect = { 0, 0,  mTexture->GetWidth(), mTexture->GetHeight() };
	SDL_Rect destRect = { (int)mPos.x, (int)mPos.y,  mTexture->GetWidth(), mTexture->GetHeight() };
	mTexture->Render(srcRect, destRect, SDL_FLIP_NONE, 0);
}

Rect2D BreakableBlock::GetCollisonBox()
{
	return Rect2D(mPos.x, mPos.y, mTexture->GetWidth(), mTexture->GetHeight());
}

void BreakableBlock::TakeHit()
{
	soundManager->LoadMusic(2, hit, "Music/Hit.wav", 0);
	//if the block is destroyed, change this tile so it has no collision
	//dividing by the tilesize, gets the tiles position in the array
	mLevelMap->ChangeTileAt(this->mPos.y / TILE_HEIGHT, this->mPos.x / TILE_WIDTH, 0);
	isAvaliable = false;
}