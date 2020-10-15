#ifndef _GAMESCREENLVL2_H
#define _GAMESCREENLVL2_H

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
#include "SupriseBlock.h"
#include "Mushroom.h"
#include "BreakableBlock.h"

//we use this so we can gain access to the Texture2D functions, to create textures
class Texture2D;
class Character;
class Collisions;


class GameScreenLvl2 : GameScreen {
public:
	GameScreenLvl2(SDL_Renderer* renderer);
	~GameScreenLvl2();

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
	void UpdateEnemies(float deltaTime, SDL_Event e);
	void CreateKoopa(Vector2D startPos, float patrolA, float patrolB);
	void CreateCoin(Vector2D startPos);
	void UpdateCoins(float deltaTime);
	void UpdateSupriseBlock();
	void UpdateBreakableBlock();

	//variable to hold the background texture of this screen
	Texture2D* mBackGroundTexture;

	//variable that store the character, to be shown in the level
	Mario* mario;
	Collisions* collision;
	LevelMap* mLevelMap;
	Koopa* koopa;
	Coin* coin;
	SupriseBlock* block;
	Mushroom* mushroom;
	BreakableBlock* breakableBlock[4];

	SDL_Rect camera;

	bool mScreenShake;
	float mScreenShakeDuration;
	float mWobble;
	float mBackgroundYPos;

	vector <Koopa*> mEnemies;
	vector <Coin*> mCoins;

	float enemyTimer;
};
#endif // !GAMEscreenlvl1_h