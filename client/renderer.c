#include "renderer.h"
#include "bootleg3d.c"
#include <SDL2/SDL.h>

void
r_render_b3d (core_t *core)
{
  SDL_RenderClear (core->sdl.renderer);
  SDL_UpdateTexture (core->sdl.texture, NULL, core->b3d.pixels,
                     WND_WIDTH * sizeof (uint32_t));
  SDL_RenderCopy (core->sdl.renderer, core->sdl.texture, NULL, NULL);
  SDL_RenderPresent (core->sdl.renderer);
}
void
r_reset_depth_buffer (core_t *core)
{
  memset (b3d_depth, 0x7f, b3d_width * b3d_height * sizeof (b3d_depth[0]));
}
