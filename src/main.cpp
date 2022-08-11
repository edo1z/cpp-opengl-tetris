#ifdef __APPLE__
#  define GL_SILENCE_DEPRECATION
#  include <GL/glew.h>
#  include <GLFW/glfw3.h>
#endif
#include <iostream>
#include <vector>

#include "key_callbacks.h"
#include "shader.h"

void updateBgColor(std::vector<GLfloat> &v, bool &isUpping)
{
  if (isUpping) {
    if (v[0] <= 0.2) {
      v[0] += 0.001;
    } else if (v[1] <= 0.3) {
      v[1] += 0.001;
    } else if (v[2] <= 0.5) {
      v[2] += 0.001;
    } else {
      isUpping = false;
    }
  } else {
    if (v[0] >= 0.2) {
      v[0] -= 0.001;
    } else if (v[1] >= 0.2) {
      v[1] -= 0.001;
    } else if (v[2] >= 0.3) {
      v[2] -= 0.001;
    } else {
      isUpping = true;
    }
  }
}

void move(std::vector<GLfloat> &v)
{
  if (v[6] > 1) {
    v[0]  = -1.5;
    v[3]  = -1.0;
    v[6]  = -2.0;
    v[9]  = -1.5;
    v[12] = -1.0;
    v[15] = -2.0;
  } else {
    v[0] += 0.01;
    v[3] += 0.01;
    v[6] += 0.01;
    v[9] += 0.01;
    v[12] += 0.01;
    v[15] += 0.01;
  }
}

int main()
{
  GLFWwindow          *window = NULL;
  GLuint               vao;
  GLuint               vertex_vbo;
  GLuint               color_vbo;
  std::vector<GLfloat> bgColor         = { 0.0f, 0.0f, 0.0f };
  bool                 isBgColorUpping = true;

  std::vector<GLfloat> points          = { 0.0f, 0.5f,  0.0f,  0.5f, -0.5f,
                                  0.0f, -0.5f, -0.5f, 0.0f };
  std::vector<GLfloat> points2         = { 0.0f, -0.75f, 0.0f,  0.5f, 0.25f,
                                   0.0f, -0.5f,  0.25f, 0.0f };
  points.insert(points.end(), points2.begin(), points2.end());
  std::vector<GLfloat> colors = { 1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f,
                                  0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,
                                  1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f };

  if (! glfwInit()) return 1;
  atexit(glfwTerminate);

  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
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
      GL_ARRAY_BUFFER, 18 * sizeof(GLfloat), colors.data(), GL_STATIC_DRAW);

  GLint shader = makeShader();
  while (! glfwWindowShouldClose(window)) {
    updateBgColor(bgColor, isBgColorUpping);
    glClearColor(bgColor[0], bgColor[1], bgColor[2], 0.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glUseProgram(shader);

    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, vertex_vbo);
    move(points);
    glBufferData(
        GL_ARRAY_BUFFER, 18 * sizeof(GLfloat), points.data(), GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);

    glEnableVertexAttribArray(1);
    glBindBuffer(GL_ARRAY_BUFFER, color_vbo);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, NULL);

    glDrawArrays(GL_TRIANGLES, 0, 6);

    glfwPollEvents();
    glfwSwapBuffers(window);
  }
}
