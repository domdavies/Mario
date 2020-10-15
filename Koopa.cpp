#include "Koopa.h"
#include "Texture2D.h"

Koopa::Koopa(SDL_Renderer* renderer, string imagePath, Vector2D startpos, LevelMap* map, float patrolA, float patrolB) : Character(renderer, imagePath, startpos, map){
	singleSpriteWidth = KOOPA_SPRITE_WIDTH;
	singleSpriteHeight = KOOPA_SPRITE_HEIGHT;
	mInjured = false;
	mInjuredTime = INJURED_TIME;
	movingLeft = true;
	notMoving = false;
	_alive = true;

	pointA = patrolA;
	pointB = patrolB;
}

Koopa::~Koopa() {

}

void Koopa::Update(float deltaTime, SDL_Event e) {
	Character::Update(deltaTime, e);
	
	if (mInjured)
	{
		movingLeft = false;
		movingRight = false;
		
		mInjuredTime -= deltaTime;
		if (mInjuredTime <= 0)
		{
			FlipRightWay();
		}
	}

	if (notMoving)
	{
		movingLeft = true;
		notMoving = false;
	}
	Patrol(deltaTime, pointA, pointB);
	
	if (mJumping)
	{
		mPosition.y -= INITIAL_JUMP_FORCE_KOOPA * deltaTime;

		mJumpForce -= JUMP_FORCE_DECREMENT_KOOPA * deltaTime;

		if (mJumpForce <= 0)
		{
			mJumping = false;
		}
	}
}

void Koopa::Patrol(float deltaTime, float pointA, float pointB) {
	if (mPosition.x >= pointB)
	{
		movingRight = false;
		movingLeft = true;
	}
	else if (mPosition.x <= pointA)
	{
		movingLeft = false;
		movingRight = true;
	}
}

void Koopa::Render() {
	int left;
	if (mInjured)
	{
		left =(int) singleSpriteWidth;
	}
	else
	{
		left = 0.0f;
	}
	SDL_Rect portionOfSpriteSheet{ left, 0, singleSpriteWidth, singleSpriteHeight };
	SDL_Rect destRect = { (int)mPosition.x, (int)mPosition.y, singleSpriteWidth, singleSpriteHeight };
	if (mFacingDirection == FACEING_RIGHT) {
		mTexture->Render(portionOfSpriteSheet, destRect, SDL_FLIP_NONE, 0);
	}
	else {
		mTexture->Render(portionOfSpriteSheet, destRect, SDL_FLIP_HORIZONTAL, 0);
	}
}

void Koopa::TakeDamage() {
	mInjured = true;
	mInjuredTime = INJURED_TIME;
	Jump();
}

void Koopa::Jump() {
	if (!mJumping)
	{
		mJumpForce = INITIAL_JUMP_FORCE_KOOPA;
		mJumping = true;
		mCanJump = false;
	}
}

void Koopa::FlipRightWay() {
	mInjured = false;
	notMoving = true;
	Jump();
}

void Koopa::MoveLeft(float deltaTime) {
	mFacingDirection = FACEING_LEFT;
	mPosition.x -= KOOPA_MOVEMENT_SPEED * deltaTime;
}

void Koopa::MoveRight(float deltaTime) {
	mFacingDirection = FACEING_RIGHT;
	mPosition.x += KOOPA_MOVEMENT_SPEED * deltaTime;
}

void Koopa::SetAlive(bool alive) {
	_alive = alive;
}