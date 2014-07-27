#include "shaders.h"

#include <stdlib.h>
#include <stdio.h>
#include <GL/glew.h>

char *read_entire_file (const char *path) {
  long length;
  char *buffer;
  FILE *fp = fopen (path, "rb");
  if (!fp) {
    return NULL;
  }
  fseek(fp, 0L, SEEK_END);
  length = ftell(fp);
  rewind(fp);
  buffer = calloc(1, length + 1);
  if (!buffer) {
    return NULL;
  }
  if (1 != fread(buffer, length, 1, fp)) {
    free(buffer);
    return NULL;
  }
  fclose(fp);
  return buffer;
}

GLuint set_up_shader (const char *shader_path,
                      GLenum shaderType) {
  GLuint shader = glCreateShader(shaderType);
  GLchar *shader_source = read_entire_file(shader_path);
  glShaderSource(shader, 1, (const GLchar**)&shader_source, NULL);
  free(shader_source);
  glCompileShader(shader);
  GLint status;
  glGetShaderiv(shader, GL_COMPILE_STATUS, &status);
  if (GL_FALSE == status) {
    fprintf(stderr, "A shader failed to compile.\n");
    GLint infoLogLength;
    glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infoLogLength);
    GLchar *strInfoLog = malloc(infoLogLength + 1);
    glGetShaderInfoLog(shader, infoLogLength, NULL, strInfoLog);
    fprintf(stderr, "Compiler error:  %s\n", strInfoLog);
    free(strInfoLog);
    return -1;
  }
  return shader;
}

void set_up_program (const char *vert_shader_path,
                     const char *frag_shader_path) {
  GLuint vert_shader = set_up_shader(vert_shader_path, GL_VERTEX_SHADER);
  GLuint frag_shader = set_up_shader(frag_shader_path, GL_FRAGMENT_SHADER);
  GLuint program = glCreateProgram();
  glAttachShader(program, vert_shader);
  glAttachShader(program, frag_shader);
  glLinkProgram(program);
  GLint status;
  glGetProgramiv(program, GL_LINK_STATUS, &status);
  if (GL_FALSE == status) {
    fprintf(stderr, "The program failed to link.\n");
    GLint infoLogLength;
    glGetProgramiv(program, GL_INFO_LOG_LENGTH, &infoLogLength);
    GLchar *strInfoLog = malloc(infoLogLength + 1);
    glGetProgramInfoLog(program, infoLogLength, NULL, strInfoLog);
    fprintf(stderr, "Linker failure: %s\n", strInfoLog);
    free(strInfoLog);
    return;
  }
  glUseProgram(program);
  glBindAttribLocation(program, 0, "position");
  glBindAttribLocation(program, 1, "color");
  glLinkProgram(program);
}
