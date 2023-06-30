#include "player.h"
#include "bootleg3d.c"

void
p__movement_test (game_player_t *player)
{
  float size = player->world->size;
  float boundary = player->world->boundary;

  if (player->camera->pos.x < -(size - boundary))
    player->camera->pos.x = -size + boundary;
  if (player->camera->pos.x > (size - boundary))
    player->camera->pos.x = size - boundary;
  if (player->camera->pos.y < -(size - boundary))
    player->camera->pos.y = -size + boundary;
  if (player->camera->pos.y > (size - boundary))
    player->camera->pos.y = size - boundary;
}
void
p__handle_movement (game_player_t *player)
{
  if (player->keys.up)
    player->velocity.x += PLAYER_ACCEL;
  if (player->keys.down)
    player->velocity.x += -PLAYER_ACCEL;
  if (player->keys.left)
    player->velocity.y += PLAYER_ACCEL;
  if (player->keys.right)
    player->velocity.y += -PLAYER_ACCEL;
  player->camera->pos.z
      += ((player->keys.crouch ? 0.5f : 1.0f) - player->camera->pos.z) * 0.1f;

  player->camera->pos.x -= cosf (player->camera->angles.yaw - PLAYER_PITCH_CAP)
                           * player->velocity.x;
  player->camera->pos.y -= sinf (player->camera->angles.yaw - PLAYER_PITCH_CAP)
                           * player->velocity.x;
  player->camera->pos.x
      -= cosf (player->camera->angles.yaw) * player->velocity.y;
  player->camera->pos.y
      -= sinf (player->camera->angles.yaw) * player->velocity.y;

  if (player->keys.crouch)
    {
      player->velocity.x *= 0.7f;
      player->velocity.y *= 0.7f;
    }
  else
    {
      player->velocity.x *= 0.9f;
      player->velocity.y *= 0.9f;
    }

  p__movement_test (player);
}
void
p__handle_input (game_player_t *player)
{
  const Uint8 *keys = SDL_GetKeyboardState (NULL);

  player->keys.up = keys[SDL_SCANCODE_UP];
  player->keys.down = keys[SDL_SCANCODE_DOWN];
  player->keys.left = keys[SDL_SCANCODE_LEFT];
  player->keys.right = keys[SDL_SCANCODE_RIGHT];
  player->keys.crouch = keys[SDL_SCANCODE_LSHIFT];

  if (keys[SDL_SCANCODE_ESCAPE])
    exit (0);
}

void
p_setup (game_player_t *player, game_world_t *world, game_camera_t *camera)
{
  player->world = world;
  player->camera = camera;
  player->current_weapon = NULL;

  player->velocity = (vec2_t){ 0.f, 0.f };

  player->health = 100.f;

  {
    vec3_t default_pos = (vec3_t){ -1.f, 1.f, -3.f };
    viewangles_t default_angles = (viewangles_t){ 0.f, 1.f };
    game_camera_viewbobbing_t default_bobbing;
    default_bobbing.enabled = 1;
    default_bobbing.frequency = 1.5f;
    default_bobbing.amplitude = 0.075f;
    default_bobbing.velocity = &player->velocity;

    g_c_setup (player->camera, default_pos, default_angles, default_bobbing);
  }

  player->keys = (game_player_keys_t){ 0, 0, 0, 0, 0 };
  player->mouse_sensitivity = 0.001f;

  player->is_shooting = 0;
}
void
p_destroy (game_player_t *player)
{
}

void
p_handle_mouse_events (game_player_t *player, SDL_Event *e)
{
  if (e->type == SDL_MOUSEMOTION)
    {
      player->camera->angles.pitch
          += e->motion.yrel * player->mouse_sensitivity;
      player->camera->angles.yaw -= e->motion.xrel * player->mouse_sensitivity;
      if (player->camera->angles.pitch < -PLAYER_PITCH_CAP)
        player->camera->angles.pitch = -PLAYER_PITCH_CAP;
      else if (player->camera->angles.pitch > PLAYER_PITCH_CAP)
        player->camera->angles.pitch = PLAYER_PITCH_CAP;
    }
  else if (e->type == SDL_MOUSEBUTTONDOWN || e->type == SDL_MOUSEBUTTONUP)
    {
      if (e->button.button == SDL_BUTTON_LEFT)
        {
          player->keys.shoot = e->button.state;
        }
    }
}
void
p_update (game_player_t *player)
{
  p__handle_input (player);
  p__handle_movement (player);

  g_c_set (player->camera);
}

void
p_render_dummy (core_t *core, obj_t *model, vec3_t position)
{
  b3d_reset ();
  b3d_scale (0.1f, 0.1f, 0.1f);
  b3d_translate (position.x, position.z - 1.0f, position.y);

  for (int i = 0; i < core->b3d.vert_count; i += 9)
    {
      b3d_triangle (model->triangles[i + 0], model->triangles[i + 1],
                    model->triangles[i + 2], model->triangles[i + 3],
                    model->triangles[i + 4], model->triangles[i + 5],
                    model->triangles[i + 6], model->triangles[i + 7],
                    model->triangles[i + 8], (i << 16 | 0 << 8 | i));
    }
}
