#ifndef  _KOOPA_H
#define _KOOPA_H

#include "Character.h"

class Koopa : public Character
{
public:
	Koopa(SDL_Renderer* renderer, string imagePath, Vector2D startpos, LevelMap* map, float patrolA, float patrolB);
	~Koopa();
	void Update(float deltaTime, SDL_Event e);
	void Render();
	void TakeDamage();
	void Jump();
	void Patrol(float deltaTime, float pointA, float pointB);

	void MoveLeft(float deltaTime);
	void MoveRight(float deltaTime);
	void SetAlive(bool alive);
    bool GetAlive() { return _alive; };
	bool IsInjured() { return mInjured; }
private:
	bool mInjured;
	float mInjuredTime;

	void FlipRightWay();

	bool notMoving;
	bool _alive;
	float pointA, pointB;
};
#endif // ! _KOOPA_H