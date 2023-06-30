#ifndef NETWORK_H
#define NETWORK_H

#include "utils.h"

typedef struct net_data_s
{
  vec3_t position;
  viewangles_t angles;
  float health;

  // bullet
  // (velocity later for prediction)
} net_data_t;

#endif /* NETWORK_H */
