#version 130
smooth in vec4 theColor;
out vec4 outputColor;
void main() {
//  outputColor = vec4(0.5, 0.5, 0.5, 1);
  outputColor = mix(theColor, vec4(0.5, 0.5, 0.5, 1), 0.5);
}
