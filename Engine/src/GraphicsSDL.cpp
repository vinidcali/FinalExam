#include "GraphicsSDL.h"
#include <SDL.h>

void GraphicsSDL::Initialize(SDL_Window *window)
{
  _rendererObject = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
}

void GraphicsSDL::Shutdown()
{
  SDL_DestroyRenderer(GetRenderer());
  _rendererObject = nullptr;
}

SDL_Renderer* GraphicsSDL::GetRenderer()
{
  return (SDL_Renderer *)_rendererObject;
}

void GraphicsSDL::SetClearColour(float r, float g, float b, float a)
{
  // Set the draw colour for screen clearing.
  SDL_SetRenderDrawColor(GetRenderer(), (float)(255.0f * r), (float)(255.0f * g), (float)(255.0f * b), (float)(255.0f * a));
}

void GraphicsSDL::ClearScreen()
{
  // Clear the renderer with the current draw colour.
  SDL_RenderClear(GetRenderer());
}

void GraphicsSDL::Present()
{
  SDL_RenderPresent(GetRenderer());
}