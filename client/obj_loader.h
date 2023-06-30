#ifndef OBJ_LOADER_H
#define OBJ_LOADER_H

#include "core_wrapper.h"

typedef struct obj_s
{
  float *vertices;
  float *triangles;
} obj_t;

obj_t *g_ol_setup (core_t *core, const char *file_name);
void g_ol_destroy (obj_t *obj);

#endif /* OBJ_LOADER_H */
