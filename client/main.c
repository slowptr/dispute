#include "core_wrapper.h"
#include "game.h"
#include "network.h"
#include "renderer.h"

#define BOOTLEG3D_IMPLEMENTATION
#include "bootleg3d.c"

int
main ()
{
  net_connection_t net;
  core_t core;
  game_t game;

  n_main_init ();

  n_setup (&net, "127.0.0.1", 1933);
  c_setup (&core);
  g_setup (&game, &core, &net);
  {
    g_run (&game);
  }
  g_destroy (&game);
  c_destroy (&core);
  n_destroy (&net);

  n_main_quit ();
  return 0;
}
