#include "ParallaxLayer.h"
#include "../Graphics/GraphicsOpenGL.h"
#include <SDL_image.h>
#include <string>

// Rough estimate of pixel:unit assuming no z-depth for layer.
#define PIXELS_PER_UNIT 100

ParallaxLayer::ParallaxLayer(std::string imageName, Vector2 parallaxSpeed)
{
  _textureName = imageName;
  _parallaxSpeed = parallaxSpeed;
}

ParallaxLayer::~ParallaxLayer()
{
  SDL_FreeSurface(_parallaxSurface);
  _parallaxSurface = nullptr;
}

Vector2 ParallaxLayer::GetParallaxSpeed()
{
  return _parallaxSpeed;
}

void ParallaxLayer::Initialize(Graphics *graphics)
{
  _parallaxSurface = IMG_Load(_textureName.c_str());
  std::string formatName = SDL_GetPixelFormatName(_parallaxSurface->format->format);

  float unitWidth = _parallaxSurface->w / PIXELS_PER_UNIT;
  float unitHeight = _parallaxSurface->h / PIXELS_PER_UNIT;

  GLenum format = GetFormatForSurface(_parallaxSurface);
  _hasTransparency = _parallaxSurface->format->Amask != 0.0f;

  glGenTextures(1, &_textureID);

  glEnable(GL_TEXTURE_2D);
  glBindTexture(GL_TEXTURE_2D, _textureID);

  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

  glTexImage2D(GL_TEXTURE_2D, 0, format, _parallaxSurface->w, _parallaxSurface->h, 0, format, GL_UNSIGNED_BYTE, _parallaxSurface->pixels);

  glDisable(GL_TEXTURE_2D);

  vertices = new Vector3[4];
  texCoords = new Vector2[4];
  colours = new Vector4[4];
  indices = new unsigned int[6];

  float vertPosition = 5.5f;
  vertices[0] = Vector3(-(unitWidth / 2.0f), (unitHeight / 2.0f), 0.5);
  vertices[1] = Vector3((unitWidth / 2.0f), (unitHeight / 2.0f), 0.5f);
  vertices[2] = Vector3(-(unitWidth / 2.0f), -(unitHeight / 2.0f), 0.5f);
  vertices[3] = Vector3((unitWidth / 2.0f), -(unitHeight / 2.0f), 0.5f);

  texCoords[0] = Vector2(0.0f, 0.0f);
  texCoords[1] = Vector2(1.0f, 0.0f);
  texCoords[2] = Vector2(0.0f, 1.0f);
  texCoords[3] = Vector2(1.0f, 1.0f);

  colours[0] = Vector4(1.0f, 0.0f, 0.0f, 0.5f);
  colours[1] = Vector4(1.0f, 0.0f, 0.0f, 0.5f);
  colours[2] = Vector4(1.0f, 0.0f, 0.0f, 0.5f);
  colours[3] = Vector4(1.0f, 0.0f, 0.0f, 0.5f);

  indices[0] = 0;
  indices[1] = 1;
  indices[2] = 2;

  indices[3] = 2;
  indices[4] = 1;
  indices[5] = 3;
}

void ParallaxLayer::Update(float dt)
{

}

void ParallaxLayer::Draw(Graphics *graphics, Matrix4x4 relativeTo, float dt)
{
  glEnable(GL_TEXTURE_2D);

  glEnableClientState(GL_VERTEX_ARRAY);
  glEnableClientState(GL_TEXTURE_COORD_ARRAY);
  glEnableClientState(GL_INDEX_ARRAY);

  glBindTexture(GL_TEXTURE_2D, _textureID);

  glVertexPointer(3, GL_FLOAT, 0, vertices);
  glTexCoordPointer(2, GL_FLOAT, 0, texCoords);

  if (_hasTransparency)
  {
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  }

  glPushMatrix();
  {
    glTranslatef(_transform.position.x, _transform.position.y, _transform.position.z);
    glRotatef(_transform.rotation.x, 1.0f, 0.0f, 0.0f);
    glRotatef(_transform.rotation.y, 0.0f, 1.0f, 0.0f);
    glRotatef(_transform.rotation.z, 0.0f, 0.0f, 1.0f);

    glScalef(_transform.scale.x, _transform.scale.y, _transform.scale.z);

    int indexCount = sizeof(indices) / sizeof(unsigned int);
    indexCount = 6;
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, indices);
  }
  glPopMatrix();

  if (_hasTransparency)
  {
    glDisable(GL_BLEND);
  }

  glDisableClientState(GL_VERTEX_ARRAY);
  glDisableClientState(GL_TEXTURE_COORD_ARRAY);
  glDisableClientState(GL_INDEX_ARRAY);

  glDisable(GL_TEXTURE_2D);
}

/* Got this on StackOverflow a while back. If I can find the link, I'll provide it.*/
GLenum ParallaxLayer::GetFormatForSurface(SDL_Surface *surface)
{
  GLenum textureFormat = GL_NONE;
  // get the number of channels in the SDL surface
  GLuint nOfColors = surface->format->BytesPerPixel;
  if (nOfColors == 4)     // contains an alpha channel
  {
    if (surface->format->Rmask == 0x000000ff)
    {
      textureFormat = GL_RGBA;
    }
    else
      textureFormat = GL_BGRA;
  }
  else if (nOfColors == 3)     // no alpha channel
  {
    if (surface->format->Rmask == 0x000000ff)
      textureFormat = GL_RGB;
    else
      textureFormat = GL_BGR;
  }
  else {
    printf("warning: the image is not truecolor..  this will probably break\n");
    // this error should not go unhandled
  }

  return textureFormat;
}