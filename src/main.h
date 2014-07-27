#ifndef __GLHYP_MAIN_H
#define __GLHYP_MAIN_H

#include <GL/glew.h>
#include <SDL.h>


char *read_entire_file (const char *path);
GLuint set_up_shader (const char *shader_path,
                      GLenum shaderType);
void set_up_program (const char *vert_shader_path,
                     const char *frag_shader_path);
void main_loop (SDL_Surface *screen);


#endif /* __GLHYP_MAIN_H */
