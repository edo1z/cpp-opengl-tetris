#ifdef __APPLE__
#  define GL_SILENCE_DEPRECATION
#  include <GL/glew.h>
#  include <GLFW/glfw3.h>
#endif
#include <iostream>
#include <string>
#include <vector>

#include "Block.h"
#include "GameMap.h"

int GameMap::size()
{
  return w * h;
}
std::vector<GLfloat> GameMap::position(int idx)
{
  int     x_idx = idx % w;
  int     y_idx = idx / w;
  GLfloat x     = -1.0f + 2.0f / w * x_idx;
  GLfloat y     = 1.0f - 2.0f / h * y_idx;
  return std::vector<GLfloat> { x, y };
}

void GameMap::init_game_map()
{
  game_map = default_game_map;
}

GameMap::GameMap(int _w, int _h, std::string _game_map): w(_w), h(_h)
{
  for (char c : _game_map) {
    if (c == '#' || c == '.') {
      default_game_map.push_back(c);
    }
  }
  init_game_map();
}

void GameMap::update_vertexes_and_colors()
{
  std::vector<GLfloat> color = { 0.5f, 0.5f, 0.5f };
  std::vector<GLfloat> _vertexes;
  std::vector<GLfloat> _colors;
  for (int i = 0; i < size(); i++) {
    if (game_map[i] == '#') {
      Block block(2.0f / w, 2.0f / h, position(i), color);
      _vertexes.insert(
          _vertexes.end(), block.positions.begin(), block.positions.end());
      _colors.insert(_colors.end(), block.colors.begin(), block.colors.end());
    }
  }
  vertexes = _vertexes;
  colors   = _colors;
}
