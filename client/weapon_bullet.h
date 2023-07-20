#ifndef WEAPON_BULLET_H
#define WEAPON_BULLET_H

#include "player.h"
#include "utils.h"
#include <stdint.h>

typedef struct game_weapon_bullet_s
{
  vec3_t start_pos;
  viewangles_t direction;
} game_weapon_bullet_t;

void g_w_b_from_player (game_weapon_bullet_t *bullet, game_player_t *player);
int g_w_b_hit (game_weapon_bullet_t *bullet);

#endif /* WEAPON_BULLET_H */
