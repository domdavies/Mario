#ifndef _BREAKABLE_BLOCK_
#define _BREAKABLE_BLOCK_

#include "Commons.h"
#include "Texture2D.h"
#include "LevelMap.h"
#include "SoundManager.h"
class BreakableBlock
{
public:
	BreakableBlock(SDL_Renderer* renderer, LevelMap* map, Vector2D pos);
	~BreakableBlock();

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

	bool isAvaliable;
};
#endif // !_SUPRISE_BLOCK_