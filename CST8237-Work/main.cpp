#include <iostream>
#include <SDL.h>

using namespace std;

int main(int argc, char** argv)
{
  SDL_Init(SDL_INIT_VIDEO);

  SDL_Window *window = SDL_CreateWindow("CST8237 Lab",
    SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
    640, 640, 
    SDL_WINDOW_SHOWN);

  SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

  int posX = 100, posY = 100;
  while(true)
  {
    SDL_Event evt;
    SDL_PollEvent(&evt);

    // Set the draw colour for screen clearing.
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

    // Clear the renderer with the current draw colour.
    SDL_RenderClear(renderer);

    // Set the draw colour for our point.
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);

    // Draw the point.
    SDL_RenderDrawPoint(renderer, posX, posY);

    posY = (posY < 640) ? posY + 1 : posY;

    // Present what is in our renderer to our window.
    SDL_RenderPresent(renderer);
  }

  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);

  return 0;
}