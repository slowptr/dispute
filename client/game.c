#include "game.h"
#include "bootleg3d.c"
#include "dmap_loader.h"
#include "network.h"
#include "player.h"
#include "renderer.h"
#include "ui.h"
#include "weapon.h"
#include "weapon_action_handler.h"

game_player_t localplayer;
game_weapon_t w_pistol;
game_weapon_action_handler_t w_a_handler;
obj_t *dummy_model;
dmap_t *dmap;

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
g_setup (game_t *game, core_t *core, net_connection_t *net)
{
  game->core = core;
  game->net = net;
  p_setup (&localplayer, &game->world, &game->camera);

  dmap = dmap_setup ("test.dmap");
  g_w_setup (&game->world, dmap->world.size, dmap->world.boundary);

  dummy_model = g_ol_setup (game->core, "assets/player.obj");

  g_weap_create_pistol (&w_pistol, game->core, localplayer.camera);
  g_weap_a_h_setup (&w_a_handler, &localplayer);

  { // connection check
    printf ("Trying to find server to connect to.\n");
    for (uint16_t i = 0; i < 5; i++)
      {
        if (!n_connection.has_connection)
          {
            usleep (1);
          }
        else
          {
            printf ("Connected to server.\n");
            break;
          }
      }

    if (!n_connection.has_connection)
      {
        perror ("Failed to find server to connect to");
        // exit (1);
      }
  }

  n_calc_client_id ();
}
void
g_destroy (game_t *game)
{
  p_destroy (&localplayer);
  g_weap_destroy (&w_pistol);
  dmap_destroy (dmap);
}
void
g_run (game_t *game)
{
  while (1)
    {
      if (c_frame_limiter (game->core, 60.f))
        continue;

      g_weap_a_h_handle (&w_a_handler, localplayer.current_weapon);
      g_c_set (localplayer.camera, 0, -w_a_handler.viewpunch); // handle recoil

      g__handle_events ();
      p_update (&localplayer);
      p_send_net_update (&localplayer);

      b3d_clear ();
      b3d_reset ();

      g_w_render (&game->world);
      dmap_render (dmap);

      { // dmap debug
        const Uint8 *keys = SDL_GetKeyboardState (NULL);
        if (keys[SDL_SCANCODE_P])
          {
            dmap_destroy (dmap);
            dmap_setup ("test.dmap");
            usleep (200 * 1000); // 200ms
          }
      }

      for (int i = 0; i < 16; i++)
        {
          if (i == n_client_id)
            {
              continue;
            }
          net_data_t *client = &n_clients[i];
          if (client->msg_type != -1)
            {
              p_render_dummy (game->core, dummy_model, client->position);
            }
        }

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
