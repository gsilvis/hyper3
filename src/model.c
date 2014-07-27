#include "model.h"

#include <GL/glew.h>
#include <stdio.h>
#include <stdlib.h>

#include "view.h"

GLuint buf_obj = 0;
size_t len = 0;
GLfloat *buffer = NULL;

void model_read (const char *path) {
  FILE *f = fopen(path, "r");
  if (!f) {
    fprintf(stderr, "Error loading model at '%s'\n", path);
    return;
  }
  int i;
  for (i = 0; 1; i++) {
    buffer = realloc(buffer, (i+1)*sizeof(GLfloat));
    if (fscanf(f, "%f,", &buffer[i]) != 1) {
      break;
    }
  }
  len = i / 8;
  glGenBuffers(1, &buf_obj);
  glBindBuffer(GL_ARRAY_BUFFER, buf_obj);
  glBufferData(GL_ARRAY_BUFFER, i*sizeof(GLfloat), buffer, GL_STATIC_DRAW);
}


void render (void) {
  glBindBuffer(GL_ARRAY_BUFFER, buf_obj);
  glEnableVertexAttribArray(0);
  glEnableVertexAttribArray(1);
  glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 32, (const GLfloat *)0);
  glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 32, (const GLfloat *)16);

  GLfloat model_loc[4] = {0, 0, 0, 1};

  for (int i = -2; i <= 2; i++) {
    model_loc[0] = 0.45*i;
    for (int j = -2; j <= 2; j++) {
      model_loc[1] = 0.45*j;
      for (int k = -2; k <= 0; k++) {
        model_loc[2] = 0.45*k;
        set_model_loc(model_loc);
        glDrawArrays(GL_TRIANGLES, 0, len);
      }
    }
  }
#if 0
  GLfloat model_loc_1[4] = {0, 0, 0, 1};
  set_model_loc(model_loc_1);
  glDrawArrays(GL_TRIANGLES, 0, len);

  GLfloat model_loc_2[4] = {-0.25, 0.25, 0.25, 1};
  set_model_loc(model_loc_2);
  glDrawArrays(GL_TRIANGLES, 0, len);
#endif

  glDisableVertexAttribArray(0);
  glDisableVertexAttribArray(1);
}
