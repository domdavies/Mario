#ifndef _TEXTURE2D_H
#define _TEXTURE2D_H

#include <SDL.h>
#include <string>
#include "Commons.h"

class Texture2D {
public:
	Texture2D(SDL_Renderer* renderer);
	~Texture2D();
	bool LoadFromFile(std::string path);
	bool LoadText(std::string path, int size, std::string text, SDL_Color& textColor);
	void Free();
	void Render(Vector2D newPos, SDL_RendererFlip flip, double angle = 0.0f);
	void Render(SDL_Rect srcRect, SDL_Rect destRect, SDL_RendererFlip flip, double angle);

	int GetWidth() { return mWidth; }
	int GetHeight() { return mHeight; }
	int mHeight;
	int mWidth;

private:
	SDL_Renderer* mRenderer;
	SDL_Texture* mTexture;
};
#endif // !_TEXTURE2D_H
