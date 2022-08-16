#pragma once
#ifdef __APPLE__
#  define GL_SILENCE_DEPRECATION
#  include <GL/glew.h>
#  include <GLFW/glfw3.h>
#endif
#include <iostream>
#include <string>
#include <vector>

class GameMap
{
 public:
  int               w, h;  // ブロックの個数
  std::vector<char> game_map;
  GameMap(int _w, int _h, std::string _game_map);
  std::vector<GLfloat> position(int idx);
  int                  size();
};
