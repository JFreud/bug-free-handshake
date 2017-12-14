#include "pipe_networking.h"


int main() {

  int to_server;
  int from_server;



  char userin[512];
  char serverout[512];
  from_server = client_handshake( &to_server );
  printf("FINISHED HANDSHAKE\n");

  while(1) {
    printf("Enter some text:\n");
    fgets(userin, sizeof(userin), stdin);
    strtok(userin, "\n"); //remove newline
    write(to_server, userin, sizeof(userin));
    read(from_server, serverout, sizeof(serverout));
    printf("Modified data: %s\n", serverout);
  }
  return 0;
}
