#pragma once
#include "Character.h"

class Mushroom : public Character
{
public:
	Mushroom(SDL_Renderer* renderer, string imagePath, Vector2D startpos, LevelMap* map);
	~Mushroom();

	void Update(float deltaTime, SDL_Event e);
	void Render();
	void MoveLeft(float deltaTime);
	void MoveRight(float deltaTime);
};