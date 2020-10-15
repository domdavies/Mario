#include "GameScreenLvl2.h"
#include <iostream>
#include "Texture2D.h"
#include "GameScreen.h"
#include "Collisions.h"

using namespace::std;

GameScreenLvl2::GameScreenLvl2(SDL_Renderer* renderer) : GameScreen(renderer) {
	collision = NULL;
	mBackGroundTexture = NULL;
	mario = NULL;
	mLevelMap = NULL;
	block = NULL;
	mushroom = NULL;
	SetUpLvl();
	//could use an enum as need to check 3 states. COMPLETE, FAILED, IN_PROGRESS
	_isComplete = false;
	_isFailed = false;

	camera = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };
}

GameScreenLvl2::~GameScreenLvl2() {
	delete mBackGroundTexture;
	mBackGroundTexture = NULL;

	delete mario;
	mario = NULL;

	delete block;
	block = NULL;

	mEnemies.clear();
	mCoins.clear();
}

void GameScreenLvl2::Render() {
	//draws the background
	mBackGroundTexture->Render(Vector2D(0, mBackgroundYPos), SDL_FLIP_NONE);
	block->Render();
	if (mushroom != NULL)
	{
		mushroom->Render();
	}
	for (int i = 0; i < 4; i++)
	{
		if (breakableBlock[i]->IsAvaliable())
		{
			breakableBlock[i]->Render();
		}
	}
	mario->Render();
	for (unsigned int i = 0; i < mEnemies.size(); i++)
	{
		mEnemies[i]->Render();
	}

	for (unsigned int i = 0; i < mCoins.size(); i++)
	{
		mCoins[i]->Render();
	}

}
void GameScreenLvl2::Update(float deltaTime, SDL_Event e) {
	if (mario->GetState() == PLAYER_DEATH)
	{
		mario->PlayDeathAnim(deltaTime);
		if (mario->GetPosition().y >= SCREEN_HEIGHT)
		{
			_isFailed = true;
			mario->SetState(PLAYER_SMALL);
		}
	}
	else
	{
		_isFailed = false;
	}
	UpdateEnemies(deltaTime, e);
	mario->Update(deltaTime, e);
	UpdateSupriseBlock();
	if (mushroom != NULL)
	{
		mushroom->Update(deltaTime, e);
		if (Collisions::Instance()->Box(mario->GetCollisionBox(), mushroom->GetCollisionBox()))
		{
			mushroom = NULL;
			mario->Grow();
		}
	}

	UpdateBreakableBlock();
	UpdateBackGround(deltaTime);
	UpdateCoins(deltaTime);
}

void GameScreenLvl2::UpdateCoins(float deltaTime) {
	if (!mCoins.empty())
	{
		int coinIndexToDelete = -1;
		for (int i = 0; i < mCoins.size(); i++)
		{
			mCoins[i]->Update(deltaTime);

			if (Collisions::Instance()->Box(mario->GetCollisionBox(), mCoins[i]->GetCollisionBox()))
			{
				mCoins[i]->SetCollected(true);
			}

			if (mCoins[i]->Getcollected())
				//score += 100;
				//delete any any coin that is collected
				coinIndexToDelete = i;
		}
		if (coinIndexToDelete != -1)
		{
			mCoins.erase(mCoins.begin() + coinIndexToDelete);
		}
	}
	else
	{
		_isComplete = true;
	}
}

void GameScreenLvl2::UpdateSupriseBlock()
{
	if (block->IsAvaliable())
	{
		if (Collisions::Instance()->Box(mario->GetCollisionBox(), block->GetCollisonBox()))
		{
			block->TakeHit();
			mushroom = new Mushroom(mRenderer, "Images/Mushroom.png", Vector2D(96, 224), mLevelMap);
			mario->CancelJump();
		}
	}
}

void GameScreenLvl2::UpdateBreakableBlock()
{
	if (mario->GetState() == PLAYER_LARGE)
	{
		for (int i = 0; i < 4; i++)
		{
			if (breakableBlock[i]->IsAvaliable())
			{
				if (Collisions::Instance()->Box(mario->GetCollisionBox(), breakableBlock[i]->GetCollisonBox()))
				{
					breakableBlock[i]->TakeHit();
					mario->CancelJump();
				}
			}
		}
	}
	else
	{
		for (int i = 0; i < 4; i++)
		{
			if (Collisions::Instance()->Box(mario->GetCollisionBox(), breakableBlock[i]->GetCollisonBox()))
			{
				mario->CancelJump();
			}
		}
	}
}

void GameScreenLvl2::UpdateEnemies(float deltaTime, SDL_Event e) {
	if (!mEnemies.empty())
	{
		int enemyIndexToDelete = -1;
		for (unsigned int i = 0; i < mEnemies.size(); i++)
		{
			if (mEnemies[i]->GetPosition().y > 300.0f)
			{
				if (mEnemies[i]->GetPosition().x  < (float)(-mEnemies[i]->GetCollisionBox().w * 0.5) ||
					mEnemies[i]->GetPosition().x > SCREEN_WIDTH - (float)(mEnemies[i]->GetCollisionBox().w * 0.55))
					mEnemies[i]->SetAlive(false);
			}

			mEnemies[i]->Update(deltaTime, e);

			if ((mEnemies[i]->GetPosition().y > 300.0f || mEnemies[i]->GetPosition().y <= 64.0f) &&
				(mEnemies[i]->GetPosition().x < 64.0f || mEnemies[i]->GetPosition().y > SCREEN_WIDTH - 96.0f))
			{

			}
			else
			{
				if (Collisions::Instance()->Box(mario->GetCollisionBox(), mEnemies[i]->GetCollisionBox()))
				{
					//if mario jumps on koopa
					//once, injure koopa
					//if there is a collision between mario and the Kroopa, while the Kroopa is injured
					if (mario->InAir())
					{
						if (!mEnemies[i]->IsInjured())
						{
							mario->Jump();
							mEnemies[i]->TakeDamage();
						}
						else
						{
							//set enemy status to dead
							mEnemies[i]->SetAlive(false);
						}
					}
					else //if koopa hits mario
					{
						if (mario->GetState() == PLAYER_LARGE)
						{
							mario->Shrink();
						}
						else
						{
							mario->SetState(PLAYER_DEATH);
						}
					}
				}
			}
			if (!mEnemies[i]->GetAlive())
				//delete any anymies that are dead
				enemyIndexToDelete = i;
		}
		if (enemyIndexToDelete != -1)
		{
			mEnemies.erase(mEnemies.begin() + enemyIndexToDelete);
		}
	}
}

void GameScreenLvl2::CreateKoopa(Vector2D startPos, float patrolA, float patrolB) {
	koopa = new Koopa(mRenderer, "Images/Koopa.png", startPos, mLevelMap, patrolA, patrolB);
	mEnemies.push_back(koopa);
}

void GameScreenLvl2::CreateCoin(Vector2D startPos) {
	coin = new Coin(mRenderer, "Images/Coin.png", startPos, mLevelMap);
	mCoins.push_back(coin);
}

void GameScreenLvl2::SetLevelMap() {
	int map[MAP_HEIGHT][MAP_WIDTH] = {
		{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
		{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
		{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
		{ 0,0,0,0,0,2,0,0,0,0,0,0,0,0,0,0 },
		{ 0,0,0,0,0,2,0,0,0,0,0,0,0,0,0,0 },
		{ 0,0,0,0,0,2,0,0,0,0,0,0,0,0,0,0 },
		{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
		{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
		{ 1,1,1,2,2,1,1,1,0,0,0,0,0,0,1,1 },
		{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1 },
		{ 0,0,0,0,0,0,0,0,0,0,1,1,0,0,1,1 },
		{ 0,0,0,0,0,0,0,0,0,0,1,1,0,0,1,1 },
		{ 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 }
	};
	//clears the old map, if there is one
	if (mLevelMap != NULL)
	{
		delete mLevelMap;
	}
	//sets the new one
	mLevelMap = new LevelMap(map);
}

void GameScreenLvl2::DoScreenShake() {
	mScreenShake = true;
	mScreenShakeDuration = SCREEN_SHAKE_TIME;
	mWobble = 0.0f;
}

void GameScreenLvl2::SetUpCoins()
{

}

void GameScreenLvl2::UpdateBackGround(float deltaTime)
{
	if (mScreenShake)
	{
		mScreenShakeDuration -= deltaTime;
		mWobble++;
		mBackgroundYPos = sin(mWobble);
		mBackgroundYPos *= 3.0f;

		if (mScreenShakeDuration <= 0.0f)
		{
			mScreenShake = false;
			mBackgroundYPos = 0.0f;
		}
	}
}

void GameScreenLvl2::SetUpEnemies(float deltaTime)
{

}

bool GameScreenLvl2::SetUpLvl() {
	SetLevelMap();
	mBackGroundTexture = new Texture2D(mRenderer);
	if (!mBackGroundTexture->LoadFromFile("Images/BackgroundL2.png"))
	{
		cout << "Failed to load background textur";
		return false;
	}
	mScreenShake = false;
	mBackgroundYPos = 0.0f;

	block = new SupriseBlock(mRenderer, mLevelMap, Vector2D(96, 256));

	breakableBlock[0] = new BreakableBlock(mRenderer, mLevelMap, Vector2D(128, 256));
	breakableBlock[1] = new BreakableBlock(mRenderer, mLevelMap, Vector2D(160, 160));
	breakableBlock[2] = new BreakableBlock(mRenderer, mLevelMap, Vector2D(160, 128));
	breakableBlock[3] = new BreakableBlock(mRenderer, mLevelMap, Vector2D(160, 96));
	//sets this characters start position
	mario = new Mario(mRenderer, "Images/MarioSprites.png", Vector2D(64, 320), mLevelMap);
	if (mario == NULL)
	{
		cout << "Character didnt load";
	}
	SetUpCoins();
	CreateKoopa(Vector2D(32, 220), 10, 160);
	return true;
}