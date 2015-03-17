#pragma once

#include "Camera.h"

class PerspectiveCamera : public Camera
{
public:
  PerspectiveCamera(float fov, float aspectRatio, float nearPlane, float farPlane, Vector4 position, Vector4 look, Vector4 up);

protected:
  float _fov;
  float _aspectRatio;
};