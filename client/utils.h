#ifndef UTILS_H
#define UTILS_H

#define DEG_TO_RAD(x) (x * M_PI / 180.f)

typedef struct vec3_s
{
  float x, y, z;
} vec3_t;
typedef struct vec2_s
{
  float x, y;
} vec2_t;
typedef struct viewangles_s
{
  float pitch, yaw;
} viewangles_t;

#endif /* UTILS_H */
