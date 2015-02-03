#include "Timer.h"
#include <SDL.h>

Timer::Timer() : _duration(0.0f) 
{
  Stop();
}

void Timer::Update()
{
  if (_state == RUNNING)
  {
    _oldTime = _currentTime;
    _currentTime = SDL_GetTicks();
    _deltaTime = (_currentTime - _oldTime) / 1000;

    _elapsedTime += _deltaTime;

    if (_duration > 0.0f && _elapsedTime >= _duration)
    {
      Stop();
    }
  }
}

void Timer::Start()
{
  if (_state != PAUSED)
  {
    _oldTime = _currentTime = SDL_GetTicks();
  }

  _state = RUNNING;
}

void Timer::Pause()
{
  _state = PAUSED;
  _deltaTime = 0;
}

void Timer::Stop()
{
  _state = STOPPED;
  Reset();
}

void Timer::Reset()
{
  _deltaTime = 0;
  _elapsedTime = 0;
  _currentTime = 0;
}

float Timer::GetElapsedTime()
{
  return _elapsedTime;
}

float Timer::GetDeltaTime()
{
  return _deltaTime;
}

float Timer::GetDuration()
{
  return _duration;
}

void Timer::SetDuration(float duration)
{
  _duration = duration;
}

void Timer::SetTimerEvent(TimerEvent evt)
{
  _timerEvt = nullptr;
  _timerInstEvt = nullptr;

  _timerEvt = evt;
}

void Timer::SetTimerEvent(TimerInstanceEvent evt)
{
  _timerEvt = nullptr;
  _timerInstEvt = nullptr;

  _timerInstEvt = evt;
}