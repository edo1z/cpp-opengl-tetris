#pragma once
#ifdef __APPLE__
#  define GL_SILENCE_DEPRECATION
#  include <GL/glew.h>
#  include <GLFW/glfw3.h>
#endif
#include <vector>

class Triangle
{
 public:
  std::vector<GLfloat> points;
  std::vector<GLfloat> colors;
  Triangle();
  void move();
};
