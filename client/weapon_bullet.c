#include "weapon_bullet.h"
#include "bootleg3d.c"
#include "network.h"

void
g_w_b_from_player (game_weapon_bullet_t *bullet, game_player_t *player)
{
  bullet->start_pos = player->camera->pos;
  bullet->direction = player->camera->angles;
}
int
g_w_b_hit (game_weapon_bullet_t *bullet)
{
  for (int i = 0; i < 16; i++)
    {
      net_data_t *player = &n_clients[i];
      if (player->msg_type != 0)
        {
          continue;
        }

      // handle bullet hit
    }

  return -1;
}
