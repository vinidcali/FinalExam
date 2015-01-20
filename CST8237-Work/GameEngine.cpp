#include "GameEngine.h"
#include <SDL.h>
#include <math.h>
#include "MathUtils.h"

GameEngine::GameEngine()
{

}

GameEngine::~GameEngine()
{

}

void GameEngine::Initialize()
{
  SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER);

  window = SDL_CreateWindow("CST8237 Lab",
    SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
    640, 640,
    SDL_WINDOW_SHOWN);

  renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

  // Using the default member-wise initializer for our new struct.
  pos = { 100.0f, 100.0f };
  endPointOffset = { 10.0f, 0.0f };
  speed = 10.0f;
  rotationSpeed = 360.0f;

  /* Get the time at the beginning of our game loop so that we can track the
  * elapsed difference. */
  oldTime = SDL_GetTicks();
  currentTime = oldTime;
}

void GameEngine::Shutdown()
{
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
}

void GameEngine::Update()
{
  SDL_Event evt;
  SDL_PollEvent(&evt);

  // Calculating the time difference since our last loop.
  oldTime = currentTime;
  currentTime = SDL_GetTicks();
  deltaTime = (currentTime - oldTime) / 1000;

  // Check for user input.
  if (evt.type == SDL_KEYDOWN)
  {
    SDL_KeyboardEvent &keyboardEvt = evt.key;
    SDL_Keycode &keyCode = keyboardEvt.keysym.sym;
    switch (keyCode)
    {
    case SDLK_UP:
      pos.y -= (speed * deltaTime);
      break;
    case SDLK_DOWN:
      pos.y += (speed * deltaTime);
      break;
    default:
      break;
    }
  }
}

void GameEngine::Draw()
{
  // Set the draw colour for screen clearing.
  SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

  // Clear the renderer with the current draw colour.
  SDL_RenderClear(renderer);

  // Set the draw colour for our point.
  SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);

  // Draw the point.
  //SDL_RenderDrawPoint(renderer, posX, posY);

  static float rotationDegrees = 10.0f;
  rotationDegrees += (rotationSpeed * deltaTime);
  rotationDegrees += (rotationDegrees >= 360.0f ? -360.0f : 0);

  float rotationRadians = MathUtils::ToRadians(rotationDegrees);

  Vector2 rotatedOffset =
  {
    endPointOffset.x * cosf(rotationRadians) + endPointOffset.y * sinf(rotationRadians),
    endPointOffset.x * sinf(rotationRadians) - endPointOffset.y * cosf(rotationRadians)
  };

  Vector2 transformedEndPoint = { pos.x + rotatedOffset.x, pos.y + rotatedOffset.y };

  SDL_RenderDrawLine(renderer, pos.x, pos.y, transformedEndPoint.x, transformedEndPoint.y);

  // Present what is in our renderer to our window.
  SDL_RenderPresent(renderer);
}