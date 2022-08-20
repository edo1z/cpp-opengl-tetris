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
  BlocksType {BlocksID::I, vector<int> { 2, 2 },
              vector<vector<char>> {
              { '.', '.', '.', '.', '.' },
              { '.', '.', '.', '.', '.' },
              { '1', '1', '1', '1', '.' },
              { '.', '.', '.', '.', '.' },
              { '.', '.', '.', '.', '.' },
              }},
  BlocksType {BlocksID::L, vector<int> { 1, 1 },
              vector<vector<char>> {
              { '.', '2', '.', '.' },
              { '.', '2', '.', '.' },
              { '.', '2', '2', '.' },
              { '.', '.', '.', '.' },
              }},
  BlocksType {BlocksID::T, vector<int> { 1, 1 },
              vector<vector<char>> {
              { '.', '3', '.', '.' },
              { '.', '3', '3', '.' },
              { '.', '3', '.', '.' },
              { '.', '.', '.', '.' },
              }},
  BlocksType {BlocksID::Z, vector<int> { 1, 1 },
              vector<vector<char>> {
              { '.', '4', '.', '.' },
              { '.', '4', '4', '.' },
              { '.', '.', '4', '.' },
              { '.', '.', '.', '.' },
              }},
  BlocksType {BlocksID::L, vector<int> { 1, 1 },
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

void Blocks::rotate(vector<vector<char>> rotated_map)
{
  blocks_type.blocks_map = rotated_map;
}

vector<vector<char>> Blocks::rotated_map(int vec)
{
  vector<int>           center = blocks_type.center;
  vector<vector<char>>& m      = blocks_type.blocks_map;
  int                   h      = m.size();
  int                   w      = m[0].size();
  vector<vector<char>>  tmp_map(h, vector<char>(w, '.'));
  for (int y_idx = 0; y_idx < h; y_idx++) {
    for (int x_idx = 0; x_idx < w; x_idx++) {
      if (m[y_idx][x_idx] != '.') {
        int _x, _y, _x2, _y2;
        _y = y_idx - center[1];  // centerを(0, 0)とした場合の座標
        _x = x_idx - center[0];  // centerを(0, 0)とした場合の座標
        if (vec > 0) {           // 時計回り
          _y2 = -_x;
          _x2 = _y;
        } else {  // 反時計回り
          _y2 = _x;
          _x2 = -_y;
        }
        tmp_map[_y2 + center[1]][_x2 + center[0]] = m[y_idx][x_idx];
      }
    }
  }
  return tmp_map;
}

vector<vector<int>> Blocks::block_indexes()
{
  vector<vector<char>>& m = blocks_type.blocks_map;
  int                   h = m.size();
  int                   w = m[0].size();
  vector<vector<int>>   indexes;
  for (int y_idx = 0; y_idx < h; y_idx++) {
    for (int x_idx = 0; x_idx < w; x_idx++) {
      if (m[y_idx][x_idx] != '.') {
        indexes.push_back(vector<int> { x_idx + x, y_idx + y });
      }
    }
  }
  return indexes;
}
