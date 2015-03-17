#pragma once

// A structure to hold two floats. Similar to SDL_Point (though it contains ints).
struct Vector2
{
  float x;
  float y;

  Vector2();
  Vector2(float x, float y);

  static Vector2 Zero();
  static Vector2 One();
  static float Dot(Vector2 first, Vector2 second);
  static Vector2 Difference(Vector2 first, Vector2 second);
  static Vector2 Normalize(Vector2 toNormalize);
  static float Magnitude(Vector2 toMagnitude);
};

struct Vector3 : public Vector2
{
  float z;

  Vector3();
  Vector3(float x, float y, float z);

  static Vector3 Zero();
  static Vector3 One();
  static float Dot(Vector3 first, Vector3 second);
  static Vector3 Cross(Vector3 first, Vector3 second);
  static Vector3 Difference(Vector3 first, Vector3 second);
  static Vector3 Normalize(Vector3 toNormalize);
  static float Magnitude(Vector3 toMagnitude);
};

struct Vector4 : public Vector3
{
  float w;

  Vector4();
  Vector4(float x, float y, float z, float w);

  static Vector4 Zero();
  static Vector4 One();
  static float Dot(Vector4 first, Vector4 second);
  static Vector4 Cross(Vector4 first, Vector4 second);
  static Vector4 Difference(Vector4 first, Vector4 second);
  static Vector4 Normalize(Vector4 toNormalize);
  static float Magnitude(Vector4 toMagnitude);
};

struct Transform
{
  Vector3 position;
  Vector3 rotation;
  Vector3 scale;

  Transform();
  Transform(Vector3 position, Vector3 rotation, Vector3 scale);
};

struct Matrix4x4
{
  float m00; float m01; float m02; float m03;
  float m10; float m11; float m12; float m13;
  float m20; float m21; float m22; float m23;
  float m30; float m31; float m32; float m33;

  Matrix4x4();
  Matrix4x4(Vector4 r0, Vector4 r1, Vector4 r2, Vector4 r3);

  static Matrix4x4 Identity();
};

class MathUtils
{
public:
  static float ToRadians(float degrees);
  static float ToDegrees(float radians);
};