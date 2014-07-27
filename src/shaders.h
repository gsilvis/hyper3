#ifndef __HYPER3_SHADERS_H
#define __HYPER3_SHADERS_H

#include <GL/glew.h>

char *read_entire_file (const char *path);
GLuint set_up_shader (const char *shader_path,
                      GLenum shaderType);
void set_up_program (const char *vert_shader_path,
                     const char *frag_shader_path);

#endif /* __HYPER3_SHADERS_H */
