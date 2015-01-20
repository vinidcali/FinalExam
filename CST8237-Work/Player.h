#pragma once

#include "GameObject.h"

class Player : public GameObject
{
public:
  Player();
  ~Player();

  void Initialize();

  void Update(float dt);
  void Draw(SDL_Renderer *renderer, float dt);
};