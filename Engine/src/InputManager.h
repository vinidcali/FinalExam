/**
 * \class InputManager
 * \brief A wrapper singleton that manages SDL's input mechanism.
 * \author Justin Wilkinson
 * \date January 27, 2015
 */

#pragma once
#include <SDL_events.h>
#include <map>
#include <vector>

// A feign class we use to use to trick the system into providing callback support with member functions.
class IInput { };
typedef void(*InputEvent)(SDL_Event e);
typedef void(IInput::*InputMemberEvent)(SDL_Event e);

class InputBlock;
struct InputPair;

class InputManager
{
public:
  /**
  * \fn static InputManager* InputManager::GetInstance()
  * \brief A static method to get the single instance of this class.
  * \return The single InputManager instance.
  */
  static InputManager* GetInstance();

  /**
  * \fn static void InputManager::DestroyInstance()
  * \brief A static method to destroy the single instance of this class.
  */
  static void DestroyInstance();

  /**
  * \fn InputManager::~InputManager()
  * \brief The class' standard destructor.
  */
  ~InputManager();

  /**
  * \fn void InputManager::AssignEvent(SDL_EventType evt, InputEvent callback)
  * \brief Assigns the given callback function to be called when the given event is triggered.
  * \param evt The event type to listen for.
  * \param callback The static callback to fire when the event is fired.
  */
  void AssignEvent(SDL_EventType evt, InputEvent callback);

  /**
  * \fn void InputManager::AssignEvent(SDL_EventType evt, void *target, InputMemberEvent callback)
  * \brief Assigns the given callback function to be called when the given event is triggered.
  * \param evt The event type to listen for.
  * \param target The object that we want to call the callback function on.
  * \param callback The member callback to fire when the event is fired.
  */
  void AssignEvent(SDL_EventType evt, void *target, InputMemberEvent callback);

  /**
  * \fn void InputManager::RemoveEvent(SDL_EventType evt, InputEvent callback)
  * \brief Unassigns the given callback function.
  * \param evt The event type to remove.
  * \param callback The static callback that was assigned with the event.
  */
  void RemoveEvent(SDL_EventType evt, InputEvent callback);

  /**
  * \fn void InputManager::RemoveEvent(SDL_EventType evt, void *target, InputMemberEvent callback)
  * \brief Unassigns the given callback function.
  * \param evt The event type to remove.
  * \param target The object that we assigned the callback to.
  * \param callback The static callback that was assigned with the event.
  */
  void RemoveEvent(SDL_EventType evt, void *target, InputMemberEvent callback);

  /**
  * \fn void InputManager::Update(float dt)
  * \brief Updates the InputManager.
  * \param dt The time since the last update.
  */
  void Update(float dt);

  /**
  * \fn void InputManager::IsKeyDown(SDL_Keycode keycode)
  * \brief Gets whether or not the given key is down (being pressed).
  * \param keycode The keycode for the key we want to check.
  * \return Whether or not the given key is down (true/false).
  */
  bool IsKeyDown(SDL_Keycode keycode);

  /**
  * \fn void InputManager::GetKeyState(SDL_Keycode keycode, SDL_EventType eventType)
  * \brief Gets whether or not the given key is in the provided state.
  * \param keycode The keycode for the key we want to check.
  * \param eventType The status we want to check against (eg. SDL_KEYDOWN/SDL_KEYUP).
  * \return Whether or not the given key is in the provided state (true/false).
  */
  bool GetKeyState(SDL_Keycode keycode, SDL_EventType eventType);

protected:
  /**
  * \fn void InputManager::InputManager()
  * \brief Standard constructor for InputManager.
  */
  InputManager();

  /**
  * \fn void InputManager::ProcessEvent(SDL_Event evt)
  * \brief Process the given SDL event.
  * \param evt An SDL event we want to process, and check against triggers for.
  */
  void ProcessEvent(SDL_Event evt);

  static InputManager *_instance;
  std::map<SDL_EventType, std::vector<InputBlock *> > _eventMap;
  std::map<SDL_EventType, std::vector<InputPair *> > _memberEventMap;

  std::map<SDL_Keycode, SDL_EventType> _keyMap;
  std::vector<std::pair<SDL_Keycode, SDL_EventType> > _keysToRemove;
};