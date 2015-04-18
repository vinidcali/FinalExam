#include "Fruit.h"
#include "Cube.h"

Fruit::~Fruit()
{
}

void Fruit::Initialize(Graphics *graphics)
{
  _fruitGeometry = new Cube();
  _fruitGeometry->Initialize(graphics);
  
  _transform.scale = Vector3(0.5f, 0.5f, 0.5f);

  // x is the minimum scale, y is the maximum.
  _pulsateScale.x = 0.35f;
  _pulsateScale.y = 0.65f;

  _isGrowing = true;
  _scaleRate = 1.0f;
}

void Fruit::Update(float dt)
{
  // Calculate how much we're going to scale by for our pulsate effect.
  float scaleFactor = _scaleRate * dt;
  _transform.scale.x += scaleFactor;
  _transform.scale.y += scaleFactor;
  _transform.scale.z += scaleFactor;

  // If we've exceeded any bounds, then we need to flip and go in the opposite direction.
  if ((_isGrowing == true && _transform.scale.x >= _pulsateScale.y) ||
    (_isGrowing == false && _transform.scale.x <= _pulsateScale.x))
  {
    _isGrowing = !_isGrowing;
    _scaleRate *= -1.0f;
  }

  // Update the fruit geo with our current transform values.
  _fruitGeometry->GetTransform().position = _transform.position;
  _fruitGeometry->GetTransform().rotation = _transform.rotation;
  _fruitGeometry->GetTransform().scale = _transform.scale;

  _fruitGeometry->Update(dt);
}

void Fruit::Draw(Graphics *graphics, Matrix4x4 relativeTo, float dt)
{
  _fruitGeometry->Draw(graphics, relativeTo, dt);
}