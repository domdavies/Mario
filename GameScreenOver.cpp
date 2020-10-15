#include "GameScreenOver.h"
#include "Constants.h"
#include <iostream>

using namespace::std;

GameScreenOver::GameScreenOver(SDL_Renderer* renderer) : GameScreen(renderer)
{
	mBackGroundTexture = NULL;
	SetUpGameOver();
}

GameScreenOver::~GameScreenOver()
{
	delete mBackGroundTexture;
	mBackGroundTexture = NULL;
}

void GameScreenOver::Render()
{
	SDL_Rect srcRect = { 0, 0, 500, 500 };
	SDL_Rect destRect = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };
	mBackGroundTexture->Render(srcRect, destRect, SDL_FLIP_NONE, 0);
}

void GameScreenOver::Update(float deltaTime, SDL_Event e)
{
}

bool GameScreenOver::SetUpGameOver()
{
	mBackGroundTexture = new Texture2D(mRenderer);
	if (!mBackGroundTexture->LoadFromFile("Images/GameOver.png"))
	{
		cout << "Couldnt load the intro image";
		return false;
	}
	return true;
}
