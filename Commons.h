#ifndef _COMMONS_H
#define _COMMONS_H

struct Vector2D
{
	float x;
	float y;
	Vector2D()
	{
		x = 0.0f;
		y = 0.0f;
	}
	Vector2D(float x, float y)
	{
		this->x = x;
		this->y = y;
	}
};

struct Rect2D {
	float x, y , w, h;

	Rect2D(float x, float y, float w, float h) {
		this->x = x;
		this->y = y;
		this->w = w;
		this->h = h;
	}
};

//an enumeration to switch between screens
enum SCREENS {
	SCREEN_INTRO = 0,
	SCREEN_MENU,
	SCREEN_LVL1,
	SCREEN_LVL2,
	SCREEN_GAMEOVER,
	SCREEN_HIGHSCORES
};

enum PLAYERSTATE {
	PLAYER_DEATH = 0,
	PLAYER_LARGE,
	PLAYER_SMALL
};

enum FACING {
	FACEING_LEFT = 0,
	FACEING_RIGHT
};

enum PLAYERS {
	ONE_PLAYER = 0,
	TWO_PLAYER
};
#endif // !_COMMONS_H