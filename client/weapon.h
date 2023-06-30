#ifndef WEAPON_H
#define WEAPON_H

#include "viewmodel.h"

typedef struct game_weapon_s
{
  game_viewmodel_t viewmodel;
  int ammo;
  float damage;
} game_weapon_t;

void g_weap_setup (game_weapon_t *weap, int ammo, float damage);
void g_weap_destroy (game_weapon_t *weap);
void g_weap_render (game_weapon_t *weap);

#endif /* WEAPON_H */
