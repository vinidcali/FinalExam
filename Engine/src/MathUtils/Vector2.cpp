#include "../MathUtils.h"
#include <math.h>

Vector2::Vector2() : x(0.0f), y(0.0f) 
{ }

Vector2::Vector2(float x, float y) : 
x(x), 
y(y) 
{ }

Vector2 Vector2::Zero()
{ 
  return Vector2();
}

Vector2 Vector2::One()
{
  return Vector2(1.0f, 1.0f);
}

float Vector2::Dot(Vector2 first, Vector2 second)
{
  float dot = (first.x * second.x) + (first.y * second.y);
  float magnitudes = Vector2::Magnitude(first) * Vector2::Magnitude(second);
  float angle = 0.0f;
  if (magnitudes > 0.0f)
  {
    angle = acosf(dot / magnitudes);
  }

  return angle;
}

Vector2 Vector2::Difference(Vector2 first, Vector2 second)
{
  return Vector2(
    first.x - second.x,
    first.y - second.y);
}

Vector2 Vector2::Normalize(Vector2 toNormalize)
{
  Vector2 normalized;
  float magnitude = fabsf(Vector2::Magnitude(toNormalize));

  if (magnitude != 0.0f)
  {
    normalized.x = toNormalize.x / magnitude;
    normalized.y = toNormalize.y / magnitude;
  }

  return normalized;
}

float Vector2::Magnitude(Vector2 toMagnitude)
{
  return sqrtf(powf(toMagnitude.x, 2.0f) + powf(toMagnitude.y, 2.0f));
}