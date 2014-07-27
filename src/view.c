#include "view.h"

#include <GL/glew.h>
#include <stdio.h>

#include "matrix.h"


GLfloat proj_mat[16] = {
  0, 0, 0, 0,
  0, 0, 0, 0,
  0, 0, 0, 0,
  0, 0, 0, 0,
};
GLfloat camera_mat[16] = {
  0, 0, 0, 0,
  0, 0, 0, 0,
  0, 0, 0, 0,
  0, 0, 0, 0,
};
GLfloat model_mat[16] = {
  0, 0, 0, 0,
  0, 0, 0, 0,
  0, 0, 0, 0,
  0, 0, 0, 0,
};

void reshape (int w, int h) {
  GLfloat fFrustumScale = 400.0;
  GLfloat fzNear = 0.1;
  GLfloat fzFar = 1.0;
  proj_mat[0] = fFrustumScale / (GLfloat) w;
  proj_mat[5] = fFrustumScale / (GLfloat) h;
  proj_mat[10] = (fzFar+fzNear)/(fzNear-fzFar);
  proj_mat[14] = (2*fzFar*fzNear)/(fzNear-fzFar);
  proj_mat[11] = -1;
  insert_mat();
}

void set_camera_loc (const GLfloat *loc) {
  GLfloat origin[4] = {0, 0, 0, 1};
  translate(camera_mat, &origin[0], loc);
  insert_mat();
}

void set_model_loc (const GLfloat *loc) {
  GLfloat origin[4] = {0, 0, 0, 1};
  translate(model_mat, &origin[0], loc);
  insert_mat();
}

void insert_mat (void) {
  static GLfloat mat1[16] = {
    0, 0, 0, 0,
    0, 0, 0, 0,
    0, 0, 0, 0,
    0, 0, 0, 0,
  };
  static GLfloat mat2[16] = {
    0, 0, 0, 0,
    0, 0, 0, 0,
    0, 0, 0, 0,
    0, 0, 0, 0,
  };
  GLint program;
  glGetIntegerv(GL_CURRENT_PROGRAM, &program);
  GLint mat_uniform = glGetUniformLocation(program, "mat");
  matrix_mult(mat1, camera_mat, proj_mat);
  matrix_mult(mat2, model_mat, mat1);
  glUniformMatrix4fv(mat_uniform, 1, GL_FALSE, &mat2[0]);
}
