#ifdef __APPLE__
#  define GL_SILENCE_DEPRECATION
#  include <GL/glew.h>
#  include <GLFW/glfw3.h>
#endif
#include <iostream>
#include <vector>

#include "Block.h"

using namespace std;

vector<BlockType> block_types {
  BlockType {  BlockID::HARD, vector<GLfloat> { 0.5f, 0.5f, 0.5f }, false},
  BlockType {   BlockID::RED, vector<GLfloat> { 0.8f, 0.0f, 0.0f },  true},
  BlockType { BlockID::GREEN, vector<GLfloat> { 0.0f, 0.8f, 0.0f },  true},
  BlockType {  BlockID::BLUE, vector<GLfloat> { 0.0f, 0.0f, 0.9f },  true},
  BlockType {BlockID::PURPLE, vector<GLfloat> { 0.6f, 0.0f, 0.6f },  true},
};

Block::Block(GLfloat _w, GLfloat _h, vector<GLfloat> _posi, int block_types_idx)
    : w(_w), h(_h), block_type(block_types[block_types_idx]), position(_posi)
{
  GLfloat x = position[0];
  GLfloat y = position[1];
  positions = {
    x, y, 0.0f, x + w, y, 0.0f, x + w, y - h, 0.0f, x, y - h, 0.0f
  };
  GLfloat r = block_type.color[0];
  GLfloat g = block_type.color[1];
  GLfloat b = block_type.color[2];
  colors    = {
    r, g, b, r, g, b, r, g, b, r, g, b,
  };
}
