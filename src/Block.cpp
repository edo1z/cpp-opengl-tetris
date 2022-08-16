#ifdef __APPLE__
#  define GL_SILENCE_DEPRECATION
#  include <GL/glew.h>
#  include <GLFW/glfw3.h>
#endif
#include <iostream>
#include <vector>

#include "Block.h"

Block::Block(
    GLfloat _w, GLfloat _h, std::vector<GLfloat> _posi,
    std::vector<GLfloat> _color)
    : w(_w), h(_h), position(_posi), color(_color)
{
  GLfloat x = position[0];
  GLfloat y = position[1];
  positions = {
    x, y, 0.0f, x + w, y, 0.0f, x + w, y + h, 0.0f, x, y + h, 0.0f
  };
  GLfloat r = color[0];
  GLfloat g = color[1];
  GLfloat b = color[2];
  colors    = {
    r, g, b, r, g, b, r, g, b, r, g, b,
  };
}
