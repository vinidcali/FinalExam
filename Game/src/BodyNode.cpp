#include "BodyNode.h"
#include "Cube.h"
#include <Graphics/Graphics.h>

BodyNode::~BodyNode()
{
  delete nodeCube;
  nodeCube = nullptr;
}

void BodyNode::Initialize(Graphics *graphics)
{
  // Create first node for the BodyNode.
  nodeCube = new Cube();
  nodeCube->Initialize(graphics);

  moveSpeed = 1.0f;
  active = false;
}

void BodyNode::SetDirection(BodyNode::Direction direction)
{
  _direction = direction;
}

const BodyNode::Direction& BodyNode::GetDirection()
{
  return _direction;
}

void BodyNode::Update(float dt)
{
  // Move BodyNode based on current direction.
  switch (_direction)
  {
  case UP:
    _transform.position.y += moveSpeed * dt;
    break;
  case DOWN:
    _transform.position.y -= moveSpeed * dt;
    break;
  case LEFT:
    _transform.position.x -= moveSpeed * dt;
    break;
  case RIGHT:
    _transform.position.x += moveSpeed * dt;
    break;
  }

  // Copy over the current transform information into our cube.
  nodeCube->GetTransform().position = _transform.position;
  nodeCube->GetTransform().rotation = _transform.rotation;
  nodeCube->GetTransform().scale = _transform.scale;
}

void BodyNode::Draw(Graphics *graphics, Matrix4x4 relativeTo, float dt)
{
  nodeCube->Draw(graphics, relativeTo, dt);
}