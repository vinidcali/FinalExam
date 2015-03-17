#include "Game.h"
#include <GameObject.h>
#include <SDL.h>
#include <math.h>
#include <SDL_image.h>
#include <SDL_opengl.h>
#include <InputManager.h>

#include "Cube.h"
#include <Cameras/Camera.h>
#include <Cameras/PerspectiveCamera.h>
#include <Cameras/OrthographicCamera.h>

// Initializing our static member pointer.
GameEngine* GameEngine::_instance = nullptr;

GameEngine* GameEngine::CreateInstance()
{
  if (_instance == nullptr)
  {
    _instance = new Game();
  }
  return _instance;
}

Game::Game() : GameEngine()
{

}

Game::~Game()
{
}

void Game::InitializeImpl()
{
  SDL_SetWindowTitle(_window, "Game");

  float nearPlane = 0.01f;
  float farPlane = 100.0f;
  Vector4 position(3.5f, 2.5f, 2.5f, 0.0f);
  Vector4 lookAt = Vector4::Normalize(Vector4::Difference(Vector4(0.0f, 0.0f, 0.0f, 0.0f), position));
  Vector4 up(0.0f, 1.0f, 0.0f, 0.0f);

  //_camera = new PerspectiveCamera(100.0f, 1.0f, nearPlane, farPlane, position, lookAt, up);
  _camera = new OrthographicCamera(-10.0f, 10.0f, 10.0f, -10.0f, nearPlane, farPlane, position, lookAt, up);

  _objects.push_back(new Cube(Vector3(0.0f, 2.0f, 0.0f)));
  _objects.push_back(new Cube(Vector3(1.0f, 1.0f, 0.0f)));
  _objects.push_back(new Cube(Vector3(1.0f, 0.0f, 1.0f)));
  _objects.push_back(new Cube(Vector3(0.0f, 1.0f, 1.0f)));

  for (auto itr = _objects.begin(); itr != _objects.end(); itr++)
  {
    (*itr)->Initialize(_graphicsObject);
  }
}

void Game::UpdateImpl(float dt)
{
  //SDL_Event evt;
  //SDL_PollEvent(&evt);
  InputManager::GetInstance()->Update(dt);

  if (InputManager::GetInstance()->GetKeyState(SDLK_UP, SDL_KEYUP) == true)
  {
    Vector4 position = _camera->GetPosition();
    position.y += 1.0f;

    Vector4 lookAt = Vector4::Normalize(Vector4::Difference(Vector4(1.0f, 0.0f, 0.0f, 0.0f), position));

    _camera->SetPosition(position);
    _camera->SetLookAtVector(lookAt);
  }
  else if (InputManager::GetInstance()->GetKeyState(SDLK_DOWN, SDL_KEYUP) == true)
  {
    Vector4 position = _camera->GetPosition();
    position.y -= 1.0f;

    Vector4 lookAt = Vector4::Normalize(Vector4::Difference(Vector4(1.0f, 0.0f, 0.0f, 0.0f), position));

    _camera->SetPosition(position);
    _camera->SetLookAtVector(lookAt);
  }

  for (auto itr = _objects.begin(); itr != _objects.end(); itr++)
  {
    (*itr)->Update(dt);
  }
}

void Game::DrawImpl(Graphics *graphics, float dt)
{
  std::vector<GameObject *> renderOrder = _objects;
  //CalculateDrawOrder(renderOrder);

  glPushMatrix();

  CalculateCameraViewpoint();

  for (auto itr = renderOrder.begin(); itr != renderOrder.end(); itr++)
  {
    (*itr)->Draw(graphics, _camera->GetProjectionMatrix(), dt);
  }

  glPopMatrix();
}

void Game::CalculateDrawOrder(std::vector<GameObject *>& drawOrder)
{
  // SUPER HACK GARBAGE ALGO.
  drawOrder.clear();

  auto objectsCopy = _objects;
  auto farthestEntry = objectsCopy.begin();
  while (objectsCopy.size() > 0)
  {
    bool entryFound = true;
    for (auto itr = objectsCopy.begin(); itr != objectsCopy.end(); itr++)
    {
      if (farthestEntry != itr)
      {
        if ((*itr)->GetTransform().position.y < (*farthestEntry)->GetTransform().position.y)
        {
          entryFound = false;
          farthestEntry = itr;
          break;
        }
      }
    }

    if (entryFound)
    {
      GameObject *farthest = *farthestEntry;

      drawOrder.push_back(farthest);
      objectsCopy.erase(farthestEntry);
      farthestEntry = objectsCopy.begin();
    }
  }
}

void Game::CalculateCameraViewpoint()
{
  Vector4 xAxis(1.0f, 0.0f, 0.0f, 0.0f);
  Vector4 yAxis(0.0f, 1.0f, 0.0f, 0.0f);
  Vector4 zAxis(0.0f, 0.0f, 1.0f, 0.0f);

  Vector3 cameraVector(_camera->GetLookAtVector().x, _camera->GetLookAtVector().y, _camera->GetLookAtVector().z);
  Vector3 lookAtVector(0.0f, 0.0f, -1.0f);

  Vector3 cross = Vector3::Normalize(Vector3::Cross(cameraVector, lookAtVector));
  float dot = MathUtils::ToDegrees(Vector3::Dot(lookAtVector, cameraVector));

  glRotatef(cross.x * dot, 1.0f, 0.0f, 0.0f);
  glRotatef(cross.y * dot, 0.0f, 1.0f, 0.0f);
  glRotatef(cross.z * dot, 0.0f, 0.0f, 1.0f);

  glTranslatef(-_camera->GetPosition().x, -_camera->GetPosition().y, -_camera->GetPosition().z);
}