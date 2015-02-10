#include "GameEngine.h"
#include <SDL.h>
#include <SDL_image.h>
#include "MathUtils.h"

GameEngine::GameEngine()
{

}

GameEngine::~GameEngine()
{

}

void GameEngine::Initialize()
{
  SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER | SDL_INIT_JOYSTICK | SDL_INIT_GAMECONTROLLER);

  _window = SDL_CreateWindow("Engine",
    SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
    640, 640,
    SDL_WINDOW_SHOWN);

  _renderer = SDL_CreateRenderer(_window, -1, SDL_RENDERER_ACCELERATED);

  IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG | IMG_INIT_TIF | IMG_INIT_WEBP);

  InitializeImpl();

  /* Get the time at the beginning of our game loop so that we can track the
  * elapsed difference. */
  _engineTimer.Start();
}

void GameEngine::Shutdown()
{
  /* Stop the engine timer as we're shutting down. */
  _engineTimer.Stop();

  SDL_DestroyRenderer(_renderer);
  SDL_DestroyWindow(_window);

  /* Quit and clean up all libraries. */
  IMG_Quit();
  SDL_Quit();
}

void GameEngine::Update()
{
  // Calculating the time difference since our last loop.
  _engineTimer.Update();

  UpdateImpl(_engineTimer.GetDeltaTime());
}

void GameEngine::Draw()
{
  // Set the draw colour for screen clearing.
  SDL_SetRenderDrawColor(_renderer, 255, 255, 255, 255);

  // Clear the renderer with the current draw colour.
  SDL_RenderClear(_renderer);

  DrawImpl(_renderer, _engineTimer.GetDeltaTime());

  // Present what is in our renderer to our window.
  SDL_RenderPresent(_renderer);
}