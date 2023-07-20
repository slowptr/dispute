#include "core_wrapper.h"
#include "game.h"
#include "network.h"

int
main (int argc, char **argv)
{
  net_connection_t net;
  core_t core;
  game_t game;

  n_setup ("127.0.0.1", 1933);
  c_setup (&core);
  g_setup (&game, &core, &net);
  {
    g_run (&game);
  }
  g_destroy (&game);
  c_destroy (&core);
  n_destroy ();
  return 0;
}
