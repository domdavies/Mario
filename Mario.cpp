#include "Mario.h"

Mario::Mario(SDL_Renderer* renderer, string imagePath, Vector2D startpos, LevelMap* map) : Character(renderer, imagePath, startpos, map){
	SetState(PLAYER_SMALL);
	jump = true;
	deathSound = NULL;
	jumpSound = NULL;
}

Mario::~Mario() {
	delete deathSound;
	deathSound = NULL;

	delete jumpSound;
	jumpSound = NULL;
}

void Mario::Render() {
	Character::Render();
}

void Mario::Grow()
{
	this->SetState(PLAYER_LARGE);
	this->mPosition.y -= 16;
	size = 1.5;
}

void Mario::Shrink()
{
	this->SetState(PLAYER_SMALL);
	size = 1;
	this->mPosition.y += 16;
	this->mPosition.x += 10;
}

void Mario::PlayDeathAnim(float deltaTime)
{
	currentFrame = 4;
	movingLeft = false;
	movingRight = false;
	if (jump)
	{
		Character::Jump();
		soundManager->LoadMusic(1, deathSound, "Music/Death.wav", 0);
		jump = false;
	}
 }

void Mario::Update(float deltaTime, SDL_Event e) {
	Character::Update(deltaTime, e);
	//checks to see if the framecount is less than 0
	if (frameCount <= 0.0f)
	{
		//if the player is alive, allow them to walk left or right
		if (GetState() != PLAYER_DEATH)
		{
			//if this flag returns true, then checks to see if the characte is moving in either direction
			if (movingLeft || movingRight)
			{
				//loops through this code to give the impression of animation
				frameCount = ANIMATION_DELAY;
				currentFrame++;
				if (currentFrame > 3)
				{
					currentFrame = 0;
				}
			}
			else
				currentFrame = 0;
		}
	}
	switch (e.type)
	{
	case SDL_KEYDOWN:
		switch (e.key.keysym.sym)
		{
		case SDLK_LEFT:
			movingLeft = true;
			movingRight = false;
			//cout << movingLeft << endl;
			break;
		case SDLK_RIGHT:
			movingRight = true;
			movingLeft = false;
			//cout << movingRight << endl;
			break;
		case SDLK_UP:
			if (mCanJump)
			{
				Character::Jump();
				soundManager->LoadMusic(1, jumpSound, "Music/Jump.wav", 0);
			}
			break;
		}
		break;
	case SDL_KEYUP:
		switch (e.key.keysym.sym)
		{
		case SDLK_LEFT:
			movingLeft = false;
			break;
		case SDLK_RIGHT:
			movingRight = false;
			break;
		case SDLK_SPACE:
			break;
		}
		break;
	}
}