#ifdef __APPLE__
#  define GL_SILENCE_DEPRECATION
#  include <GL/glew.h>
#  include <GLFW/glfw3.h>
#endif
#include <iostream>
#include <vector>

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
