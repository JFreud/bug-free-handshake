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

  printf("server started\n");
  mkfifo("WKP", 0644);
  //printf("Second hello\n");
  int pfd = open("WKP", O_RDONLY, 0644);
  if (pfd == -1) {
    printf("%s\n", strerror(errno));
  }
  printf("Server: WKP Created\n");
  char * pvtfifo = malloc(512);
  //printf("pvt start\n");
  read(pfd, pvtfifo, sizeof(pvtfifo));
  //printf("read end\n");



  if(strcmp(pvtfifo, "priv") == 0){
    printf("Server: Received connection\n");
    close(pfd);
    //mkfifo("ser_to_cli", 0644);
    *to_client = open(pvtfifo, O_WRONLY);
    //printf("%d\n", *to_client);
    char * testmsg = "yes";
    write(*to_client, testmsg, sizeof(testmsg));
    printf("Server: Sent message\n");

  }

  char * confirmed = malloc(512);
  read(pfd, confirmed, sizeof(confirmed));
  if (strcmp(confirmed, "confirmed")) {
    printf("Server: Handshake confirmed\n");
  }

  //printf("Hello!!!\n");

  free(pvtfifo);
  free(confirmed);

  return pfd;
}


/*=========================
  client_handshake
  args: int * to_server

  Perofrms the client side pipe 3 way handshake.
  Sets *to_server to the file descriptor for the upstream pipe.

  returns the file descriptor for the downstream pipe.
  =========================*/
int client_handshake(int *to_server) {

  //printf("Client hello\n");
  *to_server = open("WKP", O_WRONLY, 0644);
  //printf("%d\n", *to_server);
  char * sent= "priv";
  write(*to_server, sent, sizeof(sent));
  printf("Client: Sent connection\n");


  mkfifo("priv", 0644);
  int pfd = open("priv", O_RDONLY, 0644);
  if (pfd == -1){
    printf("%s\n", strerror(errno));
  }
  //printf("%d\n", pfd);


  // int pfd1 = open("ser_to_cli", O_RDONLY);
  char * message = malloc(512);
  read(pfd, message, sizeof(message));

  if (strcmp(message, "yes") == 0) {
    printf("Client: Received message\n");
    close(pfd);
    char * confirm = "confirmed";
    printf("Client: Sending confirmation\n");
    if(write(*to_server, confirm, sizeof(confirm)) == -1){
      printf("!!!\n");
      printf("some sort of error: %s\n", strerror(errno));
      exit(0);
    }
    printf("hm\n");
  }

  printf("?\n");
  free(message);

  return pfd;
}
