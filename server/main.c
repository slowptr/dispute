#include <enet/enet.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_CLIENTS 16
#define PORT 1933

typedef struct {
  ENetPeer *peer;
  int connected;
} Client;

typedef struct vec3_s {
  float x, y, z;
} vec3_t;
typedef struct viewangles_s {
  float pitch, yaw;
} viewangles_t;

typedef struct net_data_s {
  int msg_type;
  uint16_t client_id;

  vec3_t position;
  viewangles_t angles;
  float health;
} net_data_t;

Client clients[MAX_CLIENTS];

void broadcastMessage(ENetHost *server, ENetPeer *sender,
		      const net_data_t *message) {
  ENetPacket *packet = enet_packet_create(message, sizeof(net_data_t),
					  ENET_PACKET_FLAG_RELIABLE);

  for (int i = 0; i < MAX_CLIENTS; ++i) {
    if (clients[i].connected && clients[i].peer != sender) {
      enet_peer_send(clients[i].peer, 0, packet);
    }
  }

  enet_host_flush(server);
}

int main() {
  if (enet_initialize() != 0) {
    fprintf(stderr, "Failed to initialize ENet.\n");
    return EXIT_FAILURE;
  }

  ENetAddress address;
  ENetHost *server;

  address.host = ENET_HOST_ANY;
  address.port = PORT;

  server = enet_host_create(&address, 32, 2, 0, 0);
  if (server == NULL) {
    fprintf(stderr, "Failed to create the server.\n");
    enet_deinitialize();
    return EXIT_FAILURE;
  }

  ENetEvent event;
  net_data_t message;

  printf("Server started. Listening on port %d...\n", address.port);

  while (1) {
    if (enet_host_service(server, &event, 10) > 0) {
      switch (event.type) {
	case ENET_EVENT_TYPE_CONNECT: {
	  printf("A client connected.\n");

	  // Find an available slot for the new client
	  int clientIndex = -1;
	  for (int i = 0; i < MAX_CLIENTS; ++i) {
	    if (!clients[i].connected) {
	      clientIndex = i;
	      break;
	    }
	  }

	  if (clientIndex != -1) {
	    clients[clientIndex].peer = event.peer;
	    clients[clientIndex].connected = 1;
	  } else {
	    fprintf(stderr,
		    "Max number of clients reached. "
		    "Disconnecting new client.\n");
	    enet_peer_disconnect_now(event.peer, 0);
	  }

	  break;
	}

	case ENET_EVENT_TYPE_RECEIVE: {
	  memcpy(&message, event.packet->data, sizeof(net_data_t));

	  if (message.msg_type == 0 || message.msg_type == -1) {
	    broadcastMessage(server, event.peer, &message);
	  }

	  enet_packet_destroy(event.packet);
	  break;
	}

	case ENET_EVENT_TYPE_DISCONNECT: {
	  printf("A client disconnected.\n");

	  for (int i = 0; i < MAX_CLIENTS; ++i) {
	    if (clients[i].connected && clients[i].peer == event.peer) {
	      net_data_t msg;
	      msg.msg_type = -1;
	      msg.client_id = i;

	      broadcastMessage(server, clients[i].peer, &msg);
	      clients[i].connected = 0;
	      break;
	    }
	  }

	  break;
	}

	case ENET_EVENT_TYPE_NONE:
	  break;
      }
    }
  }

  enet_host_destroy(server);
  enet_deinitialize();

  return EXIT_SUCCESS;
}
