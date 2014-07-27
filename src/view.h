#ifndef __GLHYP_VIEW_H
#define __GLHYP_VIEW_H

#include <GL/glew.h>

void reshape (int w, int h);
void set_camera_loc (const GLfloat *loc);
void set_model_loc (const GLfloat *loc);
void insert_mat (void);

#endif /* __GLHYP_VIEW_H */
