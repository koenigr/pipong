
/* The port number is passed as an argument */
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/time.h>


#define BUFSIZE 1024


void error(const char *msg)
{
    perror(msg);
    exit(1);
}


long int getms(timeval tp) {  
     gettimeofday(&tp, NULL);
     return tp.tv_sec * 1000 + tp.tv_usec / 1000;
}


int main(int argc, char *argv[])
{

     printf("set variables\n");

     int sockfd; // socket
  //   int newsockfd; // new socket ????
     int portown; // port to listen on
     int portout;
     int clientlen;
     socklen_t clilen;
     char buffer[BUFSIZE]; // message buf
     struct sockaddr_in own_addr; // server's address
     struct sockaddr_in out_addr; // client's address
     struct sockaddr_in recv_addr; // recv address
     int n; // message byte size
     struct timeval tp;

     printf("create socket\n");
     if (argc < 3) {
        fprintf(stderr,"usage %s hostname portown portout\n", argv[0]);
        exit(0);
     }
     portown = atoi(argv[1]);
     portout = atoi(argv[2]);
     // create a socket
     // socket(int domain, int type, int protocol)
     sockfd =  socket(AF_INET, SOCK_DGRAM | SOCK_NONBLOCK, 0);
     if (sockfd < 0) 
        error("ERROR opening socket");

 	 int broadcast=1;
  	 setsockopt(sockfd, SOL_SOCKET, SO_BROADCAST,
        (void *) &broadcast, sizeof(broadcast));

     printf("socket created. Set more values\n");


     bzero((char *) &own_addr, sizeof(own_addr)); // clear address structure
     own_addr.sin_family = AF_INET; /* setup the host_addr structure for use in bind call */    // server byte order
     own_addr.sin_addr.s_addr = INADDR_ANY; // automatically be filled with current host's IP address
     own_addr.sin_port = htons(portown); // convert short integer value for port must be converted into network byte order

     {
         // now get it back and print it
         char str[INET_ADDRSTRLEN];
         inet_ntop(AF_INET, &(own_addr.sin_addr), str, INET_ADDRSTRLEN);
         printf("Address: %s\n", str);
         printf("Read portno %d\n", portown);

     }

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


     // bind(int fd, struct sockaddr *local_addr, socklen_t addr_length)
     // bind() passes file descriptor, the address structure, 
     // and the length of the address structure
     // This bind() call will bind  the socket to the current IP address on port, portno
     if (bind(sockfd, (struct sockaddr *) &own_addr,
              sizeof(own_addr)) < 0)
              error("ERROR on binding");

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



     close(sockfd);
     return 0; 
}
