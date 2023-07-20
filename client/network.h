#ifndef NETWORK_H
#define NETWORK_H

#include "utils.h"
#include <enet/enet.h>
#include <stdint.h>

typedef struct net_data_s
{
  int msg_type;
  uint16_t client_id;

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

  uint8_t has_connection;
} net_connection_t;

void n_setup (const char *hostname, uint16_t port);

void n_calc_client_id ();

void n_send (net_data_t *msg);

void n_destroy ();

extern net_data_t n_last_msg;
extern net_data_t n_clients[16];
extern net_connection_t n_connection;
extern uint16_t n_client_id;

#endif /* NETWORK_H */
