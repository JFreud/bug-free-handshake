#include "pipe_networking.h"


int main() {

  int to_client;
  int from_client;

  //char * usermod = malloc(512);
  from_client = server_handshake( &to_client );

  while (1) {
    char * usermod = malloc(512);
    read(from_client, usermod, sizeof(usermod));
    printf("Here it is: %s\n", usermod);
    usermod = strcat(usermod, " repeats the server");
    printf("Modified stuff: %s\n", usermod);
    write(to_client, usermod, sizeof(usermod));
    
  }
}
