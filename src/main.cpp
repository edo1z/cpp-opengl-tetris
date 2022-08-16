#ifdef __APPLE__
#  define GL_SILENCE_DEPRECATION
#  include <GL/glew.h>
#  include <GLFW/glfw3.h>
#endif
#include <iostream>
#include <vector>

#include "BgColor.h"
#include "Block.h"
#include "key_callbacks.h"
#include "shader.h"
#include "Triangle.h"

const GLfloat SCREEN_WIDTH   = 450.0f;
const GLfloat SCREEN_HEIGHT  = 750.0f;
const int     BLOCK_NUMBER_X = 15;
const GLfloat BLOCK_WIDTH    = SCREEN_WIDTH / BLOCK_NUMBER_X;
const GLfloat BLOCK_HEIGHT   = BLOCK_WIDTH;

void          init_blocks(
             std::vector<GLfloat>& blocks, std::vector<GLfloat>& block_colors)
{
  GLfloat              w     = BLOCK_WIDTH / SCREEN_WIDTH;
  GLfloat              h     = BLOCK_HEIGHT / SCREEN_HEIGHT;
  std::vector<GLfloat> posi  = { 0.0f, 0.0f, 0.0f };
  std::vector<GLfloat> color = { 0.0f, 1.0f, 1.0f };
  Block                bl(w, h, posi, color);
  blocks                     = bl.positions;
  block_colors               = bl.colors;
  std::vector<GLfloat> posi2 = { 0.0f, 0.0f + h, 0.0f };
  Block                bl2(w, h, posi2, color);
  blocks.insert(blocks.end(), bl2.positions.begin(), bl2.positions.end());
  block_colors.insert(block_colors.end(), bl2.colors.begin(), bl2.colors.end());
}

int main()
{
  GLFWwindow*          window = NULL;
  GLuint               vao;
  GLuint               vertex_vbo;
  GLuint               color_vbo;
  Triangle             triangle;
  BgColor              bgColor;
  std::vector<GLfloat> blocks;
  std::vector<GLfloat> block_colors;

  init_blocks(blocks, block_colors);

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
      /* GL_ARRAY_BUFFER, 18 * sizeof(GLfloat), triangle.colors.data(), */
      /* GL_STATIC_DRAW); */
      GL_ARRAY_BUFFER, 24 * sizeof(GLfloat), block_colors.data(),
      GL_STATIC_DRAW);

  GLint shader = makeShader();
  while (! glfwWindowShouldClose(window)) {
    bgColor.update();
    glClearColor(bgColor.color[0], bgColor.color[1], bgColor.color[2], 0.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glUseProgram(shader);

    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, vertex_vbo);
    triangle.move();
    glBufferData(
        /* GL_ARRAY_BUFFER, 18 * sizeof(GLfloat), triangle.points.data(), */
        /* GL_STATIC_DRAW); */
        GL_ARRAY_BUFFER, 24 * sizeof(GLfloat), blocks.data(), GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);

    glEnableVertexAttribArray(1);
    glBindBuffer(GL_ARRAY_BUFFER, color_vbo);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, NULL);

    glDrawArrays(GL_TRIANGLE_FAN, 0, 8);

    glfwPollEvents();
    glfwSwapBuffers(window);
  }
}
