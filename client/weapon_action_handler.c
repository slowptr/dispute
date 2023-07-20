#include "weapon_action_handler.h"
#include "weapon_bullet.h"

void
g_weap_a_h_setup (game_weapon_action_handler_t *wah, game_player_t *player)
{
  wah->player = player;
  wah->cooldown = 0;
}
void
g_weap_a_h_handle (game_weapon_action_handler_t *wah, game_weapon_t *weap)
{
  if (weap == NULL)
    {
      return;
    }

  if (wah->viewpunch > 0.f)
    {
      wah->viewpunch -= weap->config.recoil_decay;
    }

  if (wah->cooldown > 0)
    {
      wah->cooldown--;
      if (wah->cooldown
          < weap->config.shot_cooldown - weap->config.shot_duration)
        {
          weap->viewmodel.rotation.x = 0.f;
        }
      else
        {
          weap->viewmodel.rotation.x = 0.15f;
        }
      if (wah->cooldown == 0)
        {
          weap->is_shooting = 0;
        }
      return;
    }

  if (wah->player->keys.shoot && wah->cooldown == 0)
    {
      weap->is_shooting = 1;
      wah->cooldown = weap->config.shot_cooldown;
      wah->viewpunch = weap->config.recoil;

      {
        game_weapon_bullet_t bullet;

        g_w_b_from_player (&bullet, wah->player);

        int t = g_w_b_hit (&bullet);
        printf ("t: %d\n", t);
      }
    }
}
