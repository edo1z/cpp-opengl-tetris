#version 330
layout(location = 0) in vec3 position;
layout(location = 1) in vec3 color;
out vec3 colors;

void main() {
  colors = color;
  gl_Position = vec4(position, 1.0);
}
