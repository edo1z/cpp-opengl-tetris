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

using namespace std;

int GameMap::size()
{
  return w * h;
}
vector<GLfloat> GameMap::position(int idx)
{
  int     x_idx = idx % w;
  int     y_idx = idx / w;
  GLfloat x     = -1.0f + 2.0f / w * x_idx;
  GLfloat y     = 1.0f - 2.0f / h * y_idx;
  return vector<GLfloat> { x, y };
}

void GameMap::init_game_map()
{
  game_map = default_game_map;
}

vector<char> enabled_chars = { '#', '.', '1', '2', '3', '4', '5' };

GameMap::GameMap(int _w, int _h, string _game_map): w(_w), h(_h)
{
  for (char c : _game_map) {
    auto result = find(enabled_chars.begin(), enabled_chars.end(), c);
    if (result != enabled_chars.end()) {
      default_game_map.push_back(c);
    }
  }
  init_game_map();
}

void _insert(vector<GLfloat>& _vertexes, vector<GLfloat>& _colors, Block& block)
{
  _vertexes.insert(
      _vertexes.end(), block.positions.begin(), block.positions.end());
  _colors.insert(_colors.end(), block.colors.begin(), block.colors.end());
}

void GameMap::update_vertexes_and_colors()
{
  vector<GLfloat> _vertexes;
  vector<GLfloat> _colors;
  GLfloat         w_rate = 2.0f / w;
  GLfloat         h_rate = 2.0f / h;
  for (int i = 0; i < size(); i++) {
    switch (game_map[i]) {
      case '#':
      case '0': {
        Block block(w_rate, h_rate, position(i), 0);
        _insert(_vertexes, _colors, block);
        break;
      }
      case '1': {
        Block block(w_rate, h_rate, position(i), 1);
        _insert(_vertexes, _colors, block);
        break;
      }
      case '2': {
        Block block(w_rate, h_rate, position(i), 2);
        _insert(_vertexes, _colors, block);
        break;
      }
      case '3': {
        Block block(w_rate, h_rate, position(i), 3);
        _insert(_vertexes, _colors, block);
        break;
      }
      case '4': {
        Block block(w_rate, h_rate, position(i), 4);
        _insert(_vertexes, _colors, block);
        break;
      }
      case '5': {
        Block block(w_rate, h_rate, position(i), 5);
        _insert(_vertexes, _colors, block);
        break;
      }
    }
  }
  vertexes = _vertexes;
  colors   = _colors;
}
