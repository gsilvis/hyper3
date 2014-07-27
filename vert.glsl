#version 130
in vec4 position;
in vec4 color;

uniform mat4 mat;
smooth out vec4 theColor;
void main() {
//  vec4 cameraPosition = position*vec4(0.25, 0.25, 0.75, 1) + vec4(offset.x, offset.y, offset.z, 0);
  gl_Position = mat * position;
  theColor = color;
}
