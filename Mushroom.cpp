#include "Mushroom.h"

Mushroom::Mushroom(SDL_Renderer* renderer, string imagePath, Vector2D startpos, LevelMap* map) : Character(renderer, imagePath, startpos, map)
{
	singleSpriteWidth = 28;
	singleSpriteHeight = 28;
}

Mushroom::~Mushroom()
{

}

void Mushroom::Update(float deltaTime, SDL_Event e)
{
	Character::Update(deltaTime, e);
	movingRight = true;
}

void Mushroom::Render()
{
	Character::Render();
}

void Mushroom::MoveLeft(float deltaTime) {
	mFacingDirection = FACEING_LEFT;
	mPosition.x -= KOOPA_MOVEMENT_SPEED * deltaTime;
}

void Mushroom::MoveRight(float deltaTime) {
	mFacingDirection = FACEING_RIGHT;
	mPosition.x += KOOPA_MOVEMENT_SPEED * deltaTime;
}