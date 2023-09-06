#ifndef CORE_WRAPPER_H
#define CORE_WRAPPER_H

#include <SDL2/SDL.h>

#define WND_WIDTH 320
#define WND_HEIGHT 240
#define DEFAULT_FOV 90.f

typedef struct core_s
{
  struct
  {
    uint32_t *pixels;
    float *depth;
    int vert_count;
  } b3d;

  struct
  {
    SDL_Window *window;
    SDL_Renderer *renderer;
    SDL_Texture *texture;
  } sdl;

  float delta;
} core_t;

void c_setup (core_t *core);
void c_destroy (core_t *core);

uint8_t c_frame_limiter (core_t *core, float max_fps);

#endif /* CORE_WRAPPER_H */
