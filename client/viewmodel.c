#include "viewmodel.h"
#include "bootleg3d.c"
#include <math.h>

void
g_vm_setup (game_viewmodel_t *viewmodel, core_t *core, game_camera_t *camera,
            obj_t *model)
{
  viewmodel->core = core;
  viewmodel->camera = camera;
  viewmodel->model = model;
  viewmodel->rotation = (vec3_t){ 0, 0, 0 };
  viewmodel->scale = 1.f;
}
void
g_vm_render (game_viewmodel_t *viewmodel)
{
  b3d_reset ();
  g_c_reset (viewmodel->camera);

  b3d_scale (viewmodel->scale, viewmodel->scale, viewmodel->scale);
  b3d_rotate_x (viewmodel->rotation.x);
  b3d_rotate_y (viewmodel->rotation.y);
  b3d_rotate_z (viewmodel->rotation.z);

  float add = 0.f;
  if (viewmodel->camera->viewbob.enabled)
    {
      add = ((fabs (viewmodel->camera->viewbob.velocity->x)
              + fabs (viewmodel->camera->viewbob.velocity->y))
             * viewmodel->camera->viewbob._offset);
    }

  b3d_translate (-.4f, -.4f + add, .4f);

  for (int i = 0; i < viewmodel->core->b3d.vert_count; i += 9)
    {
      b3d_triangle (viewmodel->model->triangles[i + 0],
                    viewmodel->model->triangles[i + 1],
                    viewmodel->model->triangles[i + 2],
                    viewmodel->model->triangles[i + 3],
                    viewmodel->model->triangles[i + 4],
                    viewmodel->model->triangles[i + 5],
                    viewmodel->model->triangles[i + 6],
                    viewmodel->model->triangles[i + 7],
                    viewmodel->model->triangles[i + 8],
                    (i << 16 | i / 2 << 8 | 0), NULL);
    }
}
