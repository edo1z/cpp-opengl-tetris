#pragma once
#ifdef __APPLE__
#  define GL_SILENCE_DEPRECATION
#  include <GL/glew.h>
#  include <GLFW/glfw3.h>
#endif
#include <iostream>
#include <vector>
using namespace std;

enum class BlockID { HARD, RED, GREEN, BLUE, PURPLE, YELLOW };

struct BlockType {
  BlockID         id;
  vector<GLfloat> color;
  bool            canBroke;
};

class Block
{
 public:
  GLfloat         w;
  GLfloat         h;
  BlockType&      block_type;
  vector<GLfloat> position;
  vector<GLfloat> positions;
  vector<GLfloat> color;
  vector<GLfloat> colors;
  Block(GLfloat _w, GLfloat _h, vector<GLfloat> _posi, int block_types_idx);
};
