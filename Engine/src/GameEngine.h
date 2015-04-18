#pragma once // Preprocessor directive to ensure that this header will only be included once. -- Generally used on Windows

/**
 * GameEngine.h
 * Purpose: A basic description of the game engine.
 *
 * By: Justin Wilkinson
 */

#include "MathUtils.h"
#include "Timer.h"
#include <vector>

// Forward declaring our renderer and window.
// Because we're using them as pointers, we don't need to know their size
// at compile time to define this class.
struct SDL_Renderer;
struct SDL_Window;
class GameObject;
class Graphics;

class GameEngine
{
public:
  /**
   * Creates a GameEngine instance
   * @return The new GameEngine instance, NULL if no instance could be created.
   */
  static GameEngine* CreateInstance();

  void Initialize();
  void Shutdown();

  void Update();
  void Draw();

  ~GameEngine();

protected:
  GameEngine();

  virtual void InitializeImpl() = 0;
  virtual void UpdateImpl(float dt) = 0;
  virtual void DrawImpl(Graphics *graphics, float dt) = 0;

  static GameEngine *_instance;

  SDL_Window *_window;
  Graphics *_graphicsObject;
  Timer _engineTimer;

  std::vector<GameObject *> _objects;

  float _oldTime, _currentTime, _deltaTime;
};