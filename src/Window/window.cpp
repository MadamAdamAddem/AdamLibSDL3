#include "../include/Window.h"
#include <string>

#define GW_ GameWindow::


GW_ GameWindow(const std::string& title, int _w = 1280, int _h = 720) : m_window(SDL_CreateWindow(title.c_str(), _w, _h, 0), SDL_DestroyWindow)
{

}