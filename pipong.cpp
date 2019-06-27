
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "network/UDPSocket.h"

int main(int argc, char *argv[])
{
  if (argc < 3) {
    fprintf(stderr,"usage %s hostname portown portout\n", argv[0]);
    exit(0);
  }

  int port_self = atoi(argv[1]);
  int port_out = atoi(argv[2]);


  UDPSocket pi_socket(port_self);


     int clientlen;
     socklen_t clilen;

     struct sockaddr_in out_addr; // client's address
     struct sockaddr_in recv_addr; // recv address
     int n; // message byte size


     printf("create socket\n");

     // create a socket
     // socket(int domain, int type, int protocol)





     bzero((char *) &out_addr, sizeof(out_addr)); // clear address structure
     out_addr.sin_family = AF_INET; /* setup the host_addr structure for use in bind call */    // server byte order
     //out_addr.sin_addr.s_addr = inet_addr("255.255.255.255"); // automatically be filled with current host's IP address
	 out_addr.sin_addr.s_addr = INADDR_BROADCAST;
     out_addr.sin_port = htons(portout); // convert short integer value for port must be converted into network byte order

     {
         // now get it back and print it
         char str[INET_ADDRSTRLEN];
         inet_ntop(AF_INET, &(out_addr.sin_addr), str, INET_ADDRSTRLEN);
         printf("Address: %s\n", str);
         printf("Read portno %d\n", portout);

     }




/*
 *
 * RECEIVE
 *
 */


     long int ms_start = getms(tp);
     long int ms_then = getms(tp);

     printf("read socket\n");
     while(true) {



        n = recvfrom(sockfd,buffer, 255, 0, (struct sockaddr *)&recv_addr, &clilen);
        if (n > 0) {
            printf("Here is the message: %s\n",buffer);
        }
        memset(buffer, BUFSIZE, sizeof(buffer));


      //printf("%ld, %ld\n", ms_start, ms_then);

       if ((ms_then - ms_start) > 1000) {

           /*
            *
            * SEND
            */
           // This send() function sends the 13 bytes of the string to the new socket
           printf("send hello world to sockfd\n");
           printf("sockfd: %d\n", sockfd);
           clilen = sizeof(out_addr);
		   bzero(buffer,256);
           sprintf(buffer, "hi! says port %d", portown);
		   //strcpy(buffer, "Sending a message from goddamn port but do not have fucking int");
           n = sendto(sockfd, buffer, strlen(buffer), 0, (struct sockaddr *)&out_addr, clilen);
           bzero(buffer,256);


           ms_start = getms(tp);
       }


       ms_then = getms(tp);;
     }



     return 0;
}
