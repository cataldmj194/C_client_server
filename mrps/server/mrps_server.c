#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

int main(){

  char message[100]; //hold message from client
  int listen_fd; //listen file descriptor
  int comm_fd;   //communication file descriptor

  //server socket struct
  struct sockaddr_in server_addr;

  //socket: returns an int file descriptor if successful, -1 else
  //AF_INET: Internet Domain Sockets
  //SOCK_STREAM: Byte-Stream socket
  //0: Uses unspecified default protocol for the requested socket type
  listen_fd = socket(AF_INET, SOCK_STREAM, 0);
  
  //should change to memset, bzero is deprecated
  //bzero sets first n to s '\0'
  bzero(&server_addr, sizeof(server_addr));

  //Sets address family
  server_addr.sin_family = AF_INET;

  //Sets server internet address struct to address in betwork byte order
  server_addr.sin_addr.s_addr = htons(INADDR_ANY);

  printf("Now listening for connections on port 22000\n");

  //sets server internet port to listen on
  //htons converts values between host and network byte order
  server_addr.sin_port = htons(22000);

  //binds address specified to socket referred to by file descriptor
  bind(listen_fd, (struct sockaddr*) &server_addr, sizeof(server_addr));

  //listens for connections on socket, up to 10 on backlog
  listen(listen_fd, 10);

  //extracts first connection request on queue of pending connections
  comm_fd = accept(listen_fd, (struct sockaddr*) NULL, NULL);
  
  while(1){
    bzero(message,100);

    //read up to 100 bytes from file descriptor comm_fd into str
    read(comm_fd,message,100);
    printf("Echoing back - %s",message);

    //write up to str+1 bytes from str to comm_fd
    write(comm_fd, message, strlen(message)+1);
  }
}
