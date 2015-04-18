#include "Player.h"
#include "Cube.h"
#include "BodyNode.h"

Player::~Player()
{
  // Clean up the snake's allocated memory.
  while (_body.size() > 0)
  {
    delete _body[_body.size() - 1];
    _body.pop_back();
  }
}

void Player::Initialize(Graphics *graphics)
{
  _moveSpeed = 3.0f;

  BodyNode *head = new BodyNode();
  head->Initialize(graphics);
  head->SetDirection(BodyNode::LEFT);
  head->moveSpeed = _moveSpeed;
  head->active = true;

  // Create first node for the player.
  _body.push_back(head);
  _difference = 0.0f;
}

void Player::AddBodyPiece(Graphics *graphics)
{
  BodyNode *bodyPiece = new BodyNode();
  bodyPiece->Initialize(graphics);
  bodyPiece->moveSpeed = _moveSpeed;

  // Copy over the information from the previous node.
  bodyPiece->GetTransform().position = _body[_body.size() - 1]->GetTransform().position;
  bodyPiece->directionChange = _body[_body.size() - 1]->directionChange;

  // Add the node to our list.
  _body.push_back(bodyPiece);

  _piecesToAdd++;
}

void Player::SetHeadDirection(BodyNode::Direction direction)
{
  BodyNode::Direction oldHeadDirection = GetHeadDirection();

  if (oldHeadDirection != direction)
  {
    // Check to see if we're already waiting to go in that direction. If so, disregard it.
    bool alreadyContains = false;
    if (_nextDirection.size() > 0 && _nextDirection[_nextDirection.size() - 1] == direction)
    {
      alreadyContains = true;
    }

    if (alreadyContains == false)
    {
      _nextDirection.push_back(direction);
    }
  }
}

const BodyNode::Direction& Player::GetHeadDirection()
{
  return _body[0]->GetDirection();
}

void Player::Update(float dt)
{
  bool canTurn = false;

  _difference += dt;
  if (_difference > 0.5f)
  {
    _difference -= 0.5f;
    canTurn = true;
  }

  // If we've moved enough to warrant a turn, let's see what direction we'll be going in.
  if (canTurn && _nextDirection.size() > 0)
  {
    // Get the new direction.
    BodyNode::Direction newDirection = _nextDirection[0];
    BodyNode::Direction oldHeadDirection = GetHeadDirection();
    _nextDirection.erase(_nextDirection.begin());

    // Set the head's direction.
    _body[0]->SetDirection(newDirection);

    // If we've got nodes, and we're moving in a new direction, we have to update the body!
    if (_body.size() > 1 && oldHeadDirection != newDirection)
    {
      BodyNode::DirectionPair pair;
      pair.direction = newDirection;
      pair.pivot = _body[0]->GetTransform().position;

      // Update the body.
      for (int bodyIndex = 1; bodyIndex < _body.size(); bodyIndex++)
      {
        _body[bodyIndex]->directionChange.push_back(pair);
      }
    }
  }

  // Move player based on current direction.
  for (int bodyIndex = _body.size() - 1; bodyIndex >= 0; bodyIndex--)
  {
    BodyNode *currentNode = _body[bodyIndex];
    bool canMove = true;

    if (_body.size() > 1 && bodyIndex > 0)
    {
      BodyNode *nextNode = _body[bodyIndex - 1];
      Vector3 currentPosition = currentNode->GetTransform().position;

      /* If we're at the last piece of the body and it's just been added, we don't want it to move until the previous piece is
       * far enough away so we don't risk colliding with it. */
      if (bodyIndex == _body.size() - 1 && currentNode->active == false)
      {
        Vector3 nextBodyPiecePosition = nextNode->GetTransform().position;

        float distance = Vector3::Magnitude(Vector3::Difference(currentPosition, nextBodyPiecePosition));

        // Make sure it's far enough away before we say it's okay.
        if (distance >= 1.0f)
        {
          currentNode->active = true;
          currentNode->SetDirection(nextNode->GetDirection());

          switch (nextNode->GetDirection())
          {
          case BodyNode::UP:
            currentNode->GetTransform().position.x = nextNode->GetTransform().position.x;
            currentNode->GetTransform().position.y = nextNode->GetTransform().position.y - 1.0f;
            break;
          case BodyNode::DOWN:
            currentNode->GetTransform().position.x = nextNode->GetTransform().position.x;
            currentNode->GetTransform().position.y = nextNode->GetTransform().position.y + 1.0f;
            break;
          case BodyNode::LEFT:
            currentNode->GetTransform().position.x = nextNode->GetTransform().position.x + 1.0f;
            currentNode->GetTransform().position.y = nextNode->GetTransform().position.y;
            break;
          case BodyNode::RIGHT:
            currentNode->GetTransform().position.x = nextNode->GetTransform().position.x - 1.0f;
            currentNode->GetTransform().position.y = nextNode->GetTransform().position.y;
            break;
          }
        }
      }
      else
      {
        float nextNodeDifference = Vector3::Magnitude(Vector3::Difference(nextNode->GetTransform().position, currentNode->GetTransform().position));

        // Move other pieces.
        if (currentNode->directionChange.size() > 0)
        {
          BodyNode::DirectionPair pair = currentNode->directionChange[0];
          Vector3 directionChange = pair.pivot;

          float difference = Vector3::Magnitude(Vector3::Difference(directionChange, currentNode->GetTransform().position));

          // Ensure that we're close enough to the pivot.
          if (difference <= 0.05f)
          {
            currentNode->SetDirection(BodyNode::NONE);
            currentNode->GetTransform().position = directionChange;

            // Ensure that we're far enough away from the previous node before moving.
            
            if (nextNodeDifference >= 1.0f)
            {
              currentNode->SetDirection(pair.direction);
              currentNode->directionChange.erase(currentNode->directionChange.begin());
            }
          }
        }

        if (nextNodeDifference > 1.25f)
        {
          switch (nextNode->GetDirection())
          {
          case BodyNode::UP:
            currentNode->GetTransform().position.x = nextNode->GetTransform().position.x;
            currentNode->GetTransform().position.y = nextNode->GetTransform().position.y - 1.0f;
            break;
          case BodyNode::DOWN:
            currentNode->GetTransform().position.x = nextNode->GetTransform().position.x;
            currentNode->GetTransform().position.y = nextNode->GetTransform().position.y + 1.0f;
            break;
          case BodyNode::LEFT:
            currentNode->GetTransform().position.x = nextNode->GetTransform().position.x + 1.0f;
            currentNode->GetTransform().position.y = nextNode->GetTransform().position.y;
            break;
          case BodyNode::RIGHT:
            currentNode->GetTransform().position.x = nextNode->GetTransform().position.x - 1.0f;
            currentNode->GetTransform().position.y = nextNode->GetTransform().position.y;
            break;
          }

          currentNode->directionChange.clear();
          currentNode->directionChange = nextNode->directionChange;
          currentNode->SetDirection(nextNode->GetDirection());
        }
      }
    }

    currentNode->Update(dt);
  }
}

void Player::Draw(Graphics *graphics, Matrix4x4 relativeTo, float dt)
{
  for (int bodyIndex = 0; bodyIndex < _body.size(); bodyIndex++)
  {
    _body[bodyIndex]->Draw(graphics, relativeTo, dt);
  }
}

void Player::SetHeadPosition(Vector3 position)
{
  Vector3 difference = Vector3::Difference(position, _body[0]->GetTransform().position);
  for (int bodyIndex = 0; bodyIndex < _body.size(); bodyIndex++)
  {
    _body[bodyIndex]->GetTransform().position.x += difference.x;
    _body[bodyIndex]->GetTransform().position.y += difference.y;
    _body[bodyIndex]->GetTransform().position.z += difference.z;
  }
}

Vector3 Player::GetHeadPosition()
{
  return _body[0]->GetTransform().position;
}