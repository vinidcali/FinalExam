#include "Player.h"
#include <SDL.h>

Player::Player() : GameObject()
{
  _transform.position = { 400.0f, 400.0f, 0.0f };
}

Player::~Player()
{
}

void Player::Initialize()
{
}

void Player::Update(float dt)
{
}

void Player::Draw(SDL_Renderer *renderer, float dt)
{
}