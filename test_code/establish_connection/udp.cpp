
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

void print_addr(sockaddr_in addr, int port) {
    char str[INET_ADDRSTRLEN];
    inet_ntop(AF_INET, &(addr.sin_addr), str, INET_ADDRSTRLEN);
    printf("Address: %s\n", str);
    printf("Read portno %d\n", port);
}


int main(int argc, char *argv[])
{

     printf("set variables\n");

     int sockfd;
     int portown;
     int portout;
     int clientlen;
     socklen_t clilen;
     char buffer[BUFSIZE];
     struct sockaddr_in own_addr;
     struct sockaddr_in out_addr;
     struct sockaddr_in recv_addr;
     int n;
     struct timeval tp;

     printf("create socket\n");
     if (argc < 3) {
        fprintf(stderr,"usage %s hostname portown portout\n", argv[0]);
        exit(0);
     }

     portown = atoi(argv[1]);
     portout = atoi(argv[2]);

     sockfd =  socket(AF_INET, SOCK_DGRAM | SOCK_NONBLOCK, 0);
     if (sockfd < 0) 
        error("ERROR opening socket");

 	 int broadcast=1;
  	 setsockopt(sockfd, SOL_SOCKET, SO_BROADCAST,
        (void *) &broadcast, sizeof(broadcast));

     printf("socket created. Set more values\n");


     bzero((char *) &own_addr, sizeof(own_addr));
     own_addr.sin_family = AF_INET;
     own_addr.sin_addr.s_addr = INADDR_ANY;
     own_addr.sin_port = htons(portown);

     print_addr(own_addr, portown);

     bzero((char *) &out_addr, sizeof(out_addr));
     out_addr.sin_family = AF_INET;
	 out_addr.sin_addr.s_addr = INADDR_BROADCAST;
     out_addr.sin_port = htons(portout);

     print_addr(out_addr, portout);

     if (bind(sockfd, (struct sockaddr *) &own_addr,
              sizeof(own_addr)) < 0)
              error("ERROR on binding");

     // RECEIVE
     long int ms_start = getms(tp);
     long int ms_then = getms(tp);

     printf("read socket\n");
     while(true) {

        n = recvfrom(sockfd,buffer, 255, 0, (struct sockaddr *)&recv_addr, &clilen);
        if (n > 0) {
            printf("Here is the message: %s\n",buffer);
        }
        memset(buffer, BUFSIZE, sizeof(buffer));

       if ((ms_then - ms_start) > 1000) {

    	   // SEND
           printf("send hello world to sockfd\n");
           printf("sockfd: %d\n", sockfd);
           clilen = sizeof(out_addr);
		   bzero(buffer,256);
           sprintf(buffer, "hi! says port %d", portown);
           n = sendto(sockfd, buffer, strlen(buffer), 0, (struct sockaddr *)&out_addr, clilen);
           bzero(buffer,256);

           ms_start = getms(tp);
       }


       ms_then = getms(tp);;
     }

     close(sockfd);
     return 0; 
}
