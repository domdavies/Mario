#pragma once
#include "GameScreen.h"
#include "Texture2D.h"
#include "GameScreenManager.h"

class GameScreenOver : GameScreen {
public:
	GameScreenOver(SDL_Renderer* renderer);
	~GameScreenOver();
	void Render();
	void Update(float deltaTime, SDL_Event e);
private:
	bool SetUpGameOver();

	GameScreenManager* gameScreenManager;
	Texture2D* mBackGroundTexture;
};