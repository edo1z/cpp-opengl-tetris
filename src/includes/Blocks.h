#pragma once
#ifdef __APPLE__
#  define GL_SILENCE_DEPRECATION
#  include <GL/glew.h>
#  include <GLFW/glfw3.h>
#endif
#include <vector>

#include "Block.h"

class Blocks
{
 public:
  std::vector<GLfloat> map;
  std::vector<Block>   blocks;
  std::vector<GLfloat> vertexes;
  std::vector<GLfloat> colors;
  Blocks();
};
