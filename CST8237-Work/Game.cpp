#include "Game.h"

// Initializing our static member pointer.
GameEngine* GameEngine::_instance = nullptr;

GameEngine* GameEngine::CreateInstance()
{
  if (_instance == nullptr)
  {
    _instance = new GameEngine();
  }
  return _instance;
}

Game::Game() : GameEngine()
{

}