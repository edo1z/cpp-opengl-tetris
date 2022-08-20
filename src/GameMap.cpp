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
  {'.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.'},
  {'.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.'},
  {'.', '.', '.', '.', '#', '.', '.', '.', '.', '.', '.', '#', '.', '.', '.', '.'},
  {'.', '.', '.', '.', '#', '.', '.', '.', '.', '.', '.', '#', '.', '.', '.', '.'},
  {'#', '#', '#', '#', '#', '.', '.', '.', '.', '.', '.', '#', '#', '#', '#', '#'},
  {'#', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '#'},
  {'#', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '#'},
  {'#', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '#'},
  {'#', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '#'},
  {'#', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '#'},
  {'#', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '#'},
  {'#', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '#'},
  {'#', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '#'},
  {'#', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '#'},
  {'#', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '#'},
  {'#', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '#'},
  {'#', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '#'},
  {'#', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '#'},
  {'#', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '#'},
  {'#', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '#'},
  {'#', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '#'},
  {'#', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '#'},
  {'#', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '#'},
  {'#', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '#'},
  {'#', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '#'},
  {'#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#'},
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
    : w(DEFAULT_GAME_MAP[0].size()), h(DEFAULT_GAME_MAP.size()), block_size(_block_size)
{
  init_game_map();
}

void _insert(vector<GLfloat>& _vertexes, vector<GLfloat>& _colors, Block& block)
{
  _vertexes.insert(_vertexes.end(), block.positions.begin(), block.positions.end());
  _colors.insert(_colors.end(), block.colors.begin(), block.colors.end());
}

void GameMap::insert_vertexes_and_colors(
    int x_idx, int y_idx, char c, vector<GLfloat>& vertexes, vector<GLfloat>& colors)
{
  GLfloat w_rate = 2.0f / w;
  GLfloat h_rate = 2.0f / h;
  switch (c) {
    case '#':
    case '0': {
      Block block(w_rate, h_rate, position(x_idx, y_idx), 0);
      _insert(vertexes, colors, block);
      break;
    }
    case '1': {
      Block block(w_rate, h_rate, position(x_idx, y_idx), 1);
      _insert(vertexes, colors, block);
      break;
    }
    case '2': {
      Block block(w_rate, h_rate, position(x_idx, y_idx), 2);
      _insert(vertexes, colors, block);
      break;
    }
    case '3': {
      Block block(w_rate, h_rate, position(x_idx, y_idx), 3);
      _insert(vertexes, colors, block);
      break;
    }
    case '4': {
      Block block(w_rate, h_rate, position(x_idx, y_idx), 4);
      _insert(vertexes, colors, block);
      break;
    }
    case '5': {
      Block block(w_rate, h_rate, position(x_idx, y_idx), 5);
      _insert(vertexes, colors, block);
      break;
    }
  }
}

void GameMap::update_vertexes_and_colors()
{
  vector<GLfloat> _vertexes;
  vector<GLfloat> _colors;
  for (int y_idx = 0; y_idx < h; y_idx++) {
    for (int x_idx = 0; x_idx < w; x_idx++) {
      insert_vertexes_and_colors(x_idx, y_idx, game_map[y_idx][x_idx], _vertexes, _colors);
    }
  }
  vertexes = _vertexes;
  colors   = _colors;
}

bool GameMap::is_collision(int x_idx, int y_idx, int x_vec, int y_vec)
{
  x_idx += x_vec;
  y_idx += y_vec;
  if (game_map[y_idx][x_idx] == '.') return false;
  return true;
}

vector<int> GameMap::deletable_rows()
{
  vector<int> _deletable_rows;
  for (int y_idx = 0; y_idx < h - BOTTOM_ROWS; y_idx++) {
    bool deletable = true;
    for (int x_idx = 0; x_idx < w; x_idx++) {
      if (game_map[y_idx][x_idx] == '.') {
        deletable = false;
      }
    }
    if (deletable) {
      _deletable_rows.push_back(y_idx);
    }
  }
  return _deletable_rows;
}

void GameMap::delete_rows(vector<int> deletable_rows)
{
  vector<vector<char>> tmp_map = game_map;
  for (int idx : deletable_rows) {
    tmp_map.erase(tmp_map.begin() + idx);
    tmp_map.insert(
        tmp_map.begin() + GAMEOVER_LINE + 1, DEFAULT_GAME_MAP.begin() + GAMEOVER_LINE + 1,
        DEFAULT_GAME_MAP.begin() + GAMEOVER_LINE + 2);
  }
  /* game_map = tmp_map; */
}
