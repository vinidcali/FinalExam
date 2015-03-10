#include "GameEngine.h"
#include <SDL.h>
#include <SDL_image.h>
#include "MathUtils.h"
#include "Graphics.h"
#include "GraphicsOpenGL.h"
#include <SDL_opengl.h>

GameEngine::GameEngine()
{

}

GameEngine::~GameEngine()
{

}

SDL_GLContext gContext;

void GameEngine::Initialize()
{
  SDL_Init(SDL_INIT_EVERYTHING);

  _window = SDL_CreateWindow("Engine",
    SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
    640, 640,
    SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);

  _graphicsObject = new GraphicsOpenGL();
  _graphicsObject->Initialize(_window);

  IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG | IMG_INIT_TIF | IMG_INIT_WEBP);

  InitializeImpl();

  /* Get the time at the beginning of our game loop so that we can track the
  * elapsed difference. */
  _engineTimer.Start();
}

void GameEngine::Shutdown()
{
  /* Stop the engine timer as we're shutting down. */
  _engineTimer.Stop();

  _graphicsObject->Shutdown();
  SDL_DestroyWindow(_window);

  /* Quit and clean up all libraries. */
  IMG_Quit();
  SDL_Quit();
}

void GameEngine::Update()
{
  // Calculating the time difference since our last loop.
  _engineTimer.Update();

  UpdateImpl(_engineTimer.GetDeltaTime());
}

void GameEngine::Draw()
{
  // Set the draw colour for screen clearing.
  _graphicsObject->SetClearColour(1.0f, 1.0f, 1.0f, 1.0f);

  // Clear the renderer with the current draw colour.
  _graphicsObject->ClearScreen();

  DrawImpl(_graphicsObject, _engineTimer.GetDeltaTime());

  // Present what is in our renderer to our window.
  _graphicsObject->Present();
}