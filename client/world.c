#include "world.h"
#include "bootleg3d.c"
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

targa_file *tga;

void
g_w__render_floor (game_world_t *world)
{
  for (int z = -world->size; z < world->size; z++)
    {
      for (int x = -world->size; x < world->size; x++)
        {
          uint32_t c = (x + z) & 1 ? 0x444444 : 0x888888;
          b3d_triangle (x + .5, 0.0, z + .5, x - .5, 0.0, z - .5, x - .5, 0.0,
                        z + .5, c, tga);
          b3d_triangle (x + .5, 0.0, z + .5, x + .5, 0.0, z - .5, x - .5, 0.0,
                        z - .5, c, tga);

          b3d_triangle (x - .5, 0.0, z - .5, x + .5, 0.0, z + .5, x + .5, 0.0,
                        z - .5, c, tga);
          b3d_triangle (x - .5, 0.0, z - .5, x + .5, 0.0, z + .5, x + .5, 0.0,
                        z - .5, c, tga);
        }
    }
}
void
g_w__render_bounds (game_world_t *world)
{
  for (int i = -world->size; i < world->size; i += 2)
    {
      for (int j = 0; j < 4; ++j)
        {
          float x = i, z = i;
          switch (j)
            {
            case 0:
              x = -world->size;
              break;
            case 1:
              x = world->size;
              break;
            case 2:
              z = -world->size;
              break;
            case 3:
              z = world->size;
              break;
            }

          uint32_t c = 0x440000;

          b3d_reset ();
          b3d_scale (2.0f, 0.25f, 2.0f);
          b3d_translate (x, 0.5, z);

          b3d_triangle (-0.5, -0.5, -0.5, -0.5, 0.5, -0.5, 0.5, 0.5, -0.5, c,
                        NULL);
          b3d_triangle (-0.5, -0.5, -0.5, 0.5, 0.5, -0.5, 0.5, -0.5, -0.5, c,
                        NULL);

          b3d_triangle (0.5, -0.5, -0.5, 0.5, 0.5, -0.5, 0.5, 0.5, 0.5, c,
                        NULL);
          b3d_triangle (0.5, -0.5, -0.5, 0.5, 0.5, 0.5, 0.5, -0.5, 0.5, c,
                        NULL);

          b3d_triangle (0.5, -0.5, 0.5, 0.5, 0.5, 0.5, -0.5, 0.5, 0.5, c,
                        NULL);
          b3d_triangle (0.5, -0.5, 0.5, -0.5, 0.5, 0.5, -0.5, -0.5, 0.5, c,
                        NULL);

          b3d_triangle (-0.5, -0.5, 0.5, -0.5, 0.5, 0.5, -0.5, 0.5, -0.5, c,
                        NULL);
          b3d_triangle (-0.5, -0.5, 0.5, -0.5, 0.5, -0.5, -0.5, -0.5, -0.5, c,
                        NULL);

          b3d_triangle (-0.5, 0.5, -0.5, -0.5, 0.5, 0.5, 0.5, 0.5, 0.5, c,
                        NULL);
          b3d_triangle (-0.5, 0.5, -0.5, 0.5, 0.5, 0.5, 0.5, 0.5, -0.5, c,
                        NULL);

          b3d_triangle (0.5, -0.5, 0.5, -0.5, -0.5, 0.5, -0.5, -0.5, -0.5, c,
                        NULL);
          b3d_triangle (0.5, -0.5, 0.5, -0.5, -0.5, -0.5, 0.5, -0.5, -0.5, c,
                        NULL);
        }
    }
}

void
g_w_setup (game_world_t *world, float size, float boundary)
{
  world->size = size;
  world->boundary = boundary;

  FILE *file = fopen ("test.tga", "r");
  if (!file)
    {
      perror ("failed to load file");
      exit (1);
    }
  tga = tga_readfile (fileno (file));
}
void
g_w_render (game_world_t *world)
{
  g_w__render_floor (world);
  g_w__render_bounds (world);
}
