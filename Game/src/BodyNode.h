#pragma once

#include <GameObject.h>
#include <vector>

class Cube;
class Graphics;

class BodyNode : public GameObject
{
public:
  enum Direction
  {
    NONE = 0,
    UP,
    DOWN,
    LEFT,
    RIGHT
  };

  struct DirectionPair
  {
    Direction direction;
    Vector3 pivot;
  };
  
  ~BodyNode();

  void Initialize(Graphics *graphics);

  void Update(float dt);
  void Draw(Graphics *graphics, Matrix4x4 relativeTo, float dt);

  void SetDirection(BodyNode::Direction direction);
  const BodyNode::Direction& GetDirection();

  float moveSpeed;
  Cube *nodeCube;
  bool active;
  
  Direction _direction;
  std::vector<DirectionPair> directionChange;
};