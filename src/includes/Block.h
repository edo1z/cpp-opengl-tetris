#pragma once
#ifdef __APPLE__
#  define GL_SILENCE_DEPRECATION
#  include <GL/glew.h>
#  include <GLFW/glfw3.h>
#endif
#include <iostream>
#include <vector>

class Block
{
 public:
  GLfloat              w;
  GLfloat              h;
  std::vector<GLfloat> position;
  std::vector<GLfloat> positions;
  std::vector<GLfloat> color;
  std::vector<GLfloat> colors;
  Block(
      GLfloat _w, GLfloat _h, std::vector<GLfloat> _posi,
      std::vector<GLfloat> _color);
};
