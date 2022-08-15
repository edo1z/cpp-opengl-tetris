#ifdef __APPLE__
#  define GL_SILENCE_DEPRECATION
#  include <GL/glew.h>
#  include <GLFW/glfw3.h>
#endif
#include <vector>

#include "Triangle.h"

Triangle::Triangle()
{
  points = { 0.0f, 0.5f,   0.0f, 0.5f, -0.5f, 0.0f, -0.5f, -0.5f, 0.0f,
             0.0f, -0.75f, 0.0f, 0.5f, 0.25f, 0.0f, -0.5f, 0.25f, 0.0f };
  colors = { 1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
             0.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f };
}
void Triangle::move()
{
  if (points[6] > 1) {
    points[0]  = -1.5;
    points[3]  = -1.0;
    points[6]  = -2.0;
    points[9]  = -1.5;
    points[12] = -1.0;
    points[15] = -2.0;
  } else {
    points[0] += 0.01;
    points[3] += 0.01;
    points[6] += 0.01;
    points[9] += 0.01;
    points[12] += 0.01;
    points[15] += 0.01;
  }
}
