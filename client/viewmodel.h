#ifndef VIEWMODEL_H
#define VIEWMODEL_H

#include "camera.h"
#include "obj_loader.h"

typedef struct game_viewmodel_s
{
  core_t *core;
  game_camera_t *camera;
  obj_t *model;
  vec3_t rotation;
  float scale;
} game_viewmodel_t;

void g_vm_setup (game_viewmodel_t *viewmodel, core_t *core,
                 game_camera_t *camera, obj_t *model);
void g_vm_render (game_viewmodel_t *viewmodel);

#endif /* VIEWMODEL_H */
