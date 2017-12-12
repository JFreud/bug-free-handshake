#include "pipe_networking.h"


/*=========================
  server_handshake
  args: int * to_client

  Perofrms the server side pipe 3 way handshake.
  Sets *to_client to the file descriptor to the downstream pipe.

  returns the file descriptor for the upstream pipe.
  =========================*/
int server_handshake(int *to_client) {
  //int READ = 0;
  //int WRITE = 1;

  mkfifo("WKP", 0644);
  int pfd = open("WKP", O_RDONLY);
  char * pvtfifo;
  read(pfd, pvtfifo, sizeof(pvtfifo));
  
  if(strcmp(pvtfifo, "priv") == 0){
    close(pfd);
    mkfifo("ser_to_cli", 0644);
    int pfd1 = open("ser_to_cli", O_WRONLY);
    char * testmsg = "test"
    write("ser_to_cli", testmsg, sizeof(testmsg));

  }



  return 0;
}


/*=========================
  client_handshake
  args: int * to_server

  Perofrms the client side pipe 3 way handshake.
  Sets *to_server to the file descriptor for the upstream pipe.

  returns the file descriptor for the downstream pipe.
  =========================*/
int client_handshake(int *to_server) {
  
  mkfifo("priv", 0644);
  int pfd = open("priv", O_WRONLY);
  char * sent= "priv";
  write("WKP", sent, sizeof(sent));
  
  int pfd1 = open("ser_to_cli", O_RDONLY);

  return 0;
}
