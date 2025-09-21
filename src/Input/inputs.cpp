#include "../include/Input.h"
#include "../include/Signal.h"

#include <iostream>

using namespace AdamLib;


const bool* input_mask = SDL_GetKeyboardState(NULL);
Signal<> key_changed[231];

bool Input::processEvents()
{
  static SDL_Event e;
  if(!SDL_PollEvent(&e))
    return true;

  if(e.type == SDL_EVENT_QUIT)
    return false;

  

  if((e.type == SDL_EVENT_KEY_DOWN || e.type == SDL_EVENT_KEY_UP) && !e.key.repeat)
    key_changed[e.key.scancode].emit();


  return true;
}


uint32_t Input::connectKeyChange(Keys key, void (*_func)(void))
{
  return key_changed[key].connect(_func);
}

void Input::disconnectKeyChange(Keys key, int _id)
{
  key_changed[key].disconnect(_id);
}


bool Input::keystate(Keys key)
{
  return input_mask[key];
}

