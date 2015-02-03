#pragma once

#include <GameEngine.h>

union SDL_Event;

class Game: public GameEngine
{
  friend class GameEngine;

public:
  ~Game();

protected:
  Game();

  void InitializeImpl();
  void UpdateImpl(float dt);
  void DrawImpl(SDL_Renderer *renderer, float dt);

  void Reset();
  void CalculateDrawOrder(std::vector<GameObject *>& drawOrder);
};