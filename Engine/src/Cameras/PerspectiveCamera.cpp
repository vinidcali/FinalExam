#include "PerspectiveCamera.h"
#include <SDL_opengl.h>
#include <gl/GLU.h>

PerspectiveCamera::PerspectiveCamera(float fov, float aspectRatio, float nearPlane, float farPlane, Vector4 position, Vector4 look, Vector4 up):
Camera(nearPlane, farPlane, position, look, up),
_fov(fov),
_aspectRatio(aspectRatio)
{
  _fov = fov;
  _aspectRatio = aspectRatio;

  gluPerspective(_fov, _aspectRatio, _nearPlane, _farPlane);
}