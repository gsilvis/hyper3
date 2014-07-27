#include "matrix.h"

#include <stdio.h>
#include <math.h>
#include <GL/glew.h>

void vector_zero (GLfloat *result) {
  for (int i = 0; i < 4; i++) {
    result[i] = 0;
  }
}

void vector_add (GLfloat *result,
                 const GLfloat *v,
                 const GLfloat *w) {
  for (int i = 0; i < 4; i++) {
    result[i] = v[i] + w[i];
  }
}

void vector_scalar_mult (GLfloat *result,
                         GLfloat scalar) {
  for (int i = 0; i < 4; i++) {
    result[i] *= scalar;
  }
}

void vector_copy (GLfloat *to,
                  const GLfloat *from) {
  for (int i = 0; i < 4; i++) {
    to[i] = from[i];
  }
}


void matrix_zero (GLfloat *result) {
  for (int i = 0; i < 16; i++) {
    result[i] = 0;
  }
}

void matrix_id (GLfloat *result) {
  matrix_zero(result);
  result[0] = 1;
  result[5] = 1;
  result[10] = 1;
  result[15] = 1;
}

void matrix_hyp_id (GLfloat *result) {
  matrix_zero(result);
  result[0] = 1;
  result[5] = 1;
  result[10] = 1;
  result[15] = -1;
}

void matrix_copy (GLfloat *to,
                  const GLfloat *from) {
  for (int i = 0; i < 16; i++) {
    to[i] = from[i];
  }
}

void matrix_add (GLfloat *result,
                 const GLfloat *mat1,
                 const GLfloat *mat2) {
  for (int i = 0; i < 16; i++) {
    result[i] = mat1[i] + mat2[i];
  }
}

void matrix_mult (GLfloat *result,
                  const GLfloat *matl,
                  const GLfloat *matr) {
  matrix_zero(result);
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      for (int k = 0; k < 4; k++) {
        result[4*i + k] += matl[4*i + j] * matr[4*j + k];
      }
    }
  }
}

void matrix_scalar_mult (GLfloat *result,
                         GLfloat scalar) {
  for (int i = 0; i < 16; i++) {
    result[i] *= scalar;
  }
}

GLfloat hyp_inner_prod (const GLfloat *vec1,
                        const GLfloat *vec2) {
  GLfloat returnee = -vec1[3] * vec2[3];
  for (int i = 0; i < 3; i++) {
    returnee += vec1[i] * vec2[i];
  }
  return returnee;
}

void outer_prod (GLfloat *result,
                 const GLfloat *vecl,
                 const GLfloat *vecr) {
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      result[4*i + j] = vecl[i] * vecr[j];
    }
  }
}

void point_reflect (GLfloat *result,
                    const GLfloat *point) {
  GLfloat a[16];
  outer_prod(a, point, point);
  GLfloat b[16];
  matrix_hyp_id(b);
  GLfloat c[16];
  matrix_mult(c, a, b);
  GLfloat scalar = -2.0 / hyp_inner_prod(point, point);
  matrix_scalar_mult(c, scalar);
  GLfloat id[16];
  matrix_id(id);
  matrix_add(result, id, c);
}


void hyp_midpoint (GLfloat *result,
                   const GLfloat *p,
                   const GLfloat *q) {
  GLfloat weightp = sqrt(hyp_inner_prod(q, q) * hyp_inner_prod(p, q));
  GLfloat weightq = sqrt(hyp_inner_prod(p, p) * hyp_inner_prod(p, q));
  GLfloat p_scaled[4];
  GLfloat q_scaled[4];
  vector_copy(p_scaled, p);
  vector_copy(q_scaled, q);
  vector_scalar_mult(p_scaled, weightp);
  vector_scalar_mult(q_scaled, weightq);
  vector_add(result, p_scaled, q_scaled);
}

void translate (GLfloat *result,
                const GLfloat *from,
                const GLfloat *to) {
  GLfloat midpoint[4];
  hyp_midpoint(midpoint, from, to);
  GLfloat trans1[16];
  point_reflect(trans1, midpoint);
  GLfloat trans2[16];
  point_reflect(trans2, from);
  matrix_mult(result, trans1, trans2);
}
