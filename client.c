#include "pipe_networking.h"


int main() {

  int to_server;
  int from_server;



  char * userin = malloc(512);
  char * serverout = malloc(512);

  while(1) {

    from_server = client_handshake( &to_server );
    printf("Enter some text:\n");
    fgets(userin, sizeof(userin), stdin);
    write(to_server, userin, sizeof(userin));
  }
}
