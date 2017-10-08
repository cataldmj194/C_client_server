#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
 
int main(int argc,char **argv) {

  int socket_fd;      //socket file descriptor
  char sendline[100]; //hold message to send
  char recvline[100]; //hold message received

  //socket struct
  struct sockaddr_in server_addr;
 
  //socket: returns an int file descriptor if successful, -1 else
  //AF_INET: Internet Domain Sockets
  //SOCK_STREAM: Byte-Stream socket
  //0: Uses unspecified default protocol for the requested socket type
  socket_fd = socket(AF_INET, SOCK_STREAM, 0);
  bzero(&server_addr,sizeof(server_addr));
 
  //Sets address family
  server_addr.sin_family=AF_INET;
  server_addr.sin_port=htons(22000);
 
  //inet_pton: converts the string for local loopback into a
  //network address structure in the af address family, then
  //copies the network address structure to server_addr.sin_addr.
  inet_pton(AF_INET, "127.0.0.1", &(server_addr.sin_addr));

  //connect: connects the socket referred to
  //by the file descriptor sockfd to the address specified by server_addr. 
  connect(socket_fd, (struct sockaddr *) &server_addr, sizeof(server_addr));
 
  while(1) {
    bzero(sendline, 100);
    bzero(recvline, 100);
    fgets(sendline, 100, stdin); /*stdin = 0 , for standard input */
 
    write(socket_fd, sendline, strlen(sendline)+1);
    read(socket_fd, recvline, 100);
    printf("%s", recvline);
  }
}
