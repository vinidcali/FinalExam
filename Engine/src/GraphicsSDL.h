#include "Graphics.h"

struct SDL_Renderer;

class GraphicsSDL : public Graphics
{
public:
  void Initialize(SDL_Window *window);
  void Shutdown();

  void SetClearColour(float r, float g, float b, float a);
  void ClearScreen();

  void Present();

  SDL_Renderer *GetRenderer();
};