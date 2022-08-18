#ifdef __APPLE__
#  define GL_SILENCE_DEPRECATION
#  include <GL/glew.h>
#  include <GLFW/glfw3.h>
#endif
#include <iostream>
#include <string>
#include <vector>

#include "Block.h"
#include "Blocks.h"
#include "Game.h"
#include "GameMap.h"
#include "key_callbacks.h"
#include "shader.h"
using namespace std;

int main()
{
  GLFWwindow* window = NULL;
  GLuint      vao;
  GLuint      vertex_vbo;
  GLuint      color_vbo;
  Game        game;
  GLfloat     screen_w = game.gamemap.screen_w();
  GLfloat     screen_h = game.gamemap.screen_h();

  game.update_vertexes_and_colors();

  if (! glfwInit()) return 1;
  atexit(glfwTerminate);

  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  window = glfwCreateWindow(screen_w, screen_h, "C++ OpenGL テトリス", NULL, NULL);
  if (! window) {
    cerr << "Failed to create window." << endl;
    return 1;
  }

  glfwSetKeyCallback(window, key_callback);
  glfwMakeContextCurrent(window);
  glfwSwapInterval(1);
  glewExperimental = GL_TRUE;
  if (glewInit() != GLEW_OK) {
    cerr << "Can't initialize GLEW" << endl;
    return 1;
  }

  glEnable(GL_DEPTH_TEST);
  glDepthFunc(GL_LESS);

  glGenVertexArrays(1, &vao);
  glBindVertexArray(vao);

  glGenBuffers(1, &vertex_vbo);
  glGenBuffers(1, &color_vbo);
  glBindBuffer(GL_ARRAY_BUFFER, color_vbo);
  glBufferData(
      GL_ARRAY_BUFFER, game.colors.size() * sizeof(GLfloat), game.colors.data(), GL_STATIC_DRAW);

  GLint shader = makeShader();
  while (! glfwWindowShouldClose(window)) {
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glUseProgram(shader);

    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, vertex_vbo);
    glBufferData(
        GL_ARRAY_BUFFER, game.vertexes.size() * sizeof(GLfloat), game.vertexes.data(),
        GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);

    glEnableVertexAttribArray(1);
    glBindBuffer(GL_ARRAY_BUFFER, color_vbo);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, NULL);

    for (int i = 0; i < game.vertexes.size() - 4; i += 4) {
      glDrawArrays(GL_TRIANGLE_FAN, i, 4);
    }

    glfwPollEvents();
    glfwSwapBuffers(window);
  }
}
