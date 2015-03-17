#include "Camera.h"
#include <SDL_opengl.h>
#include <gl/GLU.h>

Camera::Camera() { }
Camera::Camera(float nearPlane, float farPlane,Vector4 position, Vector4 look, Vector4 up) : 
_nearPlane(nearPlane),
_farPlane(farPlane),
_position(position),
_look(look),
_up(up)
{ }

Vector4 Camera::GetPosition()
{
  return _position;
}

Vector4 Camera::GetLookAtVector()
{
  return _look;
}

Vector4 Camera::GetUpVector()
{
  return _up;
}

void Camera::SetPosition(Vector4 position)
{
  _position = position;
}

void Camera::SetLookAtVector(Vector4 lookAtVector)
{
  _look = lookAtVector;
}

void Camera::SetUpVector(Vector4 up)
{
  _up = up;
}

Matrix4x4 Camera::GetViewMatrix()
{
  return Matrix4x4::Identity();
}

Matrix4x4 Camera::GetProjectionMatrix()
{
  return Matrix4x4::Identity();
}