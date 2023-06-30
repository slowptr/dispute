#include "core_wrapper.h"
#include "game.h"
#include "renderer.h"

#define BOOTLEG3D_IMPLEMENTATION
#include "bootleg3d.c"

int
main ()
{
  core_t core;
  game_t game;

  c_setup (&core);
  g_setup (&game, &core);
  {
    g_run (&game);
  }
  g_destroy (&game);
  c_destroy (&core);
  return 0;
}
