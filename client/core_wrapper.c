#include "core_wrapper.h"
#include "bootleg3d.c"

void
c__setup_b3d (core_t *core)
{
  core->b3d.vert_count = 0;
  core->b3d.pixels
      = malloc (WND_WIDTH * WND_HEIGHT * sizeof (core->b3d.pixels[0]));
  core->b3d.depth
      = malloc (WND_WIDTH * WND_HEIGHT * sizeof (core->b3d.depth[0]));
  b3d_init (core->b3d.pixels, core->b3d.depth, WND_WIDTH, WND_HEIGHT,
            DEFAULT_FOV);
}
void
c__setup_sdl (core_t *core)
{
  core->delta = 0;
  if (SDL_Init (SDL_INIT_VIDEO) < 0)
    {
      perror ("SDL_Init");
      exit (1);
    }

  core->sdl.window
      = SDL_CreateWindow ("", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                          WND_WIDTH, WND_HEIGHT, 0);
  core->sdl.renderer = SDL_CreateRenderer (core->sdl.window, -1,
                                           0 /*SDL_RENDERER_PRESENTVSYNC*/);

  core->sdl.texture
      = SDL_CreateTexture (core->sdl.renderer, SDL_PIXELFORMAT_ARGB8888,
                           SDL_TEXTUREACCESS_STREAMING, WND_WIDTH, WND_HEIGHT);

  if (!core->sdl.window)
    {
      perror ("SDL_CreateWindow");
      exit (1);
    }

  if (!core->sdl.renderer)
    {
      perror ("SDL_CreateRenderer");
      exit (1);
    }
}
void
c__destroy_b3d (core_t *core)
{
  free (core->b3d.pixels);
  free (core->b3d.depth);
}
void
c__destroy_sdl (core_t *core)
{
  SDL_DestroyTexture (core->sdl.texture);
  SDL_DestroyRenderer (core->sdl.renderer);
  SDL_DestroyWindow (core->sdl.window);
}

void
c_setup (core_t *core)
{
  c__setup_b3d (core);
  c__setup_sdl (core);

  SDL_SetRelativeMouseMode (SDL_TRUE);
}
void
c_destroy (core_t *core)
{
  c__destroy_b3d (core);
  c__destroy_sdl (core);
}

uint8_t
c_frame_limiter (core_t *core, float max_fps)
{
  static float a, b = 0;
  a = SDL_GetTicks ();
  core->delta = a - b;
  if (core->delta < (1000.f / max_fps))
    {
      SDL_Delay (1);
      return 1;
    }
  b = a;
  return 0;
}
