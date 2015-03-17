#include "GraphicsOpenGL.h"
#include <SDL.h>
#include <SDL_opengl.h>
#include <gl\GLU.h>

SDL_GLContext _glContext;

void GraphicsOpenGL::Initialize(SDL_Window *window)
{
  _window = window;

  _glContext = SDL_GL_CreateContext(window);
  int success = SDL_GL_SetSwapInterval(1);

  /* Request opengl 3.2 context.
  * SDL doesn't have the ability to choose which profile at this time of writing,
  * but it should default to the core profile */
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);

  /* Turn on double buffering with a 24bit Z buffer.
  * You may need to change this to 16 or 32 for your system */
  SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
  SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);

  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();

  glEnable(GL_DEPTH_TEST);

  glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
  glClearDepth(1.0f);

  //gluPerspective(100.0f, 1.0f, 0.01f, 100.0f);

  ClearScreen();
}

void GraphicsOpenGL::Shutdown()
{
  SDL_GL_DeleteContext(_glContext);
}

void GraphicsOpenGL::SetClearColour(float r, float g, float b, float a)
{
  // Set the draw colour for screen clearing.
  glClearColor(r, g, b, a);
}

void GraphicsOpenGL::ClearScreen()
{
  // Clear the renderer with the current draw colour.
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void GraphicsOpenGL::Present()
{ 
  SDL_GL_SwapWindow(_window);
}