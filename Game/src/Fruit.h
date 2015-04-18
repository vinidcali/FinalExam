#pragma once

#include <GameObject.h>
#include <vector>

class Cube;

class Fruit : public GameObject
{
public:
  ~Fruit();

  void Initialize(Graphics *graphics);

  void Update(float dt);
  void Draw(Graphics *graphics, Matrix4x4 relativeTo, float dt);

protected:
  Cube *_fruitGeometry;

  Vector2 _pulsateScale;
  float _scaleRate;
  bool _isGrowing;
};