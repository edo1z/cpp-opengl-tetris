#pragma once
#ifdef __APPLE__
#  define GL_SILENCE_DEPRECATION
#  include <GL/glew.h>
#  include <GLFW/glfw3.h>
#endif
#include <iostream>
#include <vector>

void key_callback(
    GLFWwindow *window, int key, int scancode, int action, int mods);
