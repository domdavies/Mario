#include "Luigi.h"
#include "Character.h"

Luigi::Luigi(SDL_Renderer* renderer, string imagePath, Vector2D startpos, LevelMap* map) : Character(renderer, imagePath, startpos, map) {
	singleSpriteWidth = 32;
	singleSpriteHeight = 32;
}

Luigi::~Luigi() {

}

void Luigi::Update(float deltaTime, SDL_Event e) {
	Character::Update(deltaTime, e);
	switch (e.type)
	{
	case SDL_KEYDOWN:
		switch (e.key.keysym.sym)
		{
		case SDLK_a:
			movingLeft = true;
			movingRight = false;
			//cout << movingLeft << endl;
			break;
		case SDLK_d:
			movingRight = true;
			movingLeft = false;
			//cout << movingRight << endl;
			break;
		case SDLK_w:
			if (mCanJump)
			{
				Character::Jump();
			}
			break;
		}
		break;
	case SDL_KEYUP:
		switch (e.key.keysym.sym)
		{
		case SDLK_a:
			movingLeft = false;
			break;
		case SDLK_d:
			movingRight = false;
			break;
		case SDLK_SPACE:
			break;
		}
		break;
	}
}

void Luigi::Render() {
	Character::Render();
}