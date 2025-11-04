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
  static SDL_Event* eptr = &e;
  bool mouse_motion = false;
  while(SDL_PollEvent(eptr))
  {
    switch(e.type)
    {
      case SDL_EVENT_QUIT:
        return false;

      case SDL_EVENT_MOUSE_MOTION:
        mouse_motion = true;
        break;

      case SDL_EVENT_KEY_DOWN:
      case SDL_EVENT_KEY_UP:
        if(!e.key.repeat) key_changed[e.key.scancode].emit();
        break;


      case SDL_EVENT_MOUSE_BUTTON_DOWN:
      case SDL_EVENT_MOUSE_BUTTON_UP:
        mouse_mask = SDL_GetMouseState(NULL, NULL);
        mouse_changed[static_cast<int>(e.button.button)].emit();
        break;


      
    }
  }
    
  if(mouse_motion) //called outside of poll event loop to prevent high polling rate mice from spamming emissions
    mouse_changed[MOUSE_MOTION].emit();


  return true;
}


//Function given will be called upon specified key change
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