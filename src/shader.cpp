#ifdef __APPLE__
#  define GL_SILENCE_DEPRECATION
#  include <GL/glew.h>
#  include <GLFW/glfw3.h>
#endif
#include <fstream>
#include <iostream>
#include <vector>

bool readShaderSource(const char* name, std::vector<GLchar>& buffer)
{
  if (name == NULL) return false;
  std::ifstream file(name);
  if (file.fail()) {
    std::cerr << "Error: Can't open source file: " << name << std::endl;
    return false;
  }
  file.seekg(0L, std::ios::end);
  GLsizei length = static_cast<GLsizei>(file.tellg());
  buffer.resize(length + 1);
  file.seekg(0L, std::ios::beg);
  file.read(buffer.data(), length);
  buffer[length] = '\0';

  if (file.fail()) {
    std::cerr << "Error: Could not read source file: " << name << std::endl;
    file.close();
    return false;
  }

  file.close();
  return true;
}

GLint makeShader()
{
  const char*         vertFileName = "src/shaders/point.vert";
  const char*         flagFileName = "src/shaders/point.frag";
  std::vector<GLchar> vsrc;
  std::vector<GLchar> fsrc;
  const bool          vstat = readShaderSource(vertFileName, vsrc);
  const bool          fstat = readShaderSource(flagFileName, fsrc);
  if (! vstat || ! fstat) {
    std::cerr << "Error: Could not read source file" << std::endl;
    return 0;
  }
  const char* vertex_shader   = vsrc.data();
  const char* fragment_shader = fsrc.data();
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
