#include "main.h"

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <GL/glew.h>
#include <GL/gl.h>
#include <SDL.h>

#include "matrix.h"
#include "view.h"
#include "shaders.h"
#include "model.h"

#define DEFAULT_WINDOW_WIDTH 800
#define DEFAULT_WINDOW_HEIGHT 600

#define IDLE_MSECS 17

void main_loop (SDL_Surface *screen) {

  int prevTime = SDL_GetTicks();
  int currTime;
  int done = 0;
  SDL_Event event;

  while (!done) {

    /* Clear screen */
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    glClearDepth(1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    /* Move camera */
    GLfloat camera[4] = {0.4*sin((float)currTime/240.0)+0.45, 0.4*cos((float)currTime/240.0), -0.5, 1.0};
    set_camera_loc(&camera[0]);
    /* Render object */
    render();
    /* Flip up screen */
    SDL_GL_SwapBuffers();

    /* Wait until IDLE_MSECS milliseconds pass */
    currTime = SDL_GetTicks();
    int difference = currTime - prevTime;
    if (difference <= IDLE_MSECS) {
      SDL_Delay(IDLE_MSECS - difference);
      currTime = SDL_GetTicks();
      difference = currTime - prevTime;
    }
    prevTime = currTime;

    /* Check for events */
    while (SDL_PollEvent(&event)) {
      switch (event.type) {
      case SDL_KEYDOWN:
        if (event.key.keysym.sym == SDLK_q) {
          done = 1;
        }
        break;
      case SDL_VIDEORESIZE:
        screen = SDL_SetVideoMode(event.resize.w, 
                                  event.resize.h, 0,
                                  SDL_OPENGL | SDL_RESIZABLE);
        reshape(screen->w, screen->h);
        break;
      case SDL_QUIT:
        done = 1;
        break;
      }
    }
    Uint8 *keys = SDL_GetKeyState(NULL);
    if (keys[SDLK_ESCAPE]) {
      done = 1;
    }

  }
}

int main (int argc, char **argv) {
  if (argc < 4) {
    fprintf(stderr, "Pass a vertex shader, then a fragment shader, then a model file.\n");
    return -1;
  }

  if (SDL_Init(SDL_INIT_VIDEO)) {
    fprintf(stderr, "SDL init failed.\n");
    return -2;
  }

  SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 5);
  SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 5);
  SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 5);
  SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 16);
  SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

  SDL_Surface* screen = SDL_SetVideoMode(DEFAULT_WINDOW_WIDTH,
                                         DEFAULT_WINDOW_HEIGHT,
                                         0,
                                         SDL_OPENGL);
  if (!screen) {
    fprintf(stderr, "Failed to set video mode.\n");
    SDL_Quit();
    return -3;
  }

  SDL_WM_SetCaption("Hyper3", "GSGT");

  if (GLEW_OK != glewInit()) {
    fprintf(stderr, "GLEW init failed.\n");
    return -4;
  }

  set_up_program(argv[1], argv[2]);
  model_read(argv[3]);
  reshape(DEFAULT_WINDOW_WIDTH, DEFAULT_WINDOW_HEIGHT);
  GLfloat camera[4] = {-0.4, -0.4, -0.4, 1.0};
  set_camera_loc(&camera[0]);
  glEnable(GL_DEPTH_TEST);
  glDepthMask(GL_TRUE);
  glDepthFunc(GL_LEQUAL);
  glDepthRange(0.0f, 1.0f);
  glClearDepth(1.0f);
  main_loop(screen);

  return 0;             
}

