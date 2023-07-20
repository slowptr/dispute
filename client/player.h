#ifndef PLAYER_H
#define PLAYER_H

#include "camera.h"
#include "core_wrapper.h"
#include "obj_loader.h"
#include "utils.h"
#include "weapon.h"
#include "world.h"
#include <SDL2/SDL.h>

#define PLAYER_PITCH_CAP DEG_TO_RAD (89.f)
#define PLAYER_ACCEL 0.02f

typedef struct game_player_keys_s
{
  uint8_t up, down, left, right, crouch, shoot;
} game_player_keys_t;

typedef struct game_player_s
{
  game_world_t *world;
  game_camera_t *camera;
  game_weapon_t *current_weapon;
  vec2_t velocity;

  game_player_keys_t keys;

  float mouse_sensitivity;

  float health;
} game_player_t;

void p_setup (game_player_t *player, game_world_t *world,
              game_camera_t *camera);
void p_destroy (game_player_t *player);

void p_handle_mouse_events (game_player_t *player, SDL_Event *e);
void p_handle_input (game_player_t *player);
void p_update (game_player_t *player);
void p_send_net_update (game_player_t *player);

void p_render_dummy (core_t *core, obj_t *model, vec3_t position);

#endif /* PLAYER_H */
