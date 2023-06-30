#ifndef NETWORK_H
#define NETWORK_H

#include "utils.h"
#include <enet/enet.h>

typedef struct net_data_s
{
  uint8_t msg_type;

  vec3_t position;
  viewangles_t angles;
  float health;

  // bullet
  // (velocity later for prediction)
} net_data_t;

typedef struct net_connection_s
{
  ENetHost *host;
  ENetPeer *peer;

  ENetAddress con_addr;
  uint16_t con_port;
} net_connection_t;

void n_main_init ();

void n_setup (net_connection_t *connection, const char *hostname,
              uint16_t port);

void n_send (net_connection_t *connection, net_data_t *msg);

void n_destroy (net_connection_t *connection);

void n_main_quit ();

#endif /* NETWORK_H */
