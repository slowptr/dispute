#include "network.h"
#include <pthread.h>
#include <stdio.h>

void *
n__networking (void *args)
{
  // implement (dis-)connect event,
  // message receiving
  return NULL;
}

pthread_t n__main_thread;

void
n_main_init ()
{
  if (enet_initialize () != 0)
    {
      perror ("Failed to initialize ENet");
      exit (1);
    }
}

void
n_setup (net_connection_t *connection, const char *hostname, uint16_t port)
{
  if (enet_address_set_host (&connection->con_addr, hostname) != 0)
    {
      perror ("Failed to set server address");
      enet_deinitialize ();
      exit (1);
    }
  connection->con_addr.port = port;

  connection->host = enet_host_create (NULL, 1, 2, 0, 0);
  if (connection->host == NULL)
    {
      perror ("Failed to create the client");
      enet_deinitialize ();
      exit (1);
    }
  connection->peer
      = enet_host_connect (connection->host, &connection->con_addr, 2, 0);
  if (connection->peer == NULL)
    {
      perror ("Failed to connect to the server");
      enet_host_destroy (connection->host);
      enet_deinitialize ();
      exit (1);
    }

  if (pthread_create (&n__main_thread, NULL, n__networking, NULL) != 0)
    {
      perror ("Failed to create thread.");
      exit (1);
    }
}

void
n_send (net_connection_t *connection, net_data_t *msg)
{
  ENetPacket *packet
      = enet_packet_create (msg, sizeof (*msg), ENET_PACKET_FLAG_RELIABLE);
  enet_peer_send (connection->peer, 0, packet);
}

void
n_destroy (net_connection_t *connection)
{
  enet_peer_disconnect (connection->peer, 0);
  enet_host_destroy (connection->host);
  pthread_join (n__main_thread, NULL);
}

void
n_main_quit ()
{
  enet_deinitialize ();
}
