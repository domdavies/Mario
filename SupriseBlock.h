#ifndef _SUPRISE_BLOCK_
#define _SUPRISE_BLOCK_

#include "Commons.h"
#include "Texture2D.h"
#include "LevelMap.h"
#include "SoundManager.h"
class SupriseBlock
{
public:
	SupriseBlock(SDL_Renderer* renderer, LevelMap* map, Vector2D pos);
	~SupriseBlock();

	void Render();
	Rect2D GetCollisonBox();
	void TakeHit();
	bool IsAvaliable() { return isAvaliable; };
private:
	SDL_Renderer* mRenderer;
	Vector2D mPos;
	Texture2D* mTexture;
	LevelMap* mLevelMap;
	SoundManager* soundManager;
	Mix_Chunk* hit;

	int left;
	bool isAvaliable;
};
#endif // !_SUPRISE_BLOCK_

