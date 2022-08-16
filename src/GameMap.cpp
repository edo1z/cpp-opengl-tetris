#ifdef __APPLE__
#  define GL_SILENCE_DEPRECATION
#  include <GL/glew.h>
#  include <GLFW/glfw3.h>
#endif
#include <iostream>
#include <string>
#include <vector>

#include "GameMap.h"

std::vector<GLfloat> GameMap::position(int idx)
{
  int     x_idx = idx % w;
  int     y_idx = idx / w;
  GLfloat x     = -1.0f + 2.0f / w * x_idx;
  GLfloat y     = 1.0f - 2.0f / h * y_idx;
  return std::vector<GLfloat> { x, y };
}
GameMap::GameMap(int _w, int _h, std::string _game_map): w(_w), h(_h)
{
  for (char c : _game_map) {
    if (c == '#' || c == '.') {
      game_map.push_back(c);
    }
  }
}
int GameMap::size()
{
  return w * h;
}
