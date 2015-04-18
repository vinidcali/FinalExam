#include "../MathUtils.h"
#include <math.h>

Vector4::Vector4() :
Vector3(),
w(0.0f)
{ }

Vector4::Vector4(float x, float y, float z, float w) :
Vector3(x, y, z),
w(w)
{ }

Vector4 Vector4::Zero()
{
  return Vector4(0.0f, 0.0f, 0.0f, 0.0f);
}

Vector4 Vector4::One()
{
  return Vector4(1.0f, 1.0f, 1.0f, 0.0f);
}

float Vector4::Dot(Vector4 first, Vector4 second)
{
  float dot = (first.x * second.x) + (first.y * second.y) + (first.z * second.z) + (first.w * second.w);
  float magnitudes = Vector4::Magnitude(first) * Vector4::Magnitude(second);
  float angle = 0.0f;
  if (magnitudes > 0.0f)
  {
    angle = acosf(dot / magnitudes);
  }

  return angle;
}

Vector4 Vector4::Difference(Vector4 first, Vector4 second)
{
  return Vector4(
    first.x - second.x,
    first.y - second.y,
    first.z - second.z,
    first.w - second.w);
}

Vector4 Vector4::Normalize(Vector4 toNormalize)
{
  Vector4 normalized;
  float magnitude = fabsf(Vector4::Magnitude(toNormalize));

  if (magnitude != 0.0f)
  {
    normalized.x = toNormalize.x / magnitude;
    normalized.y = toNormalize.y / magnitude;
    normalized.z = toNormalize.z / magnitude;
    normalized.w = toNormalize.w / magnitude;
  }

  return normalized;
}

float Vector4::Magnitude(Vector4 toMagnitude)
{
  return sqrtf(powf(toMagnitude.x, 2.0f) + powf(toMagnitude.y, 2.0f) + powf(toMagnitude.z, 2.0f) + powf(toMagnitude.w, 2.0f));
}