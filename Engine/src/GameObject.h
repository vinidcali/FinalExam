#pragma once 

#include "MathUtils.h"

struct SDL_Renderer;

class GameObject
{
public:
  virtual void Initialize(SDL_Renderer *renderer) = 0;
  
  virtual void Update(float dt) = 0;
  virtual void Draw(SDL_Renderer *renderer, float dt) = 0;

  Transform& GetTransform();

  ~GameObject();

protected:
  GameObject();

  Transform _transform;
};