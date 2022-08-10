#ifdef __APPLE__
#  define GL_SILENCE_DEPRECATION
#  include <GL/glew.h>
#  include <GLFW/glfw3.h>
#endif
#include <iostream>
#include <vector>

static void key_callback(
    GLFWwindow *window, int key, int scancode, int action, int mods)
{
  if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
    glfwSetWindowShouldClose(window, GLFW_TRUE);
}

GLint makeShader()
{
  const char *vertex_shader   = "#version 150\n"
                                "in vec3 vp;"
                                "void main() {"
                                "  gl_Position = vec4(vp, 1.0);"
                                "}";
  const char *fragment_shader = "#version 150\n"
                                "out vec4 frag_colour;"
                                "void main() {"
                                "  frag_colour = vec4(0.1, 0.1, 0.1, 1.0);"
                                "}";
  GLuint      vs, fs;
  GLuint      shader_programme;
  vs = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(vs, 1, &vertex_shader, NULL);
  glCompileShader(vs);
  fs = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(fs, 1, &fragment_shader, NULL);
  glCompileShader(fs);
  shader_programme = glCreateProgram();
  glAttachShader(shader_programme, fs);
  glAttachShader(shader_programme, vs);
  glLinkProgram(shader_programme);
  return shader_programme;
}

void updateBgColor(std::vector<GLfloat> &v, bool &isUpping)
{
  if (isUpping) {
    if (v[0] <= 1) {
      v[0] += 0.1;
    } else if (v[1] <= 1) {
      v[1] += 0.1;
    } else if (v[2] <= 1) {
      v[2] += 0.1;
    } else {
      isUpping = false;
    }
  } else {
    if (v[0] >= 0) {
      v[0] -= 0.1;
    } else if (v[1] >= 0) {
      v[1] -= 0.1;
    } else if (v[2] >= 0) {
      v[2] -= 0.1;
    } else {
      isUpping = true;
    }
  }
}

int main()
{
  GLFWwindow          *window = NULL;
  GLuint               vao;
  GLuint               vbo;
  std::vector<GLfloat> bgColor         = { 0.0f, 0.0f, 0.0f };
  bool                 isBgColorUpping = true;

  /* GLfloat              points[]        = { */
  /*   0.0f, 0.5f, 0.0f, 0.5f, -0.5f, 0.0f, -0.5f, -0.5f, 0.0f */
  /* }; */
  std::vector<GLfloat> points1         = { 0.0f, 0.5f,  0.0f,  0.5f, -0.5f,
                                   0.0f, -0.5f, -0.5f, 0.0f };
  std::vector<GLfloat> points2         = { 0.0f, -0.5f, 0.0f, 0.5f, 0.5f,
                                   0.0f, -0.5f, 0.5f, 0.0f };
  points1.insert(points1.end(), points2.begin(), points2.end());

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

  glGenBuffers(1, &vbo);
  glBindBuffer(GL_ARRAY_BUFFER, vbo);
  glBufferData(
      GL_ARRAY_BUFFER, 18 * sizeof(GLfloat), points1.data(), GL_STATIC_DRAW);

  glGenVertexArrays(1, &vao);
  glBindVertexArray(vao);
  glEnableVertexAttribArray(0);
  glBindBuffer(GL_ARRAY_BUFFER, vbo);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);

  GLint shader = makeShader();
  while (! glfwWindowShouldClose(window)) {
    updateBgColor(bgColor, isBgColorUpping);
    glClearColor(bgColor[0], bgColor[1], bgColor[2], 0.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glUseProgram(shader);
    glBindVertexArray(vao);
    glDrawArrays(GL_TRIANGLES, 0, 6);
    glfwPollEvents();
    glfwSwapBuffers(window);
  }
}
