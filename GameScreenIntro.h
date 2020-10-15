#ifndef _GAMESCREENINTRO_H
#define _GAMESCREENINTRO_H

#include <SDL.h>
#include "Commons.h"
#include "GameScreen.h"

//we use this so we can gain access to the Texture2D functions, to create textures
class Texture2D;

class GameScreenIntro : GameScreen {
public:
	GameScreenIntro(SDL_Renderer* renderer);
	~GameScreenIntro();
	void Render();
	void Update(float deltaTime, SDL_Event e);
	bool IsComplete() { return _isComplete; };
private:
	bool SetUpIntro();

	Texture2D* mBackGroundTexture;
	Texture2D* scroller;
	int scrollerPosY;
};
#endif 