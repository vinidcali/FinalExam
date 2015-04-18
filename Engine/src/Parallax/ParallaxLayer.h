#pragma once

#include "../GameObject.h"
#include <string>
#include <SDL_opengl.h>

struct SDL_Texture;
struct SDL_Surface;

class ParallaxLayer: public GameObject
{
public:
  ParallaxLayer(std::string imageName, Vector2 parallaxSpeed);
  ~ParallaxLayer();

  void Initialize(Graphics *graphics);

  void Update(float dt);
  void Draw(Graphics *graphics, Matrix4x4 relativeTo, float dt);

  Vector2 GetParallaxSpeed();

protected:
  std::string _textureName;
  SDL_Surface *_parallaxSurface;
  unsigned int _textureID;

  Vector3 *vertices;
  Vector2 *texCoords;
  Vector4 *colours;
  unsigned int* indices;

  bool _hasTransparency;
  Vector2 _parallaxSpeed;

  GLenum GetFormatForSurface(SDL_Surface *surface);
};