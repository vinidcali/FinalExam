#include "../MathUtils.h"
#include <math.h>

Vector3::Vector3() : 
Vector2(),
z(0.0f)
{ }

Vector3::Vector3(float x, float y, float z) : 
Vector2(x, y), 
z(z) 
{ }

Vector3 Vector3::Zero()
{
  return Vector3(0.0f, 0.0f, 0.0f);
}

Vector3 Vector3::One()
{
  return Vector3(1.0f, 1.0f, 1.0f);
}

float Vector3::Dot(Vector3 first, Vector3 second)
{
  float dot = (first.x * second.x) + (first.y * second.y) + (first.z * second.z);
  float magnitudes = Vector3::Magnitude(first) * Vector3::Magnitude(second);
  float angle = 0.0f;
  if (magnitudes > 0.0f)
  {
    angle = acosf(dot / magnitudes);
  }

  return angle;
}

Vector3 Vector3::Cross(Vector3 first, Vector3 second)
{
  return Vector3(
    first.y * second.z - first.z * second.y,
    first.z * second.x - first.x * second.z,
    first.x * second.y - first.y * second.x
    );
}

Vector3 Vector3::Difference(Vector3 first, Vector3 second)
{
  return Vector3(
    first.x - second.x,
    first.y - second.y,
    first.z - second.z);
}

Vector3 Vector3::Normalize(Vector3 toNormalize)
{
  Vector3 normalized;
  float magnitude = fabsf(Vector3::Magnitude(toNormalize));

  if (magnitude != 0.0f)
  {
    normalized.x = toNormalize.x / magnitude;
    normalized.y = toNormalize.y / magnitude;
    normalized.z = toNormalize.z / magnitude;
  }

  return normalized;
}

float Vector3::Magnitude(Vector3 toMagnitude)
{
  return sqrtf(powf(toMagnitude.x, 2.0f) + powf(toMagnitude.y, 2.0f) + powf(toMagnitude.z, 2.0f));
}