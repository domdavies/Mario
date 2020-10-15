#ifndef _GAMESCREEN_H
#define _GAMESCREEN_H

#include <SDL.h>

class GameScreen {
public:
	GameScreen(SDL_Renderer* renderer);
	~GameScreen();

	virtual void Render();
	virtual void Update(float deltaTime, SDL_Event e);
	virtual bool IsComplete() { return _isComplete; };
	virtual bool IsFailed() { return _isFailed; };
private:
protected:
	//a render used by any gamescreen that inherits from the GameScreen class
	SDL_Renderer* mRenderer;
	bool _isComplete;
	bool _isFailed;
};
#endif // !_GAMESCREEN_H