#include "camera.h"
#include "bootleg3d.c"

#include <SDL2/SDL.h>
#include <math.h>

void
g_c__calculate_viewbobbing (game_camera_t *camera)
{
  uint32_t frametime = SDL_GetTicks ();
  float delta = (frametime - camera->viewbob._prev_frametime) / 1000.f;

  float bob_speed = camera->viewbob.frequency * 2.f * M_PI;
  float bob_amount
      = camera->viewbob.amplitude * sinf (camera->viewbob._timer * bob_speed);

  camera->viewbob._offset = bob_amount;
  camera->viewbob._timer += delta;
  camera->viewbob._prev_frametime = frametime;
}

void
g_c_setup (game_camera_t *camera, vec3_t pos, viewangles_t angles,
           game_camera_viewbobbing_t viewbob)
{
  camera->pos = pos;
  camera->angles = angles;
  camera->viewbob = viewbob;
  {
    camera->viewbob._timer = 0.f;
    camera->viewbob._offset = 0.f;
    camera->viewbob._prev_frametime = 0;
  }
}
void
g_c_set (game_camera_t *camera)
{
  float add = 0;
  if (camera->viewbob.enabled)
    {
      g_c__calculate_viewbobbing (camera);
      add = (fabs (camera->viewbob.velocity->x)
             + fabs (camera->viewbob.velocity->y))
            * 10.f * camera->viewbob._offset;
    }
  b3d_set_camera (camera->pos.x, camera->pos.z + add, camera->pos.y,
                  camera->angles.yaw, camera->angles.pitch, 0);
}
void
g_c_reset (game_camera_t *camera)
{
  b3d_set_camera (0, 0, 0, 0, 0, 0);
}
