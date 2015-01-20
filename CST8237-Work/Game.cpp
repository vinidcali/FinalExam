#include "Game.h"

GameEngine* GameEngine::CreateInstance()
{
  return new GameEngine();
}