#pragma once

#include <GameEngine.h>

union SDL_Event;
class Graphics;
class Camera;
class Player;
class Fruit;

class Game : public GameEngine
{
  friend class GameEngine;

public:
  ~Game();

protected:
  Game();

  void InitializeImpl();
  void UpdateImpl(float dt);
  void DrawImpl(Graphics *graphics, float dt);

  void Reset();
  void CalculateCameraViewpoint(Camera *camera);

  Player *_player;
  Fruit *_fruit;
  int currentScore;

  Camera *_gameCamera;
};