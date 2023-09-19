#include "dmap_loader.h"
#include "bootleg3d.c"

dmap_t *
dmap_setup (const char *file_name)
{
  dmap_t *dmap = malloc (sizeof (dmap_t));
  dmap->triangles = NULL;

  FILE *file = fopen (file_name, "r");
  if (!file)
    {
      perror ("failed to load file");
      exit (1);
    }

  char line[128];
  dmap->ti = 0;
  while (fgets (line, sizeof (line), file) != NULL)
    {
      if (line[0] == 's')
        {
          sscanf (line, "s %f %f", &dmap->world.size, &dmap->world.boundary);
        }
      if (line[0] == 't')
        {
          dmap->triangles = realloc (
              dmap->triangles, (dmap->ti + 1) * sizeof (dmap_triangle_t));

          dmap->triangles[dmap->ti].xs = 1.f;
          dmap->triangles[dmap->ti].ys = 1.f;
          dmap->triangles[dmap->ti].zs = 1.f;

          if (line[1] == 's')
            {
              sscanf (
                  line, "ts %f %f %f: %f %f %f: %f %f %f, %f %f %f, %f %f %f",
                  &dmap->triangles[dmap->ti].xt, &dmap->triangles[dmap->ti].yt,
                  &dmap->triangles[dmap->ti].zt, &dmap->triangles[dmap->ti].xs,
                  &dmap->triangles[dmap->ti].ys, &dmap->triangles[dmap->ti].zs,
                  &dmap->triangles[dmap->ti].x1, &dmap->triangles[dmap->ti].y1,
                  &dmap->triangles[dmap->ti].z1, &dmap->triangles[dmap->ti].x2,
                  &dmap->triangles[dmap->ti].y2, &dmap->triangles[dmap->ti].z2,
                  &dmap->triangles[dmap->ti].x3, &dmap->triangles[dmap->ti].y3,
                  &dmap->triangles[dmap->ti].z3);
            }
          else
            {
              // x, y: height, z... americans are fucked up
              sscanf (
                  line, "t %f %f %f: %f %f %f, %f %f %f, %f %f %f",
                  &dmap->triangles[dmap->ti].xt, &dmap->triangles[dmap->ti].yt,
                  &dmap->triangles[dmap->ti].zt, &dmap->triangles[dmap->ti].x1,
                  &dmap->triangles[dmap->ti].y1, &dmap->triangles[dmap->ti].z1,
                  &dmap->triangles[dmap->ti].x2, &dmap->triangles[dmap->ti].y2,
                  &dmap->triangles[dmap->ti].z2, &dmap->triangles[dmap->ti].x3,
                  &dmap->triangles[dmap->ti].y3,
                  &dmap->triangles[dmap->ti].z3);
            }

          dmap->ti++;
        }
    }
  return dmap;
}

void
dmap_render (dmap_t *dmap)
{
  for (int i = 0; i < dmap->ti; i++)
    {
      uint32_t c = 0xFFFFFF;

      b3d_reset ();
      b3d_scale (dmap->triangles[i].xs, dmap->triangles[i].ys,
                 dmap->triangles[i].zs);

      b3d_translate (dmap->triangles[i].xt, dmap->triangles[i].yt,
                     dmap->triangles[i].zt);

      b3d_triangle (dmap->triangles[i].x1, dmap->triangles[i].y1,
                    dmap->triangles[i].z1, dmap->triangles[i].x2,
                    dmap->triangles[i].y2, dmap->triangles[i].z2,
                    dmap->triangles[i].x3, dmap->triangles[i].y3,
                    dmap->triangles[i].z3, c, NULL);
    }
}
void
dmap_destroy (dmap_t *dmap)
{
  free (dmap->triangles);
  free (dmap);
}
