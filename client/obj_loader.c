#include "obj_loader.h"
#include <stdio.h>

obj_t *
g_ol_setup (core_t *core, const char *file_name)
{
  obj_t *obj = malloc (sizeof (obj_t));
  obj->vertices = NULL;
  obj->triangles = NULL;

  FILE *obj_file = fopen (file_name, "r");
  if (!obj_file)
    {
      perror ("failed to load file");
      exit (1);
    }

  char line[128];
  int vi = 0, ti = 0;
  float x, y, z;
  while (fgets (line, 128, obj_file))
    {
      if (line[0] == 'v' && sscanf (line, " v %f %f %f ", &x, &y, &z))
        {
          obj->vertices
              = realloc (obj->vertices, (vi + 3) * sizeof (obj->vertices[0]));
          obj->vertices[vi++] = x;
          obj->vertices[vi++] = y;
          obj->vertices[vi++] = z;
        }
    }
  rewind (obj_file);
  int a, b, c;
  while (fgets (line, 128, obj_file))
    {
      if (line[0] == 'f')
        {
          // DOES: erase texture and normal info
          for (int i = 0; i < 128; ++i)
            {
              if (line[i] == '/')
                {
                  while (line[i] != ' ' && line[i] != '\n' && line[i] != '\0')
                    {
                      line[i++] = ' ';
                    }
                }
            }
          if (sscanf (line, " f %d %d %d ", &a, &b, &c))
            {
              a--, b--, c--;
              obj->triangles = realloc (obj->triangles,
                                        (ti + 9) * sizeof (obj->triangles[0]));
              obj->triangles[ti++] = obj->vertices[(a * 3) + 0];
              obj->triangles[ti++] = obj->vertices[(a * 3) + 1];
              obj->triangles[ti++] = obj->vertices[(a * 3) + 2];
              obj->triangles[ti++] = obj->vertices[(b * 3) + 0];
              obj->triangles[ti++] = obj->vertices[(b * 3) + 1];
              obj->triangles[ti++] = obj->vertices[(b * 3) + 2];
              obj->triangles[ti++] = obj->vertices[(c * 3) + 0];
              obj->triangles[ti++] = obj->vertices[(c * 3) + 1];
              obj->triangles[ti++] = obj->vertices[(c * 3) + 2];
            }
        }
    }
  free (obj->vertices);
  core->b3d.vert_count = ti;

  printf ("loaded %d triangles from file '%s'\n", core->b3d.vert_count / 9,
          file_name);

  return obj;
}
void
g_ol_destroy (obj_t *obj)
{
  free (obj->vertices);
  free (obj->triangles);
  free (obj);
}
