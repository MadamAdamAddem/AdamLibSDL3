#include <AdamLib/Input.hpp>
#include <AdamLib/Signal.hpp>

#include <SDL3/SDL_mouse.h>
#include <SDL3/SDL_keyboard.h>
#include <SDL3/SDL_events.h>

using namespace AdamLib;


const bool* input_mask = SDL_GetKeyboardState(NULL);
uint32_t mouse_mask;
Input::Mouse mouse;



Signal<> key_changed[231];
Signal<> mouse_changed[7];

bool Input::processEvents()
{
  static SDL_Event e;
  if(!SDL_PollEvent(&e))
    return true;

  if(e.type == SDL_EVENT_QUIT)
    return false;

  if(e.type == SDL_EVENT_MOUSE_MOTION)
    mouse_changed[MOUSE_MOTION].emit();

  if(e.type == SDL_EVENT_MOUSE_BUTTON_DOWN || e.type == SDL_EVENT_MOUSE_BUTTON_UP)
  {
    mouse_mask = SDL_GetMouseState(nullptr, nullptr);
    mouse_changed[static_cast<int>(e.button.button)].emit();
  }
    


  
  if((e.type == SDL_EVENT_KEY_DOWN || e.type == SDL_EVENT_KEY_UP) && !e.key.repeat)
  {
    key_changed[e.key.scancode].emit();
  }


  return true;
}


//Function given will be called upon specified key change
//Returns controller to disconnect. If not disconnected, then will cause problems.
ConnectionController Input::connectKeyChange(Keys _key, std::function<void(void)> _func)
{
  return key_changed[_key].connect(_func);
}

ConnectionController Input::connectMouseChange(MouseInput _mouse_input, std::function<void(void)> _func)
{
  return mouse_changed[_mouse_input].connect(_func);
}


bool Input::keystate(Keys _key)
{
  return input_mask[_key];
}

bool Input::mousestate(MouseInput _mouse_key)
{
  return mouse_mask & SDL_BUTTON_MASK(_mouse_key);
}