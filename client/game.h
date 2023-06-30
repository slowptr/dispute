#ifndef GAME_H
#define GAME_H

#include "camera.h"
#include "core_wrapper.h"
#include "network.h"
#include "world.h"

typedef struct game_s
{
  core_t *core;
  net_connection_t *net;
  game_world_t world;
  game_camera_t camera;
} game_t;

void g_setup (game_t *game, core_t *core, net_connection_t *net);
void g_destroy (game_t *game);
void g_run (game_t *game);

#endif /* GAME_H */
