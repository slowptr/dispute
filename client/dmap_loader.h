#ifndef DMAP_LOADER_H
#define DMAP_LOADER_H

#include "obj_loader.h"
#include "world.h"
#include <stdio.h>

typedef struct dmap_triangle_s
{
  float xt, yt, zt;

  float x1, y1, z1;
  float x2, y2, z2;
  float x3, y3, z3;
} dmap_triangle_t;

typedef struct dmap_s
{
  game_world_t world;
  dmap_triangle_t *triangles;

  int ti;
} dmap_t;

dmap_t *dmap_setup (const char *file_name);
void dmap_render (dmap_t *dmap);
void dmap_destroy (dmap_t *dmap);

#endif /* DMAP_LOADER_H */
