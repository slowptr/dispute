#include "weapon.h"

void
g_weap_setup (game_weapon_t *weap)
{
  /*
   * rest has to be set
   */
  weap->is_shooting = 0;
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

void
g_weap_create_pistol (game_weapon_t *weap, core_t *core, game_camera_t *camera)
{
  g_weap_setup (weap);
  g_vm_setup (&weap->viewmodel, core, camera,
              g_ol_setup (core, "assets/pistol.obj"));
  weap->viewmodel.scale = 0.05f;
  weap->viewmodel.rotation.y = DEG_TO_RAD (89.f) * 2;
  {
    weap->config.shot_cooldown = 50;
    weap->config.shot_duration = 5;
    weap->config.recoil = 0.06f;
    weap->config.recoil_decay = 0.02f;
  }
}
