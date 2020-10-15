#include "Character.h"
#include "Texture2D.h"
#include "Constants.h"

Character::Character(SDL_Renderer* renderer, string imagePath, Vector2D startpos, LevelMap* map) {
	mRenderer = renderer;
	mTexture = new Texture2D(renderer);
	//sets the map for the level, so the character can collide with objects/blocks
	mCurrentLevelMap = map;

	if (!mTexture->LoadFromFile(imagePath))
	{
		cout << " failed to load image" << endl;
	}

	mPosition = startpos;

	mCanJump = true;
	mJumpForce = INITIAL_JUMP_FORCE;
	mJumping = false;

	mFacingDirection = FACEING_RIGHT;
	movingLeft = false;
	movingRight = false;
	isAir = false;
	collisionRadius = 15.0f;
	frameCount = 0;
	currentFrame = 0;
	size = 1;
	singleSpriteWidth = mTexture->GetWidth() / 5;
	singleSpriteHeight = mTexture->GetHeight();
}

Character::~Character() {
	mRenderer = NULL;
}

void Character::Render(){
	SDL_Rect portionofSpriteSheet = { singleSpriteWidth * currentFrame, 0, singleSpriteWidth, singleSpriteHeight };
	SDL_Rect dest = { (int)mPosition.x, (int)mPosition.y, (float)singleSpriteWidth * size, (float)singleSpriteHeight * size };

	if (mFacingDirection == FACEING_RIGHT) {
		mTexture->Render(portionofSpriteSheet, dest, SDL_FLIP_HORIZONTAL, 0);
	}
	else {
		mTexture->Render(portionofSpriteSheet, dest, SDL_FLIP_NONE, 0);
	}
}

void Character::Update(float deltaTime, SDL_Event e) {
	frameCount -= deltaTime;

	//cout << mFacingDirection << endl;
	//sets centralXPos to be the centre of the characters x position
	int centralXPos = (int)(mPosition.x + ((singleSpriteWidth * size) * 0.5f)) / TILE_WIDTH;
	//sets foootPos to be the bottom of the characters y coord
	int footPos = (int)(mPosition.y + (size * singleSpriteHeight)) / TILE_HEIGHT;
	int headPos = (int)(mPosition.y) / TILE_HEIGHT;
	int midY = (int)(mPosition.y + (size * singleSpriteHeight) / 2) / TILE_HEIGHT;
	int rightSide = (int)(mPosition.x + (size * singleSpriteWidth)) / TILE_WIDTH;
	int leftSide = (int)(mPosition.x) / TILE_WIDTH;

	//deaal with gravity
	//check if we are stood on a block tile or not
	if (currentFrame == 4)
	{
		AddGravity(deltaTime);
	}
	else
	{
		if (mCurrentLevelMap->GetTileAt(footPos, centralXPos) == 0)
		{
			AddGravity(deltaTime);
			isAir = true;
		}
		else
		{
			//we are stood on solid ground
			mCanJump = true;
			isAir = false;
		}

		if (mCurrentLevelMap->GetTileAt(headPos, centralXPos) == 1)
		{
			CancelJump();
		}
		if (mCurrentLevelMap->GetTileAt(midY, rightSide) == 1)
		{
			mPosition.x -= mCurrentLevelMap->GetTileAt(midY, rightSide);
		}
		else if (mCurrentLevelMap->GetTileAt(midY, leftSide) == 1)
    	{
			mPosition.x += mCurrentLevelMap->GetTileAt(midY, leftSide);
		}
	}

	//deal with the jumping
	if (mJumping)
	{
		//adjust the position of the character
		mPosition.y -= mJumpForce * deltaTime;

		//reduce the jumpforce
		mJumpForce -= JUMP_FORCE_DECREMENT * deltaTime;

		//has the jumpforce reached 0
		if (mJumpForce <= 0)
		{
			mJumping = false;
		}
	}

	if (movingLeft)
	{
		MoveLeft(deltaTime);
	}
	if (movingRight)
	{
		MoveRight(deltaTime);
	}
}

void Character::AddGravity(float deltaTime) {
	mPosition.y += GRAVITY * deltaTime;
	mCanJump = false;
}

void Character::Jump() {
	if (!mJumping)
	{
		mJumpForce = INITIAL_JUMP_FORCE;
		mJumping = true;
		mCanJump = false;
	}
}

void Character::CancelJump() {
	mJumping = false;
}

void Character::SetPosition(Vector2D newPosition) {
	mPosition = newPosition;
}

Vector2D Character::GetPosition() {
	return mPosition;
}

void Character::MoveLeft(float deltaTime) {
	mFacingDirection = FACEING_LEFT;
	mPosition.x -= MOVEMENT_SPEED * deltaTime;
}

void Character::MoveRight(float deltaTime) {
	mFacingDirection = FACEING_RIGHT;
	mPosition.x += MOVEMENT_SPEED * deltaTime;
}

float Character::GetCollisionRadius() {
	return collisionRadius;
}

Rect2D Character::GetCollisionBox() { return Rect2D(mPosition.x, mPosition.y, singleSpriteWidth * size, singleSpriteHeight * size); }