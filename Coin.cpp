#include "Coin.h"
#include "Texture2D.h"

Coin::Coin(SDL_Renderer* renderer, string imagePath, Vector2D startpos, LevelMap* map) : Character(renderer, imagePath, startpos, map)
{
	mSingleSpriteWidth = COIN_SPRITE_WIDTH / 3;
	mSingleSpriteHeight = COIN_SPRITE_HEIGHT;
	_isCollected = false;
}

Coin::~Coin()
{

}

void Coin::Update(float deltaTime)
{
	mFrameDelay -= deltaTime;
	if (mFrameDelay <= 0.0f)
	{
		mFrameDelay = ANIMATION_DELAY;
		mCurrentFrame++;
		if (mCurrentFrame > 2)
		{
			mCurrentFrame = 0;
		}
	}
}

void Coin::Render()
{
	SDL_Rect portionofSpriteSheet = { mSingleSpriteWidth * mCurrentFrame, 0, mSingleSpriteWidth, mSingleSpriteHeight };
	SDL_Rect dest = { (int)mPosition.x, (int)mPosition.y, mSingleSpriteWidth, mSingleSpriteHeight };

	mTexture->Render(portionofSpriteSheet, dest, SDL_FLIP_NONE, 0);
}

void Coin::SetCollected(bool isCollected) {
	_isCollected = isCollected;
}