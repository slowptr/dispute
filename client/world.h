#ifndef WORLD_H
#define WORLD_H

typedef struct game_world_s
{
  float size;
  float boundary;
} game_world_t;

void g_w_setup (game_world_t *world, float size, float boundary);
void g_w_render (game_world_t *world);

#endif /* WORLD_H */
