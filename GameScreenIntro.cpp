#include "GameScreenIntro.h"
#include "Texture2D.h"
#include <iostream>
#include "GameScreen.h"
#include "Constants.h"

using namespace::std;

GameScreenIntro::GameScreenIntro(SDL_Renderer* renderer) : GameScreen(renderer) {
	mBackGroundTexture = NULL;
	scroller = NULL;
	_isComplete = true;
	SetUpIntro();
	scrollerPosY = 402;
}

GameScreenIntro::~GameScreenIntro() {
	delete mBackGroundTexture;
	mBackGroundTexture = NULL;

	delete scroller;
	scroller = NULL;
}

void GameScreenIntro::Update(float deltaTime, SDL_Event e) {
	switch (e.type)
	{
	case SDL_KEYDOWN:
		switch (e.key.keysym.sym)
		{
		case SDLK_UP:
			if (scrollerPosY == 402)
			{
				scrollerPosY = 460;
			}
			else {
				scrollerPosY = 402;
			}
			break;

		case SDLK_DOWN:
			if (scrollerPosY == 460)
			{
				scrollerPosY = 402;
			}
			else {
				scrollerPosY = 460;
			}
			break;
		}
	}
	if (scrollerPosY == 402)
	{
		//players = ONE_PLAYER;
	}
	else
	{
		//players = TWO_PLAYER;
	}
}

void GameScreenIntro::Render() {
	SDL_Rect srcRect = { 0, 0, START_WIDTH, START_HEIGHT };
	SDL_Rect destRect = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };
	mBackGroundTexture->Render(srcRect, destRect, SDL_FLIP_NONE, 0);

	SDL_Rect srcRectScroller = { 0, 0, 7, 7 };
	SDL_Rect destRectScroller = { 100, scrollerPosY, 22, 30 };
	scroller->Render(srcRectScroller, destRectScroller, SDL_FLIP_NONE, 0);
}

bool GameScreenIntro::SetUpIntro() {
	mBackGroundTexture = new Texture2D(mRenderer);
	if (!mBackGroundTexture->LoadFromFile("Images/SpriteSheet.png"))
	{
		cout << "Couldnt load the intro image";
		return false;
	}
	scroller = new Texture2D(mRenderer);
	if (!scroller->LoadFromFile("Images/Scroller.png"))
	{
		cout << "Couldnt load the intro image";
		return false;
	}
	return true;
}