#include "GameScreenLvl1.h"
#include <iostream>
#include "Texture2D.h"
#include "GameScreen.h"
#include "Collisions.h"
#include "GameScreenIntro.h"

using namespace::std;

GameScreenLvl1::GameScreenLvl1(SDL_Renderer* renderer) : GameScreen(renderer) {
	collision = NULL;
	luigi = NULL;
	mBackGroundTexture = NULL;
	scoreTexture = NULL;
	mario = NULL;
	mLevelMap = NULL;
	enemyTimer = ENEMY_TIMER;
	SetUpLvl();
	//could use an enum as need to check 3 states. COMPLETE, FAILED, IN_PROGRESS
	_isComplete = false;
	_isFailed = false;
	score = 0;
}

GameScreenLvl1::~GameScreenLvl1() {
	delete mBackGroundTexture;
	mBackGroundTexture = NULL;

	delete scoreTexture;
	scoreTexture = NULL;

	delete mario;
	mario = NULL;

	delete luigi;
	luigi = NULL;

	for (int i = 0; i < 2; i++)
	{
		delete mPowBlock[i];
		mPowBlock[i] = NULL;
	}

	mEnemies.clear();
	mCoins.clear();
}

void GameScreenLvl1::Render() {
	//draws the background
	mBackGroundTexture->Render(Vector2D(0, mBackgroundYPos), SDL_FLIP_NONE);
	for (int i = 0; i < 2; i++)
	{
		mPowBlock[i]->Render();

	}
	mario->Render();
	if (luigi != NULL)
	{
		luigi->Render();
	}
	for (unsigned int i = 0; i < mEnemies.size(); i++)
	{
		mEnemies[i]->Render();
	}

	for (unsigned int i = 0; i < mCoins.size(); i++)
	{
		mCoins[i]->Render();
	}
	scoreTexture->Render(Vector2D(0, 470), SDL_FLIP_NONE);
}
void GameScreenLvl1::Update(float deltaTime, SDL_Event e) {
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
	SetUpEnemies(deltaTime);

	mario->Update(deltaTime, e);
	if (luigi != NULL)
	{
		luigi->Update(deltaTime, e);
	}
	UpdateBackGround(deltaTime);
	UpdateCoins(deltaTime);
	UpdatePowBlock();
	UpdateEnemies(deltaTime, e);
	SDL_Color red = { 255, 0, 0 };
	str = to_string(score);
	scoreTexture->LoadText("arial.ttf", 24, "SCORE: " + str, red);
}

void GameScreenLvl1::UpdateCoins(float deltaTime) {
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
			{
				score += 10;
				//delete any any coin that is collected
				coinIndexToDelete = i;
			}
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

void GameScreenLvl1::UpdateEnemies(float deltaTime, SDL_Event e) {
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

			if ((mEnemies[i]->GetPosition().y > 300.0f  || mEnemies[i]->GetPosition().y <= 64.0f) &&
				(mEnemies[i]->GetPosition().x < 64.0f || mEnemies[i]->GetPosition().y > SCREEN_WIDTH-96.0f))
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
						if (mEnemies[i]->IsInjured())
						{
							//set enemy status to dead
							mEnemies[i]->SetAlive(false);
							score += 100;
						}
						else
						{
							mario->Jump();
							mEnemies[i]->TakeDamage();
						}
					}
					else //if koopa hits mario
					{
						mario->SetState(PLAYER_DEATH);
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

void GameScreenLvl1::UpdatePowBlock(){
	for (int i = 0; i < 2; i++)
	{
		if (Collisions::Instance()->Box(mario->GetCollisionBox(), mPowBlock[i]->GetCollisonBox()))
		{
			if (mPowBlock[i]->IsAvaliable())
			{
				if (mario->IsJumping())
				{
					DoScreenShake();
					mPowBlock[i]->TakeHit();
					for (int i = 0; i < mEnemies.size(); i++)
					{
						mEnemies[i]->Jump();
					}
					mario->CancelJump();
				}
			}
		}
	}
}

void GameScreenLvl1::CreateKoopa(Vector2D startPos, float patrolA, float patrolB) {
	koopa = new Koopa(mRenderer, "Images/Koopa.png", startPos, mLevelMap, patrolA, patrolB);
	mEnemies.push_back(koopa);
}

void GameScreenLvl1::CreateCoin(Vector2D startPos) {
	coin = new Coin(mRenderer, "Images/Coin.png", startPos, mLevelMap);
	mCoins.push_back(coin);
}

void GameScreenLvl1::SetLevelMap() {
	int map[MAP_HEIGHT][MAP_WIDTH] = {
		{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
		{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
		{ 1,1,1,1,1,1,0,0,0,0,1,1,1,1,1,1 },
		{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
		{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
		{ 0,0,0,0,1,1,1,1,1,1,1,1,0,0,0,0 },
		{ 1,1,0,0,0,0,0,0,0,0,0,0,0,0,1,1 },
		{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
		{ 0,0,0,0,0,0,0,2,2,0,0,0,0,0,0,0 },
		{ 1,1,1,1,1,1,0,0,0,0,1,1,1,1,1,1 },
		{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
		{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
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

void GameScreenLvl1::DoScreenShake() {
	mScreenShake = true;
	mScreenShakeDuration = SCREEN_SHAKE_TIME;
	mWobble = 0.0f;
}

void GameScreenLvl1::SetUpCoins()
{
	//mid left coins
	CreateCoin(Vector2D(8, 168));
	CreateCoin(Vector2D(40, 168));
	//mid right coins
	CreateCoin(Vector2D(460, 168));
	CreateCoin(Vector2D(490, 168));
	//middle coins
	CreateCoin(Vector2D(136, 136));
	CreateCoin(Vector2D(168, 136));
	CreateCoin(Vector2D(200, 136));
	CreateCoin(Vector2D(232, 136));
	CreateCoin(Vector2D(264, 136));
	CreateCoin(Vector2D(296, 136));
	CreateCoin(Vector2D(328, 136));
	CreateCoin(Vector2D(360, 136));
	//top left coins
	CreateCoin(Vector2D(74, 40));
	CreateCoin(Vector2D(106, 40));
	CreateCoin(Vector2D(138, 40));
	CreateCoin(Vector2D(170, 40));
	//top right coins
	CreateCoin(Vector2D(330, 40));
	CreateCoin(Vector2D(362, 40));
	CreateCoin(Vector2D(394, 40));
	CreateCoin(Vector2D(426, 40));
	//bottom left coins 
	CreateCoin(Vector2D(8, 264));
	CreateCoin(Vector2D(40, 264));
	CreateCoin(Vector2D(74, 264));
	CreateCoin(Vector2D(106, 264));
	CreateCoin(Vector2D(138, 264));
	CreateCoin(Vector2D(170, 264));
	//bottom right coins
	CreateCoin(Vector2D(330, 264));
	CreateCoin(Vector2D(362, 264));
	CreateCoin(Vector2D(394, 264));
	CreateCoin(Vector2D(426, 264));
	CreateCoin(Vector2D(458, 264));
	CreateCoin(Vector2D(490, 264));
}

void GameScreenLvl1::UpdateBackGround(float deltaTime)
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

void GameScreenLvl1::SetUpEnemies(float deltaTime)
{
	enemyTimer -= deltaTime;
	if (enemyTimer <= 0)
	{
		CreateKoopa(Vector2D(96, 330), 90, 400);
		CreateKoopa(Vector2D(10, 200), 10, 150);
		CreateKoopa(Vector2D(500, 200), 340, 480);
		CreateKoopa(Vector2D(10, 30), 10, 480);
		CreateKoopa(Vector2D(480, 30), 10, 480);
		enemyTimer = ENEMY_TIMER;
	}
}

bool GameScreenLvl1::SetUpLvl() {
	SetLevelMap();
	mBackGroundTexture = new Texture2D(mRenderer);
	if (!mBackGroundTexture->LoadFromFile("Images/BackgroundMB.png"))
	{
		cout << "Failed to load background textur";
		return false;
	}
	mPowBlock[0] = new PowBlock(mRenderer, mLevelMap, Vector2D(256, 260));
	mPowBlock[1] = new PowBlock(mRenderer, mLevelMap, Vector2D(224, 260));
	mScreenShake = false;
	mBackgroundYPos = 0.0f;
	if (mPowBlock == NULL)
	{
		cout << "block didnt load";
	}
	//sets this characters start position
	mario = new Mario(mRenderer, "Images/MarioSprites.png", Vector2D(64, 320), mLevelMap);
	if (mario == NULL)
	{
		cout << "Character didnt load";
	}
	//luigi = new Luigi(mRenderer, "Images/Luigi.png", Vector2D(64, 330), mLevelMap);
	SetUpCoins();
	scoreTexture = new Texture2D(mRenderer);
	return true;
}