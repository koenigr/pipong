
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

void create_addr(const char* inetaddr, sockaddr_in &addr, int port) {
    bzero((char *) &addr, sizeof(addr));
    addr.sin_family = AF_INET;
    // addr.sin_addr.s_addr = INADDR_ANY;
    addr.sin_addr.s_addr = inet_addr(inetaddr);
    addr.sin_port = htons(port);
}

void create_broadcast(sockaddr_in &addr, int port) {
    bzero((char *) &addr, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = inet_addr("255.255.255.0");
    //addr.sin_addr.s_addr = INADDR_BROADCAST;
    addr.sin_port = htons(port);
}

int send_message(sockaddr_in out_addr, int sockfd, char message[]) {
	char buffer[BUFSIZE];
    memset(buffer, 0, BUFSIZE);
    socklen_t clilen = sizeof(out_addr);
    strcpy(buffer, message);
    printf("Send message: %s\n", buffer);
    int n = sendto(sockfd, buffer, strlen(buffer), 0, (struct sockaddr *)&out_addr, clilen);
    return n;
}

int main(int argc, char *argv[])
{
     int portown = 2222;
     int portout = 3333;
     int clientlen;
     socklen_t clilen;
     char buffer[BUFSIZE];
     struct sockaddr_in own_addr;
     struct sockaddr_in broadcast_addr;
     struct sockaddr_in direct_addr;
     struct timeval tp;
     int loop_count = 10;
     int sockfd =  socket(AF_INET, SOCK_DGRAM | SOCK_NONBLOCK, 0);
     if (sockfd < 0)
        error("ERROR opening socket");

 	 int broadcast=1;
  	 setsockopt(sockfd, SOL_SOCKET, SO_BROADCAST,
        (void *) &broadcast, sizeof(broadcast));

     printf("Socket created.\n");

     create_addr("10.1.1.10", own_addr, portown);
     print_addr(own_addr, portown);

     create_broadcast(broadcast_addr, portout);
     printf("Broadcast: \n");
     print_addr(broadcast_addr, portout);

     create_addr("10.1.1.20", direct_addr, portout);
     print_addr(direct_addr, portout);

     if (bind(sockfd, (struct sockaddr *) &own_addr,
              sizeof(own_addr)) < 0)
              error("ERROR on binding");

     printf("Start sending to broadcast address\n");

     {
     // SEND BROADCAST
     long int start_total_time = getms(tp);
     printf("start_total_time: %lu\n", start_total_time);
     long int ms_start = getms(tp);
     printf("ms_start: %lu\n", ms_start);
     long int ms_then = getms(tp);
     printf("ms_then: %lu\n", ms_then);

     for (int i = 0; i < loop_count;) {
       if ((ms_then - ms_start) > 1000) {
    	   // SEND
    	   char m[BUFSIZE];
    	   sprintf(m, "Hi! says port %d", portown);
    	   int n = send_message(broadcast_addr, sockfd, m);
    	   printf("Message sent with return code %d\n", n);
           ms_start = getms(tp);
           i++;
       }
       ms_then = getms(tp);
     }

     long int end_total_time = getms(tp);

     printf("Sending to broadcast address finished after %ld\n", end_total_time - start_total_time);
     }

     usleep(5000000);

     printf("Start sending to direct addresses\n");

     {
     // SEND DIRECT
     long int start_total_time = getms(tp);
     long int ms_start = getms(tp);
     long int ms_then = getms(tp);
     for (int i = 0; i < loop_count;) {
       if ((ms_then - ms_start) > 1000) {
    	   // SEND
    	   char m[BUFSIZE];
    	   sprintf(m, "Hi! says port %d", portown);
    	   int n = send_message(direct_addr, sockfd, m);
    	   printf("Message sent with return code %d\n", n);
           ms_start = getms(tp);
           i++;
       }
       ms_then = getms(tp);
     }

     long int end_total_time = getms(tp);

     printf("Sending to direct addresses finished after %lu\n", end_total_time - start_total_time);
     }

     printf("Total package count: %d\n", 2 * loop_count);

     close(sockfd);
     return 0; 
}
