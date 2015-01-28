#include "Game.h"
#include <SDL.h>
#include <math.h>
#include "InputManager.h"

// Initializing our static member pointer.
GameEngine* GameEngine::_instance = nullptr;

GameEngine* GameEngine::CreateInstance()
{
  if (_instance == nullptr)
  {
    _instance = new Game();
  }
  return _instance;
}

Game::Game() : GameEngine()
{

}

void Game::InitializeImpl()
{
  // Using the default member-wise initializer for our new struct.
  pos = { 100.0f, 100.0f };
  endPointOffset = { 10.0f, 0.0f };
  speed = 100.0f;
  rotationSpeed = 360.0f;
}

void Game::UpdateImpl(float dt)
{
  InputManager *im = InputManager::GetInstance();
  im->Update(dt);

  // Check for user input.
  if (im->IsKeyDown(SDLK_UP) == true)
  {
    pos.y -= (speed * dt);
  }
  else if (im->IsKeyDown(SDLK_DOWN) == true)
  {
    pos.y += (speed * dt);
  }
}

void Game::DrawImpl(SDL_Renderer *renderer, float dt)
{
  // Set the draw colour for our point.
  SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);

  // Draw the point.
  //SDL_RenderDrawPoint(renderer, posX, posY);

  static float rotationDegrees = 10.0f;
  rotationDegrees += (rotationSpeed * dt);
  rotationDegrees += (rotationDegrees >= 360.0f ? -360.0f : 0);

  float rotationRadians = MathUtils::ToRadians(rotationDegrees);

  Vector2 rotatedOffset =
  {
    endPointOffset.x * cosf(rotationRadians) + endPointOffset.y * sinf(rotationRadians),
    endPointOffset.x * sinf(rotationRadians) - endPointOffset.y * cosf(rotationRadians)
  };

  Vector2 transformedEndPoint = { pos.x + rotatedOffset.x, pos.y + rotatedOffset.y };

  _player.Draw(renderer, dt);

  SDL_RenderDrawLine(renderer, pos.x, pos.y, transformedEndPoint.x, transformedEndPoint.y);
}