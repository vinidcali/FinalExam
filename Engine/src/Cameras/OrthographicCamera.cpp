#include "OrthographicCamera.h"
#include <SDL_opengl.h>
#include <gl/GLU.h>

OrthographicCamera::OrthographicCamera(float leftPlane, float rightPlane, float topPlane, float bottomPlane, float nearPlane, float farPlane, Vector4 position, Vector4 look, Vector4 up) :
Camera(nearPlane, farPlane, position, look, up),
_leftPlane(leftPlane),
_rightPlane(rightPlane),
_topPlane(topPlane),
_bottomPlane(bottomPlane)
{
}

void OrthographicCamera::Apply()
{
  glOrtho(_leftPlane, _rightPlane, _bottomPlane, _topPlane, _nearPlane, _farPlane);
}