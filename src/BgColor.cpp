#ifdef __APPLE__
#  define GL_SILENCE_DEPRECATION
#  include <GL/glew.h>
#  include <GLFW/glfw3.h>
#endif
#include <vector>

#include "BgColor.h"

BgColor::BgColor()
{
  color    = { 0.0f, 0.0f, 0.0f };
  isUpping = true;
}

void BgColor::update()
{
  if (isUpping) {
    if (color[0] <= 0.2) {
      color[0] += 0.001;
    } else if (color[1] <= 0.3) {
      color[1] += 0.001;
    } else if (color[2] <= 0.5) {
      color[2] += 0.001;
    } else {
      isUpping = false;
    }
  } else {
    if (color[0] >= 0.2) {
      color[0] -= 0.001;
    } else if (color[1] >= 0.2) {
      color[1] -= 0.001;
    } else if (color[2] >= 0.3) {
      color[2] -= 0.001;
    } else {
      isUpping = true;
    }
  }
}
