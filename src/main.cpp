#ifdef __APPLE__
#  define GL_SILENCE_DEPRECATION
#  include <GL/glew.h>
#  include <GLFW/glfw3.h>
#endif
#include <iostream>
#include <string>
#include <vector>

#include "BgColor.h"
#include "Block.h"
#include "GameMap.h"
#include "key_callbacks.h"
#include "shader.h"
#include "Triangle.h"

const GLfloat     SCREEN_WIDTH   = 450.0f;
const GLfloat     SCREEN_HEIGHT  = 750.0f;
const int         BLOCK_NUMBER_X = 15;
const int         BLOCK_NUMBER_Y = 25;
const std::string GAME_MAP       = R"(
...............
...............
#.............#
#.............#
#.............#
#.............#
#.............#
#.............#
#.............#
#.............#
#.............#
#.............#
#.............#
#.............#
#.............#
#.............#
#.............#
#.............#
#.............#
#.............#
#1............#
#1....44......#
#122.3.4......#
#1223334......#
###############
)";

int               main()
{
  GLFWwindow* window = NULL;
  GLuint      vao;
  GLuint      vertex_vbo;
  GLuint      color_vbo;
  Triangle    triangle;
  BgColor     bgColor;
  GameMap     game_map(BLOCK_NUMBER_X, BLOCK_NUMBER_Y, GAME_MAP);
  game_map.update_vertexes_and_colors();

  if (! glfwInit()) return 1;
  atexit(glfwTerminate);

  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  window =
      glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Hello World", NULL, NULL);
  if (! window) {
    std::cerr << "Failed to create window." << std::endl;
    return 1;
  }

  glfwSetKeyCallback(window, key_callback);
  glfwMakeContextCurrent(window);
  glfwSwapInterval(1);
  glewExperimental = GL_TRUE;
  if (glewInit() != GLEW_OK) {
    std::cerr << "Can't initialize GLEW" << std::endl;
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
      GL_ARRAY_BUFFER, game_map.colors.size() * sizeof(GLfloat),
      game_map.colors.data(), GL_STATIC_DRAW);

  GLint shader = makeShader();
  while (! glfwWindowShouldClose(window)) {
    glClearColor(bgColor.color[0], bgColor.color[1], bgColor.color[2], 0.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glUseProgram(shader);

    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, vertex_vbo);
    triangle.move();
    glBufferData(
        GL_ARRAY_BUFFER, game_map.vertexes.size() * sizeof(GLfloat),
        game_map.vertexes.data(), GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);

    glEnableVertexAttribArray(1);
    glBindBuffer(GL_ARRAY_BUFFER, color_vbo);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, NULL);

    for (int i = 0; i < game_map.vertexes.size() - 4; i += 4) {
      glDrawArrays(GL_TRIANGLE_FAN, i, 4);
    }

    glfwPollEvents();
    glfwSwapBuffers(window);
  }
}
