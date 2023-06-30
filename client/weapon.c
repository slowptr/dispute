#include "weapon.h"

void
g_weap_setup (game_weapon_t *weap, int ammo, float damage)
{
  weap->ammo = ammo;
  weap->damage = damage;
}
void
g_weap_destroy (game_weapon_t *weap)
{
  g_ol_destroy (weap->viewmodel.model);
}
void
g_weap_render (game_weapon_t *weap)
{
  g_vm_render (&weap->viewmodel);
}
