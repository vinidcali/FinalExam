#pragma once
#include <SDL_events.h>
#include <map>
#include <string>

struct SDL_Renderer;
struct SDL_Texture;
class Screen;

class ScreenManager
{
public:
  static ScreenManager* GetInstance();
  static void DestroyInstance();

  ~ScreenManager();

  bool ShowScreen(std::string id);
  bool PushScreen(std::string id, Screen *screen);
  bool PopScreen(std::string id);

  void Update();
  void Draw();

  bool IsRunning();
  void SetIsRunning(bool running);

  void ClearRenderer();

  SDL_Renderer* GetRenderer() const;
  SDL_Window* GetWindow() const;

protected:
  static ScreenManager *_instance;
  ScreenManager();

  std::map<std::string, Screen *> _screens;
  Screen *_activeScreen;

  SDL_Window *_window;
  SDL_Renderer *_renderer;
  SDL_Texture *_defaultTarget;

  bool _isRunning;
};