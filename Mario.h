#ifndef _MARIO_H
#define _MARIO_H

#include "Character.h"
#include "SoundManager.h"

class Mario : public Character{
public:
	//pass the renderer pointer, imagepath, startPosition and levelMap
	Mario(SDL_Renderer* renderer, string imagePath, Vector2D startpos, LevelMap* map);
	~Mario();
	void Update(float deltaTime, SDL_Event e);
	void Render();
	void SetState(PLAYERSTATE playerState) { _playerState = playerState; };
   	PLAYERSTATE GetState() { return _playerState; };
	void PlayDeathAnim(float deltaTime);
	void Grow();
	void Shrink();
private:
	bool jump;
	Mix_Chunk* deathSound;
	Mix_Chunk* jumpSound;
	SoundManager* soundManager;
};

#endif // !_MARIO_H