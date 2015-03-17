#pragma once

#include "Camera.h"

class OrthographicCamera : public Camera
{
public:
  OrthographicCamera(float leftPlane, float rightPlane, float topPlane, float bottomPlane, float nearPlane, float farPlane, Vector4 position, Vector4 look, Vector4 up);

protected:
  float _leftPlane;
  float _rightPlane;
  float _topPlane;
  float _bottomPlane;
};