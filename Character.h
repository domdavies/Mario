#ifndef _CHARACTER_H
#define _CHARACTER_H

#include <SDL.h>
#include <iostream>
#include "Commons.h"
#include "LevelMap.h"

using namespace::std;

class Texture2D;

class Character {
public:
	Character(SDL_Renderer* renderer, string imagePath, Vector2D startpos, LevelMap* map);
	~Character();

	virtual void Render();
	virtual void Update(float deltaTime, SDL_Event e);

	void SetPosition(Vector2D newPosition);
	Vector2D GetPosition();

	float GetCollisionRadius();
	Rect2D GetCollisionBox();
	void AddGravity(float deltaTime);
	void CancelJump();
	bool IsJumping() { return mJumping; };
	bool InAir() { return isAir; };
	void Jump();
	PLAYERSTATE GetState() { return _playerState; };
private:
protected:
	SDL_Renderer* mRenderer;
	Vector2D mPosition;
	Texture2D* mTexture;
	LevelMap* mCurrentLevelMap;

	FACING mFacingDirection;
	PLAYERSTATE _playerState;

	float collisionRadius;
	float mJumpForce;

	bool movingRight;
	bool movingLeft;
	bool mJumping;
	bool mCanJump;
	bool isAir;

	int frameCount, currentFrame;
	int singleSpriteWidth, singleSpriteHeight;
	float size;

	virtual void MoveRight(float deltaTime);
	virtual void MoveLeft(float deltaTime);
};

#endif // !_CHARACTER_H
