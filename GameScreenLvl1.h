#ifndef _GAMESCREENLVL_H
#define _GAMESCREENLVL_H

#include <SDL.h>
#include "Commons.h"
#include "GameScreen.h"
#include "Character.h"
#include "Mario.h"
#include "Luigi.h"
#include "LevelMap.h"
#include "PowBlock.h"
#include "Koopa.h"
#include "Coin.h"
#include <vector>
#include "GameScreenManager.h"

//we use this so we can gain access to the Texture2D functions, to create textures
class Texture2D;
class Character;
class Collisions;


class GameScreenLvl1 : GameScreen {
public:
	GameScreenLvl1(SDL_Renderer* renderer);
	~GameScreenLvl1();

	void Render();
	void Update(float deltaTime, SDL_Event e);

	bool IsComplete() { return _isComplete; };
	bool IsFailed() { return _isFailed; };
private:
	void SetLevelMap();
	bool SetUpLvl();
	void DoScreenShake();
	void SetUpCoins();
	void UpdateBackGround(float deltaTime);
	void SetUpEnemies(float deltaTime);
	void UpdatePowBlock();
	void UpdateEnemies(float deltaTime, SDL_Event e);
	void CreateKoopa(Vector2D startPos, float patrolA, float patrolB);
	void CreateCoin(Vector2D startPos);
	void UpdateCoins(float deltaTime);

	//variable to hold the background texture of this screen
	Texture2D* mBackGroundTexture, *scoreTexture;

	//variable that store the character, to be shown in the level
	Mario* mario;
	Luigi* luigi;
	Collisions* collision;
	LevelMap* mLevelMap;
	PowBlock* mPowBlock[2];
	Koopa* koopa;
	Coin* coin;

	bool mScreenShake;
	float mScreenShakeDuration;
	float mWobble;
	float mBackgroundYPos;
	int score;

	string str;

	vector <Koopa*> mEnemies;
	vector <Coin*> mCoins;

	float enemyTimer;
};
#endif // !GAMEscreenlvl1_h