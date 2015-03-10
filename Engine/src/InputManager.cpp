#include "InputManager.h"

class InputBlock
{
public:
  InputBlock(InputEvent callback) : callback(callback) { }
  void ProcessInput(SDL_Event e)
  {
    (*callback)(e);
  }

  InputEvent callback;

};

struct InputPair
{
  void *target;
  InputMemberEvent callback;

  InputPair(void *target, InputMemberEvent callback) : target(target), callback(callback) { }
  void ProcessInput(SDL_Event e)
  {
    IInput *castedTarget = (IInput *)target;
    (castedTarget->*callback)(e);
  }
};

InputManager* InputManager::_instance = NULL;

InputManager* InputManager::GetInstance()
{
  if (_instance == NULL)
  {
    _instance = new InputManager();
  }

  return _instance;
}

void InputManager::DestroyInstance()
{
  if (_instance != NULL)
  {
    delete _instance;
    _instance = NULL;
  }
}

InputManager::InputManager() { }
InputManager::~InputManager() { }

void InputManager::AssignEvent(SDL_EventType evt, InputEvent callback)
{
  InputBlock *newBlock = new InputBlock(callback);

  auto mapItr = _eventMap.find(evt);
  if (mapItr == _eventMap.end())
  {
    std::pair<SDL_EventType, std::vector<InputBlock *> > newPair(evt, std::vector<InputBlock *> { newBlock });
    _eventMap.insert(newPair);
  }
  else
  {
    bool found = false;
    std::vector<InputBlock *> &events = mapItr->second;
    for (auto itr = events.begin(); itr != events.end(); itr++)
    {
      InputBlock *currentBlock = (*itr);
      if (currentBlock->callback == callback)
      {
        /* If the block already exists in our list, we want to remove it.*/
        found = true;
        delete newBlock;
        break;
      }
    }

    if (found == false)
    {
      events.push_back(newBlock);
    }
  }
}

void InputManager::AssignEvent(SDL_EventType evt, void *target, InputMemberEvent callback)
{
  IInput *castedTarget = (IInput *)target;

  InputPair *newPair = new InputPair(castedTarget, callback);

  auto mapItr = _memberEventMap.find(evt);
  if (mapItr == _memberEventMap.end())
  {
    std::pair<SDL_EventType, std::vector<InputPair *> > newEntry(evt, std::vector<InputPair *> { newPair });
    _memberEventMap.insert(newEntry);
  }
  else
  {
    bool found = false;
    std::vector<InputPair *> &events = mapItr->second;
    for (auto itr = events.begin(); itr != events.end(); itr++)
    {
      InputPair *currentPair = (*itr);
      if (currentPair->target == target && currentPair->callback == callback)
      {
        found = true;
        delete newPair;
        break;
      }
    }

    if (found == false)
    {
      events.push_back(newPair);
    }
  }
}

void InputManager::RemoveEvent(SDL_EventType evt, InputEvent callback)
{
  auto mapItr = _eventMap.find(evt);
  if (mapItr != _eventMap.end())
  {
    bool found = false;
    std::vector<InputBlock *> &events = mapItr->second;

    auto itr = events.begin();
    for (; itr != events.end(); itr++)
    {
      InputBlock *currentBlock = (*itr);
      if (currentBlock->callback == callback)
      {
        found = true;
        break;
      }
    }

    if (found == true)
    {
      delete (*itr);
      events.erase(itr);

      // If there aren't any more events for this key, remove it.
      if (events.empty() == true)
      {
        _eventMap.erase(evt);
      }
    }
  }
}

void InputManager::RemoveEvent(SDL_EventType evt, void *target, InputMemberEvent callback)
{
  auto mapItr = _memberEventMap.find(evt);
  if (mapItr != _memberEventMap.end())
  {
    bool found = false;
    std::vector<InputPair *> &events = mapItr->second;

    auto itr = events.begin();
    for (; itr != events.end(); itr++)
    {
      InputPair *currentPair = (*itr);
      if (currentPair->target == target && currentPair->callback == callback)
      {
        found = true;
        break;
      }
    }

    if (found == true)
    {
      delete (*itr);
      events.erase(itr);

      // If there aren't any more events for this key, remove it.
      if (events.empty() == true)
      {
        _memberEventMap.erase(evt);
      }
    }
  }
}

void InputManager::ProcessEvent(SDL_Event e)
{
  SDL_EventType evt = (SDL_EventType)e.type;
  auto mapItr = _eventMap.find(evt);
  if (mapItr != _eventMap.end())
  {
    std::vector<InputBlock *> events = mapItr->second;
    for (auto itr = events.begin(); itr != events.end(); itr++)
    {
      (*itr)->ProcessInput(e);
    }
  }

  auto memberMapItr = _memberEventMap.find(evt);
  if (memberMapItr != _memberEventMap.end())
  {
    std::vector<InputPair *> events = memberMapItr->second;
    for (auto itr = events.begin(); itr != events.end(); itr++)
    {
      (*itr)->ProcessInput(e);
    }
  }
}

void InputManager::Update(float dt)
{
  SDL_Event evt;
  SDL_PollEvent(&evt);

  for (auto keysToRemoveItr = _keysToRemove.begin(); keysToRemoveItr != _keysToRemove.end(); keysToRemoveItr++)
  {
    auto keyMapItr = _keyMap.find(keysToRemoveItr->first);
    _keyMap.erase(keyMapItr);
    printf("KEY ERASED %d\n", _keyMap.size());
  }
  _keysToRemove.clear();

  // Check to see if we already have an entry in our map.
  if (evt.type == SDL_KEYDOWN)
  {
    SDL_Keycode &pressedKey = evt.key.keysym.sym;
    auto keyMapItr = _keyMap.find(pressedKey);
    
    // If we don't already have it in our map, let's add it!
    if (keyMapItr == _keyMap.end())
    {
      std::pair<SDL_Keycode, SDL_EventType> keyPair(pressedKey, SDL_KEYDOWN);
      _keyMap.insert(keyPair);

      printf("KEY DOWN %d\n", _keyMap.size());
    }
  }
  else if (evt.type == SDL_KEYUP)
  {
    SDL_Keycode &pressedKey = evt.key.keysym.sym;
    auto keyMapItr = _keyMap.find(pressedKey);

    // If we have it in our map, let's remove it!
    if (keyMapItr != _keyMap.end())
    {
      keyMapItr->second = SDL_KEYUP;
      _keysToRemove.push_back(*keyMapItr);

      printf("KEY UP %d\n", _keyMap.size());
    }
  }

  // Process any method we've got assigned.
  ProcessEvent(evt);
}

bool InputManager::IsKeyDown(SDL_Keycode keycode)
{
  return GetKeyState(keycode, SDL_KEYDOWN);
}

bool InputManager::GetKeyState(SDL_Keycode keycode, SDL_EventType eventType)
{
  bool doesKeyMatch = false;
  auto keyMapItr = _keyMap.find(keycode);

  // If we find an entry, then let's see if it matches.
  if (keyMapItr != _keyMap.end())
  {
    SDL_EventType &mappedEvent = keyMapItr->second;
    if (mappedEvent == eventType)
    {
      doesKeyMatch = true;
    }
  }

  return doesKeyMatch;
}

