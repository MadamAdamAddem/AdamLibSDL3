#pragma once
#include <AdamLib/Defines.hpp>
#include <AdamLib/Utilities/Signal.hpp>
#include <functional>

namespace AdamLib
{


  enum Keys : int
  {
    KEY_A = 4,
    KEY_B,
    KEY_C,
    KEY_D,
    KEY_E,
    KEY_F,
    KEY_G,
    KEY_H,
    KEY_I,
    KEY_J,
    KEY_K,
    KEY_L,
    KEY_M,
    KEY_N,
    KEY_O,
    KEY_P,
    KEY_Q,
    KEY_R,
    KEY_S,
    KEY_T,
    KEY_U,
    KEY_V,
    KEY_W,
    KEY_X,
    KEY_Y,
    KEY_Z = 29,

    KEY_1 = 30,
    KEY_2,
    KEY_3,
    KEY_4,
    KEY_5,
    KEY_6,
    KEY_7,
    KEY_8,
    KEY_9,
    KEY_0 = 39,

    KEY_RETURN = 40,
    KEY_ESCAPE,
    KEY_BACKSPACE,
    KEY_TAB,
    KEY_SPACE,
    KEY_MINUS,
    KEY_EQUALS,
    KEY_LEFTBRACKET,
    KEY_RIGHTBRACKET,
    KEY_BACKSLASH,
    KEY_SEMICOLON = 51,
    KEY_APOSTROPHE,
    KEY_GRAVE,
    KEY_COMMA,
    KEY_PERIOD,
    KEY_SLASH,
    KEY_CAPSLOCK,
    KEY_F1,
    KEY_F2,
    KEY_F3,
    KEY_F4,
    KEY_F5,
    KEY_F6,
    KEY_F7,
    KEY_F8,
    KEY_F9,
    KEY_F10,
    KEY_F11,
    KEY_F12,
    KEY_PRINTSCREEN,
    KEY_SCROLLLOCK,
    KEY_PAUSE,
    KEY_INSERT,
    KEY_HOME,
    KEY_PAGEUP,
    KEY_DELETE,
    KEY_END,
    KEY_PAGEDOWN,
    KEY_RIGHT,
    KEY_LEFT,
    KEY_DOWN,
    KEY_UP = 82,

    KEYPAD_DIVIDE = 84,
    KEYPAD_MULTIPLY,
    KEYPAD_MINUS,
    KEYPAD_PLUS,
    KEYPAD_ENTER,
    KEYPAD_1,
    KEYPAD_2,
    KEYPAD_3,
    KEYPAD_4,
    KEYPAD_5,
    KEYPAD_6,
    KEYPAD_7,
    KEYPAD_8,
    KEYPAD_9,
    KEYPAD_0,
    KEYPAD_PERIOD = 99,
    KEYPAD_EQUALS = 103,

    KEY_F13 = 104,
    KEY_F14,
    KEY_F15,
    KEY_F16,
    KEY_F17,
    KEY_F18,
    KEY_F19,
    KEY_F20,
    KEY_F21,
    KEY_F22,
    KEY_F23,
    KEY_F24 = 115,

    KEY_LCTRL = 224,
    KEY_LSHIFT,
    KEY_LALT, 
    KEY_LGUI, 
    KEY_RCTRL,
    KEY_RSHIFT,
    KEY_RALT, 
    KEY_RGUI = 231,
  };
 

  enum MouseInputs: int
  {
    MOUSE_MOTION = 0,
    MOUSE_LCLICK,
    MOUSE_MCLICK,
    MOUSE_RCLICK,
    MOUSE_S1,
    MOUSE_S2,
    MOUSE_SCROLL = 6,
  };



  namespace Input
  {
    struct Mouse
    {
      double x;
      double y;
    };



    bool processEvents();
    ConnectionController connectKeyChange(Keys _key, std::function<void(void)>);
    ConnectionController connectMouseChange(MouseInputs _mouse_input, std::function<void(void)>);


    bool keystate(Keys _key);
    bool mousestate(MouseInputs _mouse_key);
  }

  #define BMETHOD(Class, Method) std::bind(&Class::Method, this)
  #define RegisterKeyChangeConnection(Key, Method) registerConnection(Input::connectKeyChange(Key, BMETHOD(std::remove_reference_t<decltype(*this)>, Method)))
  #define RegisterMouseChangeConnection(MouseInput, Method) registerConnection(Input::connectMouseChange(MouseInput, BMETHOD(std::remove_reference_t<decltype(*this)>, Method)))


}