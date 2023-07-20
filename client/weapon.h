#ifndef WEAPON_H
#define WEAPON_H

#include "viewmodel.h"

typedef struct game_weapon_config_s
{
  float damage;
  uint32_t shot_cooldown;
  uint32_t shot_duration;
  float recoil;
  float recoil_decay;
} game_weapon_config_t;
typedef struct game_weapon_s
{
  game_viewmodel_t viewmodel;
  game_weapon_config_t config;
  int ammo;

  uint8_t is_shooting;
} game_weapon_t;

void g_weap_setup (game_weapon_t *weap);
void g_weap_destroy (game_weapon_t *weap);
void g_weap_render (game_weapon_t *weap);

void g_weap_create_pistol (game_weapon_t *weap, core_t *core,
                           game_camera_t *camera);

#endif /* WEAPON_H */
