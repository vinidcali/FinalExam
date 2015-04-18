#include "ParallaxSystem.h"
#include "ParallaxLayer.h"

ParallaxSystem::ParallaxSystem() { }

ParallaxSystem::~ParallaxSystem() { }

void ParallaxSystem::Initialize(Graphics *graphics)
{
  for (int layerIndex = 0; layerIndex < LayerCount(); layerIndex++)
  {
    _parallaxLayers[layerIndex]->Initialize(graphics);
  }
}

void ParallaxSystem::Update(Vector2 difference, float dt)
{
  for (int layerIndex = 0; layerIndex < LayerCount(); layerIndex++)
  {
    ParallaxLayer *currentLayer = _parallaxLayers[layerIndex];
    currentLayer->GetTransform().position.x += difference.x * currentLayer->GetParallaxSpeed().x * dt;
    currentLayer->GetTransform().position.y += difference.y * currentLayer->GetParallaxSpeed().y * dt;
    currentLayer->Update(dt);
  }
}

void ParallaxSystem::Draw(Graphics *graphics, Matrix4x4 relativeTo, float dt)
{
  for (int layerIndex = 0; layerIndex < LayerCount(); layerIndex++)
  {
    _parallaxLayers[layerIndex]->Draw(graphics, relativeTo, dt);
  }
}

void ParallaxSystem::PushLayer(ParallaxLayer *layer)
{
  _parallaxLayers.push_back(layer);
}

ParallaxLayer* ParallaxSystem::PopLayer()
{
  /* vector::end() returns an iterator to the last element in the vector. Since it's an iterator, we can
   * dereference it back into a ParallaxLayer pointer. */
  ParallaxLayer *lastLayerAdded = *(_parallaxLayers.end());
  _parallaxLayers.pop_back();

  return lastLayerAdded;
}

bool ParallaxSystem::AddLayerAtIndex(ParallaxLayer *layer, int index)
{
  bool didAdd = false;
  if (index < LayerCount())
  {
    _parallaxLayers.insert(_parallaxLayers.begin() + index, layer);
  }

  return didAdd;
}

ParallaxLayer* ParallaxSystem::RemoveLayerAtIndex(int index)
{
  ParallaxLayer *layerRemoved = nullptr;
  if (index < LayerCount())
  {
    std::vector<ParallaxLayer *>::iterator itr = _parallaxLayers.erase(_parallaxLayers.begin() + index);
    layerRemoved = (*itr);
  }

  return layerRemoved;
}

int ParallaxSystem::LayerCount()
{
  return _parallaxLayers.size();
}