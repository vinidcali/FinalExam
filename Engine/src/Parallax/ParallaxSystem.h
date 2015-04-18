/**
* ParallaxSystem.h
* Purpose: To allow for the movement and management of parallax layers to create a variety of effects.
*
* By: Justin Wilkinson
*/

#pragma once

#include "../GameObject.h"
#include <vector>

class ParallaxLayer;

class ParallaxSystem
{
public:
  ParallaxSystem();
  ~ParallaxSystem();

  void Initialize(Graphics *graphics);

  void Update(Vector2 difference, float dt);
  void Draw(Graphics *graphics, Matrix4x4 relativeTo, float dt);

  void PushLayer(ParallaxLayer *layer);
  ParallaxLayer* PopLayer();

  bool AddLayerAtIndex(ParallaxLayer *layer, int index);
  ParallaxLayer* RemoveLayerAtIndex(int index);

  int LayerCount();

protected:
  std::vector<ParallaxLayer *> _parallaxLayers;
};