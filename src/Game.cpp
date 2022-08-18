#ifdef __APPLE__
#  define GL_SILENCE_DEPRECATION
#  include <GL/glew.h>
#  include <GLFW/glfw3.h>
#endif
#include <iostream>
#include <random>
#include <vector>

#include "Block.h"
#include "Blocks.h"
#include "Game.h"
using namespace std;

Game::Game()
    : now_blocks(random_blocks(6, 0))
    , next_blocks(random_blocks(0, 0))
    , gamemap(GameMap(BLOCK_SIZE))
{}

Blocks Game::random_blocks(int x, int y)
{
  random_device rnd;
  return Blocks(x, y, rnd() % 5);
}

void Game::update_vertexes_and_colors()
{
  vector<GLfloat> _vertexes;
  vector<GLfloat> _colors;
  gamemap.update_vertexes_and_colors();
  _vertexes = gamemap.vertexes;
  _colors   = gamemap.colors;

  int                   y_idx, x_idx, w, h, _x_idx, _y_idx;
  char                  c;
  vector<vector<char>>& now_map  = now_blocks.blocks_type.blocks_map;
  vector<vector<char>>& next_map = next_blocks.blocks_type.blocks_map;
  w = h = now_map.size();
  for (_y_idx = 0; _y_idx < h; _y_idx++) {
    for (_x_idx = 0; _x_idx < w; _x_idx++) {
      c     = now_map[_y_idx][_x_idx];
      x_idx = _x_idx + now_blocks.x;
      y_idx = _y_idx + now_blocks.y;
      gamemap.insert_vertexes_and_colors(x_idx, y_idx, c, _vertexes, _colors);

      c     = next_map[_y_idx][_x_idx];
      x_idx = _x_idx + next_blocks.x;
      y_idx = _y_idx + next_blocks.y;
      gamemap.insert_vertexes_and_colors(x_idx, y_idx, c, _vertexes, _colors);
    }
  }
  vertexes = _vertexes;
  colors   = _colors;
}
