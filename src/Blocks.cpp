#ifdef __APPLE__
#  define GL_SILENCE_DEPRECATION
#  include <GL/glew.h>
#  include <GLFW/glfw3.h>
#endif
#include <iostream>
#include <vector>

#include "Block.h"
#include "Blocks.h"
using namespace std;

vector<BlocksType> blocks_types {
  BlocksType {BlocksID::I,
              vector<vector<char>> {
              { '.', '.', '.', '.' },
              { '1', '1', '1', '1' },
              { '.', '.', '.', '.' },
              { '.', '.', '.', '.' },
              }},
  BlocksType {BlocksID::L,
              vector<vector<char>> {
              { '.', '2', '.', '.' },
              { '.', '2', '.', '.' },
              { '.', '2', '2', '.' },
              { '.', '.', '.', '.' },
              }},
  BlocksType {BlocksID::T,
              vector<vector<char>> {
              { '.', '3', '.', '.' },
              { '.', '3', '3', '.' },
              { '.', '3', '.', '.' },
              { '.', '.', '.', '.' },
              }},
  BlocksType {BlocksID::Z,
              vector<vector<char>> {
              { '.', '4', '.', '.' },
              { '.', '4', '4', '.' },
              { '.', '.', '4', '.' },
              { '.', '.', '.', '.' },
              }},
  BlocksType {BlocksID::L,
              vector<vector<char>> {
              { '.', '5', '5', '.' },
              { '.', '5', '5', '.' },
              { '.', '.', '.', '.' },
              { '.', '.', '.', '.' },
              }},
};

Blocks::Blocks(int _x, int _y, int blocks_types_idx)
    : x(_x), y(_y), blocks_type(blocks_types[blocks_types_idx])
{}

void Blocks::fall()
{
  y++;
}

void Blocks::go_left()
{
  x--;
}

void Blocks::go_right()
{
  x++;
}

vector<vector<int>> Blocks::block_indexes()
{
  vector<vector<char>>& m = blocks_type.blocks_map;
  int                   w, h;
  w = h = m.size();
  vector<vector<int>> indexes;
  for (int y_idx = 0; y_idx < h; y_idx++) {
    for (int x_idx = 0; x_idx < w; x_idx++) {
      if (m[y_idx][x_idx] != '.') {
        indexes.push_back(vector<int> { x_idx + x, y_idx + y });
      }
    }
  }
  return indexes;
}
