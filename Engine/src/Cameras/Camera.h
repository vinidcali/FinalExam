#pragma once

#include "../GameObject.h"

class Camera
{
public:
  Camera();
  Camera(float nearPlane, float farPlane, Vector4 position, Vector4 look, Vector4 up);

  Vector4 GetPosition();
  Vector4 GetLookAtVector();
  Vector4 GetUpVector();

  void SetPosition(Vector4 position);
  void SetLookAtVector(Vector4 lookAtVector);
  void SetUpVector(Vector4 up);

  virtual Matrix4x4 GetViewMatrix();
  virtual Matrix4x4 GetProjectionMatrix();

protected:
  float _nearPlane;
  float _farPlane;

  Vector4 _position;
  Vector4 _look;
  Vector4 _up;
};