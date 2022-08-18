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

const vector<vector<char>> DEFAULT_GAME_MAP = {
  {'.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.'},
  {'.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.'},
  {'.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.'},
  {'.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.'},
  {'#', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '#'},
  {'#', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '#'},
  {'#', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '#'},
  {'#', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '#'},
  {'#', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '#'},
  {'#', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '#'},
  {'#', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '#'},
  {'#', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '#'},
  {'#', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '#'},
  {'#', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '#'},
  {'#', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '#'},
  {'#', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '#'},
  {'#', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '#'},
  {'#', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '#'},
  {'#', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '#'},
  {'#', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '#'},
  {'#', '1', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '#'},
  {'#', '1', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '#'},
  {'#', '1', '2', '2', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '#'},
  {'#', '1', '2', '2', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '#'},
  {'#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#'},
};

int GameMap::screen_w()
{
  return block_size * w;
}

int GameMap::screen_h()
{
  return block_size * h;
}

vector<GLfloat> GameMap::position(int x_idx, int y_idx)
{
  GLfloat x = -1.0f + 2.0f / w * x_idx;
  GLfloat y = 1.0f - 2.0f / h * y_idx;
  return vector<GLfloat> { x, y };
}

void GameMap::init_game_map()
{
  game_map = DEFAULT_GAME_MAP;
}

GameMap::GameMap(int _block_size)
    : w(DEFAULT_GAME_MAP[0].size())
    , h(DEFAULT_GAME_MAP.size())
    , block_size(_block_size)
{
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
  for (int y_idx = 0; y_idx < h; y_idx++) {
    for (int x_idx = 0; x_idx < w; x_idx++) {
      switch (game_map[y_idx][x_idx]) {
        case '#':
        case '0': {
          Block block(w_rate, h_rate, position(x_idx, y_idx), 0);
          _insert(_vertexes, _colors, block);
          break;
        }
        case '1': {
          Block block(w_rate, h_rate, position(x_idx, y_idx), 1);
          _insert(_vertexes, _colors, block);
          break;
        }
        case '2': {
          Block block(w_rate, h_rate, position(x_idx, y_idx), 2);
          _insert(_vertexes, _colors, block);
          break;
        }
        case '3': {
          Block block(w_rate, h_rate, position(x_idx, y_idx), 3);
          _insert(_vertexes, _colors, block);
          break;
        }
        case '4': {
          Block block(w_rate, h_rate, position(x_idx, y_idx), 4);
          _insert(_vertexes, _colors, block);
          break;
        }
        case '5': {
          Block block(w_rate, h_rate, position(x_idx, y_idx), 5);
          _insert(_vertexes, _colors, block);
          break;
        }
      }
    }
  }
  vertexes = _vertexes;
  colors   = _colors;
}
