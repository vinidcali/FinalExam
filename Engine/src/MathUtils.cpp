#include "MathUtils.h"

float MathUtils::ToDegrees(float radians)
{
  float radiansToDegrees = 180.0f / 3.1415926535f;
  return radians * radiansToDegrees;
}

float MathUtils::ToRadians(float degrees)
{
  float degreesToRadians = 3.1415926535f / 180.0f;
  return degrees * degreesToRadians;
}