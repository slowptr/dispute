#include "network.h"
#include <pthread.h>
#include <stdio.h>
#include <string.h>

net_data_t n_last_msg;
net_data_t n_clients[16];
net_connection_t n_connection;

uint16_t n_client_id;

void *
n__networking (void *args)
{
  ENetEvent event;
  while (1)
    {
      if (enet_host_service (n_connection.host, &event, 10) > 0)
        {
          switch (event.type)
            {
            case ENET_EVENT_TYPE_CONNECT:
              printf ("Connected to the server.\n");
              n_connection.has_connection = 1;
              break;

            case ENET_EVENT_TYPE_RECEIVE:
              {
                memcpy (&n_last_msg, event.packet->data, sizeof (n_last_msg));

                if (n_last_msg.client_id < 16 - 1)
                  {
                    // set msg stuff to certain n_clients
                    n_clients[n_last_msg.client_id].msg_type
                        = n_last_msg.msg_type;
                    if (n_last_msg.msg_type == 0)
                      {
                        n_clients[n_last_msg.client_id].position
                            = n_last_msg.position;
                        n_clients[n_last_msg.client_id].angles
                            = n_last_msg.angles;
                        n_clients[n_last_msg.client_id].health
                            = n_last_msg.health;
                      }
                  }
                else
                  {
                    printf ("Client with invalid id detected: %d.\n",
                            n_last_msg.client_id);
                  }
                enet_packet_destroy (event.packet);
                break;
              }

            case ENET_EVENT_TYPE_DISCONNECT:
              printf ("Disconnected from the server.\n");
              enet_peer_reset (n_connection.peer);
              break;

            case ENET_EVENT_TYPE_NONE:
              break;
            }
        }
    }
  return NULL;
}

pthread_t n__main_thread;

void
n__init ()
{
  if (enet_initialize () != 0)
    {
      perror ("Failed to initialize ENet");
      exit (1);
    }
}
void
n__quit ()
{
  enet_deinitialize ();
}

void
n_calc_client_id ()
{
  for (int i = 0; i < 16; i++)
    {
      if (n_clients[i].msg_type == -1)
        {
          n_client_id = i;
          n_clients[i].msg_type = 0;
          break;
        }
    }
}

void
n_setup (const char *hostname, uint16_t port)
{
  n__init ();

  for (int i = 0; i < 16; i++)
    {
      n_clients[i].msg_type = -1;
    }

  if (enet_address_set_host (&n_connection.con_addr, hostname) != 0)
    {
      perror ("Failed to set server address");
      enet_deinitialize ();
      exit (1);
    }
  n_connection.con_addr.port = port;

  n_connection.has_connection = 0;

  n_connection.host = enet_host_create (NULL, 1, 2, 0, 0);
  if (n_connection.host == NULL)
    {
      perror ("Failed to create the client");
      enet_deinitialize ();
      exit (1);
    }
  n_connection.peer
      = enet_host_connect (n_connection.host, &n_connection.con_addr, 2, 0);
  if (n_connection.peer == NULL)
    {
      perror ("Failed to connect to the server");
      enet_host_destroy (n_connection.host);
      enet_deinitialize ();
      // exit (1);
    }

  if (pthread_create (&n__main_thread, NULL, n__networking, NULL) != 0)
    {
      perror ("Failed to create thread.");
      exit (1);
    }

  n_client_id = -1;
}

void
n_send (net_data_t *msg)
{
  msg->client_id = n_client_id;

  ENetPacket *packet
      = enet_packet_create (msg, sizeof (*msg), ENET_PACKET_FLAG_RELIABLE);
  enet_peer_send (n_connection.peer, 0, packet);
}

void
n_destroy ()
{
  {
    net_data_t msg;
    msg.msg_type = -1;
    n_send (&msg);
  }

  enet_peer_disconnect (n_connection.peer, 0);
  enet_host_destroy (n_connection.host);
  pthread_join (n__main_thread, NULL);

  n__quit ();
}

