#ifndef _POW_BLOCK_
#define _POW_BLOCK_

#include "Commons.h"
#include "Texture2D.h"
#include "LevelMap.h"
#include "SoundManager.h"
class PowBlock
{
public:
	PowBlock(SDL_Renderer* renderer, LevelMap* map, Vector2D pos);
	~PowBlock();

	void Render();
	Rect2D GetCollisonBox();
	void TakeHit();
	bool IsAvaliable() { return hitsLeft > 0; };
private:
	SDL_Renderer* mRenderer;
	Vector2D mPos;
	Texture2D* mTexture;
	LevelMap* mLevelMap;
	SoundManager* soundManager;
	Mix_Chunk* hit;

	float singleSpriteWidth, singleSpriteHeight;
	int hitsLeft;
};
#endif // !_POW_BLOCK_