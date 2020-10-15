#pragma once
#include "Texture2D.h"
#include <SDL_image.h>
#include <iostream>
#include <SDL_ttf.h>

using namespace::std;

Texture2D::Texture2D(SDL_Renderer* renderer){
	mRenderer = renderer;
	mTexture = NULL;

	mHeight = NULL;
	mWidth = NULL;
}
Texture2D::~Texture2D() {
	Free();
	mRenderer = NULL;
}
bool Texture2D::LoadFromFile(std::string path) {
	Free();
	SDL_Surface* pSurface = IMG_Load(path.c_str());
	mWidth = pSurface->w;
	mHeight = pSurface->h;
	if (pSurface != NULL)
	{
		SDL_SetColorKey(pSurface, SDL_TRUE, SDL_MapRGB(pSurface->format, 0, 0xFF, 0xFF));
		mTexture = SDL_CreateTextureFromSurface(mRenderer, pSurface);
		if (mTexture == NULL)
		{
			cout << "Unable to create textur from the surface. ERROR: " << SDL_GetError() << endl;
		}
		SDL_FreeSurface(pSurface);
	}
	else
	{
		cout << "Unable to create textur from the surface. ERROR: " << SDL_GetError() << endl;
	}
	return mTexture != NULL;
}
bool Texture2D::LoadText(std::string path, int size, std::string text, SDL_Color& textColor)
{
	Free();
	TTF_Font* font = TTF_OpenFont(path.c_str(), size);
	SDL_Surface* message = TTF_RenderText_Solid(font, text.c_str(), textColor);
	mWidth = message->w;
	mHeight = message->h;
	if (message != NULL)
	{
		SDL_SetColorKey(message, SDL_TRUE, SDL_MapRGB(message->format, 0, 0xFF, 0xFF));
		mTexture = SDL_CreateTextureFromSurface(mRenderer, message);
		if (mTexture == NULL)
		{
			cout << "Unable to create textur from the surface. ERROR: " << SDL_GetError() << endl;
		}
		SDL_FreeSurface(message);
		TTF_CloseFont(font);
	}
	else
	{
		cout << "Unable to create textur from the surface. ERROR: " << SDL_GetError() << endl;
	}
	return mTexture != NULL;
}
void Texture2D::Free() {
	if (mTexture != NULL)
	{
		SDL_DestroyTexture(mTexture);
		mHeight = 0;
		mWidth = 0;
		mTexture = NULL;
	}
}
void Texture2D::Render(Vector2D newPos, SDL_RendererFlip flip, double angle) {

	SDL_Rect renderLocation = { newPos.x, newPos.y, mWidth, mHeight };
	SDL_RenderCopyEx(mRenderer, mTexture, NULL, &renderLocation, 0, NULL, flip);
}

void Texture2D::Render(SDL_Rect srcRect, SDL_Rect destRect, SDL_RendererFlip flip, double angle = 0.0f) {
	SDL_RenderCopyEx(mRenderer, mTexture, &srcRect, &destRect, angle, NULL, flip);
}