#include "GameScreen.h"
#include"GameScreenManager.h"
#include <SDL.h>
#include "GameScreenLvl1.h"
#include "GameScreenLvl2.h"
#include "GameScreenIntro.h"
#include "GameScreenOver.h"

GameScreenManager::GameScreenManager(SDL_Renderer* renderer, SCREENS startScreen) {
	mRenderer = renderer;
	mCurrentScreen = NULL;
	myScreen = startScreen;
	//call the first screen to be set up when loaded
	changScreen(startScreen);
}

GameScreenManager::~GameScreenManager() {
	mRenderer = NULL;

	delete mCurrentScreen;
	mCurrentScreen = NULL;
}

void GameScreenManager::Render() {
	mCurrentScreen->Render();
}

void GameScreenManager::Update(float deltaTime, SDL_Event e) {
	mCurrentScreen->Update(deltaTime, e);

	if (mCurrentScreen->IsComplete())
	{
		if (myScreen == SCREEN_LVL1)
		{
			//cout << "Complete" << endl;
			changScreen(SCREEN_LVL2);
		}
	}
	else
		//cout << "Incomplete" << endl;

	if (mCurrentScreen->IsFailed())
	{
		changScreen(SCREEN_GAMEOVER);
	}
	if (myScreen == SCREEN_GAMEOVER)
	{
		//handdle events
		switch (e.type)
		{
			//keyboard input
		case SDL_KEYDOWN:
			switch (e.key.keysym.sym)
			{
			case SDLK_r:
				changScreen(SCREEN_LVL1);
				break;
			default:
				break;
			}
		}
	}
}

void GameScreenManager::changScreen(SCREENS newScreen) {
	myScreen = newScreen;
	//clears the old screen
	if (mCurrentScreen != NULL)
	{
		delete mCurrentScreen;
	}

	GameScreenLvl1* tempLvl1Screen;
	GameScreenIntro* tempIntroScreen;
	GameScreenOver* tempGameOverScreen;
	GameScreenLvl2* tempLvl2Screen;

	switch (newScreen)
	{
		case SCREEN_INTRO:
			tempIntroScreen = new GameScreenIntro(mRenderer);
			mCurrentScreen = (GameScreen*)tempIntroScreen;
			tempIntroScreen = NULL;
			break;
		case SCREEN_LVL1:
			tempLvl1Screen = new GameScreenLvl1(mRenderer);
			mCurrentScreen = (GameScreen*)tempLvl1Screen;
			tempLvl1Screen = NULL;
			break;
		case SCREEN_GAMEOVER:
			tempGameOverScreen = new GameScreenOver(mRenderer);
			mCurrentScreen = (GameScreen*)tempGameOverScreen;
			tempGameOverScreen = NULL;
			break;
		case SCREEN_LVL2:
			tempLvl2Screen = new GameScreenLvl2(mRenderer);
			mCurrentScreen = (GameScreen*)tempLvl2Screen;
			tempLvl2Screen = NULL;
			break;
		break;	
	}
}