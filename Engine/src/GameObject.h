#pragma once 

#include "MathUtils.h"

class Graphics;

class GameObject
{
public:
  virtual void Initialize(Graphics *graphics) = 0;
  
  virtual void Update(float dt) = 0;
  virtual void Draw(Graphics *graphics, float dt) = 0;

  Transform& GetTransform();

  ~GameObject();

protected:
  GameObject();

  Transform _transform;
};