#ifndef _LUIGI_H
#define _LUIGI_H
#include "Character.h"

class Luigi : public Character {
public:
	//pass the renderer pointer, imagepath, startPosition and levelMap
	Luigi(SDL_Renderer* renderer, string imagePath, Vector2D startpos, LevelMap* map);
	~Luigi();
	void Update(float deltaTime, SDL_Event e);
	void Render();
private:
};

#endif // !_LUIGI_H
