#pragma once // Preprocessor directive to ensure that this header will only be included once. -- Generally used on Windows

// Preprocessor directive to ensure that this header will only be included once. -- Generally used for all environments.
/*#ifndef _GAME_ENGINE_H_
#define _GAME_ENGINE_H_

#endif // _GAME_ENGINE_H_*/

#include "MathUtils.h"
#include "Player.h"
#include "Timer.h"

// Forward declaring our renderer and window.
// Because we're using them as pointers, we don't need to know their size
// at compile time to define this class.

/**
 * GameEngine.h
 * Purpose: A basic description of the game engine.
 *
 * By: Justin Wilkinson
 */


struct SDL_Renderer;
struct SDL_Window;

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
  virtual void DrawImpl(SDL_Renderer *renderer, float dt) = 0;

  static GameEngine *_instance;

  SDL_Window *_window;
  SDL_Renderer *_renderer;
  Timer _engineTimer;

  float _oldTime, _currentTime, _deltaTime;
};