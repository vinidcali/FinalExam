#include "GameObject.h"

GameObject::GameObject() { }

GameObject::~GameObject() { }

Transform& GameObject::GetTransform()
{
  return _transform;
}