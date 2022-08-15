#pragma once
#ifdef __APPLE__
#  define GL_SILENCE_DEPRECATION
#  include <GL/glew.h>
#  include <GLFW/glfw3.h>
#endif
#include <vector>

class BgColor
{
 public:
  bool                 isUpping;
  std::vector<GLfloat> color;
  BgColor();
  void update();
};
