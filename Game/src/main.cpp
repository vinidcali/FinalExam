#include <iostream>
#include "Game.h"

using namespace std;

int main(int argc, char** argv)
{
  GameEngine *engine = GameEngine::CreateInstance();
  engine->Initialize();

  while(true)
  {
    engine->Update();
    engine->Draw();
  }

  engine->Shutdown();

  return 0;
}