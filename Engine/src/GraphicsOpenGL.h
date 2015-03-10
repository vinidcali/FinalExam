#pragma once

#include "Graphics.h"

struct SDL_Window;
#include <SDL_opengl.h>

class GraphicsOpenGL : public Graphics
{
public:
  void Initialize(SDL_Window *window);
  void Shutdown();

  void SetClearColour(float r, float g, float b, float a);
  void ClearScreen();

  void Present();

protected:
};