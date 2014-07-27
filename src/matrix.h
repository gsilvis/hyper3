#ifndef __HYPER3_MATRIX_H
#define __HYPER3_MATRIX_H

#include <math.h>
#include <GL/glew.h>

void vector_zero (GLfloat *result);
void vector_add (GLfloat *result,
                 const GLfloat *v,
                 const GLfloat *w);
void vector_scalar_mult (GLfloat *result,
                         GLfloat scalar);
void vector_copy (GLfloat *to,
                  const GLfloat *from);
void matrix_zero (GLfloat *result);
void matrix_id (GLfloat *result);
void matrix_hyp_id (GLfloat *result);
void matrix_copy (GLfloat *to,
                  const GLfloat *from);
void matrix_add (GLfloat *result,
                 const GLfloat *mat1,
                 const GLfloat *mat2);
void matrix_mult (GLfloat *result,
                  const GLfloat *matl,
                  const GLfloat *matr);
void matrix_scalar_mult (GLfloat *result,
                         GLfloat scalar);
GLfloat hyp_inner_prod (const GLfloat *vec1,
                        const GLfloat *vec2);
void outer_prod (GLfloat *result,
                 const GLfloat *vecl,
                 const GLfloat *vecr);
void point_reflect (GLfloat *result,
                    const GLfloat *point);
void hyp_midpoint (GLfloat *result,
                   const GLfloat *p,
                   const GLfloat *q);
void translate (GLfloat *result,
                const GLfloat *from,
                const GLfloat *to);

#endif /* __HYPER3_MATRIX_H */
