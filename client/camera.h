#ifndef CAMERA_H
#define CAMERA_H

#include "utils.h"
#include <stdint.h>

typedef struct game_camera_viewbobbing_s
{
  uint8_t enabled;
  float frequency, amplitude;

  vec2_t *velocity;

  float _timer, _offset;
  uint32_t _prev_frametime;
} game_camera_viewbobbing_t;
typedef struct game_camera_s
{
  vec3_t pos;
  viewangles_t angles;
  game_camera_viewbobbing_t viewbob;
} game_camera_t;

void g_c_setup (game_camera_t *camera, vec3_t pos, viewangles_t angles,
                game_camera_viewbobbing_t viewbob);
void g_c_set (game_camera_t *camera, float yaw_add, float pitch_add);
void g_c_reset (game_camera_t *camera);

#endif /* CAMERA_H */
