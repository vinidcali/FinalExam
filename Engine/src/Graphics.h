#pragma once

#include "MathUtils.h"

struct SDL_Window;

class Graphics
{
public:
  virtual void Initialize(SDL_Window *window);
  virtual void Shutdown();

  virtual void SetClearColour(float r, float g, float b, float a);
  virtual void ClearScreen();

  virtual void Present();

protected:
  void *_rendererObject;
  Vector4 _clearColour;
};