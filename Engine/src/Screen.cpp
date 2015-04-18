#include "Screen.h"
#include <SDL.h>

void Screen::Initialize(SDL_Renderer *renderer)
{
  SDL_Rect viewportRect;
  SDL_RenderGetViewport(renderer, &viewportRect);

  _screenRenderTarget = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, viewportRect.w, viewportRect.h);
  InitializeImpl(renderer);
}

Screen::Screen()
{
  SDL_DestroyTexture(_screenRenderTarget);
}