#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include "Constants.h"
#include <iostream>
#include "Texture2D.h"
#include "Commons.h"
#include "GameScreenManager.h"
#include <SDL_mixer.h>
#include <SDL_ttf.h>

using namespace std;
GameScreenManager* gameScreenManager;
Uint32	 gOldTime;
SDL_Window* gWindow = NULL;
SDL_Renderer* gRenderer = NULL;
Mix_Music* gMusic = NULL;
bool loaded = false;

//function prototypes
bool InitSDL();
void CloseSDL();
bool Update();
void LoadMusic(string path);

void Render();

int main(int argc, char* aargv[])
{
	//check if the SDL was set up correctly
	if (InitSDL())
	{
		TTF_Init();
		LoadMusic("Music/Mario.wav");

		if (Mix_PlayingMusic() == 0)
		{
			Mix_PlayMusic(gMusic, -1);
		}
	
		//start with the Intro Scree
		gameScreenManager = new GameScreenManager(gRenderer, SCREEN_INTRO);
		//sets the start time
		gOldTime = SDL_GetTicks();

		bool quit = false;
		while (!quit)
		{
			Render();
			quit = Update();
		}
	}

	//close and free recources
	CloseSDL();
	return 0;
}

void LoadMusic(string path)
{
	gMusic = Mix_LoadMUS(path.c_str());

	if (gMusic == NULL)
	{
		cout << "Failed to load background music: " << Mix_GetError() << endl;
	}
}

bool InitSDL()
{
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		cout << "SDL did not initialise. Error: " << SDL_GetError();
		return false;
	}
	else
	{
		//create the window
		gWindow = SDL_CreateWindow("Mario", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);

		if (gRenderer != NULL)
		{
			int imageFlages = IMG_INIT_PNG;
			if (!(IMG_Init(imageFlages) & imageFlages))
			{
				cout << "SDL image could not initialize. ERROR: " << IMG_GetError();
				return false;
			}
		}
		else
		{
			cout << "Renderer could not initialize. ERROR: " << SDL_GetError();
			return false;
		}

		if (gWindow == NULL)
		{
			cout << "Window was not created. Error: " << SDL_GetError();
			return false;
		}

		if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
		{
			cout << "Mixer could not initialize. Error: " << Mix_GetError() << endl;
			return false;
		}
		else
			return true;
	}
}

void CloseSDL() {
	//release the window
	SDL_DestroyWindow(gWindow);
	gWindow = NULL;

	SDL_DestroyRenderer(gRenderer);
	gRenderer = NULL;

	//destroy the game screen
	delete gameScreenManager;
	gameScreenManager = NULL;

	Mix_FreeMusic(gMusic);
	gMusic = NULL;

	//quit SDL subsystems
	IMG_Quit();
	TTF_Quit();
	SDL_Quit();
}

bool Update() {
	Uint32 newTime = SDL_GetTicks();
	//Eventhandler
	SDL_Event e;

	SDL_PollEvent(&e);

	//handdle events
	switch (e.type)
	{
		//CLICK the "x" to quit
	case SDL_QUIT:
		return true;
	break;
	//keyboard input
	case SDL_KEYDOWN:
		switch (e.key.keysym.sym)
		{
		//if the space key is down, then load level 1
		case SDLK_SPACE:
			if (!loaded)
			{
				gameScreenManager->changScreen(SCREEN_LVL1);
				loaded = true;
			}
			break;
		default:
			break;
		}
		break;
	}

	gameScreenManager->Update((float)(newTime - gOldTime) / 1000.0f, e);
	gOldTime = newTime;
	return false;
}

void Render()
{
	//sets the color
	SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
	SDL_RenderClear(gRenderer);
	gameScreenManager->Render();
	SDL_RenderPresent(gRenderer);
}