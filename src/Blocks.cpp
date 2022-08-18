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
              { '.', '.', '1', '.' },
              { '.', '.', '1', '.' },
              { '.', '.', '1', '.' },
              { '.', '.', '1', '.' },
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
