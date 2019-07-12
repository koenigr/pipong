#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/time.h>

#include <fstream>
#include <iostream>

#define BUFSIZE 1024
#define PORT 2222
#define CONFIG_FILE "own_ip.txt"

void error(const char *msg)
{
    perror(msg);
    exit(1);
}

long int getms(timeval tp) {
     gettimeofday(&tp, NULL);
     return tp.tv_sec * 1000 + tp.tv_usec / 1000;
}

long int getmicrosec(timeval tp) {
    gettimeofday(&tp, NULL);
    return tp.tv_usec;
}

void print_addr(sockaddr_in addr, int port) {
    char str[INET_ADDRSTRLEN];
    inet_ntop(AF_INET, &(addr.sin_addr), str, INET_ADDRSTRLEN);
    printf("Address: %s\n", str);
    printf("Read portno %d\n", port);
}

void create_addr(const char* inetaddr, sockaddr_in &addr, int port) {
    memset((char *) &addr, 0, sizeof(addr));
    addr.sin_family = AF_INET;
//    addr.sin_addr.s_addr = inet_addr(inetaddr);
    addr.sin_addr.s_addr = INADDR_ANY;
    addr.sin_port = htons(port);
}

void create_broadcast(sockaddr_in &addr, int port) {
    memset((char *) &addr, 0, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = inet_addr("10.1.1.255");
    addr.sin_port = htons(port);
}

void send_message(sockaddr_in out_addr, int sockfd, char message[]) {
    char buffer[BUFSIZE];
    memset(buffer, 0, BUFSIZE);
    socklen_t clilen = sizeof(out_addr);
    strcpy(buffer, message);
    printf("Send message: %s\n", buffer);
    sendto(sockfd, buffer, strlen(buffer), 0, (struct sockaddr *)&out_addr, clilen);
}

int main(int argc, char *argv[])
{
     int sockfd;
     int portown = PORT;
     int clientlen;
     socklen_t clilen;
     char buffer[BUFSIZE];
     struct sockaddr_in own_addr;
     struct sockaddr_in recv_addr;
     struct timeval tp;
     std::string log_filename;
     const std::string own_ip;
     std::ifstream config_file_stream;


     if (argc < 2) {
       printf("Usage: udp_receive <log_filename>\n");
       exit 1;
     }

     log_filename = argv[1];

     config_file_stream.open(CONFIG_FILE);
     while (std::getline(config_file_stream, own_ip))
     {
       std::cout << own_ip;
     }
     config_file_stream.close();

     sockfd =  socket(AF_INET, SOCK_DGRAM | SOCK_NONBLOCK, 0);
     if (sockfd < 0)
        error("ERROR opening socket");

     int broadcast=1;


     if(setsockopt(sockfd,SOL_SOCKET,SO_BROADCAST,&broadcast,sizeof(broadcast)) < 0)
     {

        printf("Error in setting Broadcast option\n");
        return 1;

     }

     printf("Socket created.\n");

     create_addr((const char* )own_ip, own_addr, portown);

     print_addr(own_addr, portown);

     if (bind(sockfd, (struct sockaddr *) &own_addr, sizeof(own_addr)) < 0) {
         error("ERROR on binding");
         exit 1;
     }


     // RECEIVE
     long int ms_start = getms(tp);

     printf("Read socket\n");


     int message_count = 0;


     while(true) {

        if (recvfrom(sockfd,buffer, 255, 0, (struct sockaddr *)&recv_addr, &clilen) > 0) {

            long int ref = getmicrosec(tp);

            std::ofstream out("receive.txt", std::ios::app);


            printf("Receive message: %s\n",buffer);

            out << ref;
	    out << "\t";
            out << buffer;
            out << "\n";
            message_count++;

        out.close();

        }
        memset(buffer, 0, BUFSIZE);

     }

     long int ms_then = getms(tp);

     printf("Received %d messages after %lu", message_count, ms_then - ms_start);

     close(sockfd);
     return 0; 
}
