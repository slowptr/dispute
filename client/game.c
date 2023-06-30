#include "game.h"
#include "bootleg3d.c"
#include "player.h"
#include "renderer.h"
#include "ui.h"
#include "weapon.h"

game_player_t localplayer;
game_weapon_t w_pistol;
obj_t *dummy_model;

void
g__handle_events ()
{
  SDL_Event event;
  while (SDL_PollEvent (&event))
    {
      if (event.type == SDL_QUIT)
        exit (0);

      p_handle_mouse_events (&localplayer, &event);

      if (event.type == SDL_KEYDOWN)
        {
          switch (event.key.keysym.sym)
            {
            case SDLK_1:
              localplayer.current_weapon = NULL;
              break;
            case SDLK_2:
              localplayer.current_weapon = &w_pistol;
              break;
            default:
              break;
            }
        }
    }
}

void
g_setup (game_t *game, core_t *core)
{
  game->core = core;
  p_setup (&localplayer, &game->world, &game->camera);
  g_w_setup (&game->world, 20.f, 1.25f);

  dummy_model = g_ol_setup (game->core, "assets/player.obj");

  { // pistol weapon
    g_weap_setup (&w_pistol, 12, 100);
    g_vm_setup (&w_pistol.viewmodel, game->core, localplayer.camera,
                g_ol_setup (game->core, "assets/pistol.obj"));
    w_pistol.viewmodel.scale = 0.05f;
    w_pistol.viewmodel.rotation.y = PLAYER_PITCH_CAP * 2;
  }
}
void
g_destroy (game_t *game)
{
  p_destroy (&localplayer);
  g_weap_destroy (&w_pistol);
}
void
g_run (game_t *game)
{
  while (1)
    {
      if (c_frame_limiter (game->core, 60.f))
        continue;

      g__handle_events ();
      p_update (&localplayer);

      b3d_clear ();
      b3d_reset ();

      g_w_render (&game->world);

      p_render_dummy (game->core, dummy_model, (vec3_t){ 0, 1.f, 0 });

      r_reset_depth_buffer (game->core);
      {
        if (localplayer.current_weapon != NULL)
          {
            g_weap_render (localplayer.current_weapon);
          }
        g_ui_render ();
      }
      r_render_b3d (game->core);
    }
}
