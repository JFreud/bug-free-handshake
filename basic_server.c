#include "pipe_networking.h"


int main() {

  int to_client;
  int from_client;

  char * usermod = malloc(512);
  from_client = server_handshake( &to_client );

  while (1) {
    read(from_client, usermod, sizeof(usermod));
    if (strlen(usermod) > 0) {
      printf("Here it is: %s\n", usermod);
      usermod = strcat(usermod, " repeats the server");
      write(to_client, usermod, sizeof(usermod));
    }
  }
}
