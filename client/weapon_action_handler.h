#ifndef WEAPON_ACTION_HANDLER_H
#define WEAPON_ACTION_HANDLER_H

#include "player.h"
#include "weapon.h"
typedef struct game_weapon_action_handler_s
{
  game_player_t *player;

  uint32_t cooldown;
  float viewpunch;
} game_weapon_action_handler_t;

void g_weap_a_h_setup (game_weapon_action_handler_t *wah,
                       game_player_t *player);
void g_weap_a_h_handle (game_weapon_action_handler_t *wah,
                        game_weapon_t *weap);

#endif /* WEAPON_ACTION_HANDLER_H */
