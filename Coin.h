#pragma once

#include "Character.h"

class Coin : public Character
{
public:
	Coin(SDL_Renderer* renderer, string imagePath, Vector2D startpos, LevelMap* map);
	~Coin();
	void Update(float deltaTime);
	void Render();
	void SetCollected(bool isCollected);
	bool Getcollected() {return _isCollected ; };
private:
	int mFrameDelay;
	int mCurrentFrame;
	float mSingleSpriteWidth;
	float mSingleSpriteHeight;
	bool _isCollected;
};

