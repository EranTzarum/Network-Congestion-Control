# include <stdio.h>
# include <string.h> 
#include <netinet/in.h>
#include <netinet/tcp.h>  


#if defined _WIN32

// link with Ws2_32.lib
#pragma comment(lib,"Ws2_32.lib")
#include <winsock2.h>
#include <ws2tcpip.h>

#else
#include <stdlib.h> 
#include <errno.h> 
#include <string.h> 
#include <sys/types.h> 
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <unistd.h>
#endif
#define SIZE 1024*1024-1
#define SERVER_PORT 5551
#define SERVER_IP_ADDRESS "127.0.0.1"
#include <time.h>


clock_t recv_file(int sockfd){
  int n = -1;
  char buffer[SIZE];
  clock_t start = 0;
 
  while (n != 0) {
    start = clock();
    n = recv(sockfd, buffer, SIZE, 0);
    if (n <= 0){
      break;
      return start;
    }
    bzero(buffer, SIZE);
  }
  return start;
}

long double calc_time(clock_t start,clock_t end){
    clock_t time = end - start;
    long double TIME = time;
    printf("time to recv file: %Lf \n",TIME);
    return TIME;
}

void time_average(long double average[]){
    long double n = 0;
    long double timeAverage = 0;
    for (size_t i = 0; i < 5; i++){
        n = n + average[i];
    }
    timeAverage = n/5;
    printf("time average to recv file: %Lf \n",timeAverage);
}

int main(){
    long double average[5];
    // Open the listening (server) socket
    int listeningSocket = -1;  
	 
    if((listeningSocket = socket(AF_INET , SOCK_STREAM , 0 )) == -1){
        printf("Could not create listening socket");
    }

	// Reuse the address if the server socket on was closed
	// and remains for 45 seconds in TIME-WAIT state till the final removal.
	//
  int enableReuse = 1;
    if (setsockopt(listeningSocket, SOL_SOCKET, SO_REUSEADDR,(const char*)&enableReuse,sizeof(int)) < 0){
         printf("setsockopt() failed with error code");
    }
        // "sockaddr_in" is the "derived" from sockaddr structure
        // used for IPv4 communication. For IPv6, use sockaddr_in6
        //
    struct sockaddr_in serverAddress;
    memset(&serverAddress, 0, sizeof(serverAddress));

    serverAddress.sin_family = AF_INET;
    serverAddress.sin_addr.s_addr = INADDR_ANY;
    serverAddress.sin_port = htons(SERVER_PORT);  //network order

    int connect = -1;

    if((connect = bind(listeningSocket, (struct sockaddr*)&serverAddress, sizeof(serverAddress))) < 0) {
        perror("[-]Error in bind");
        exit(1);
    }
    printf("[+]Binding successfull.\n");

    if(listen(listeningSocket, 10) == 0){
        printf("[+]Listening....\n");
    }
    else{
        perror("[-]Error in listening");
        exit(1);
    }


    struct sockaddr_in clientAddress; 
    socklen_t clientAddressLen = sizeof(clientAddress);
    for (size_t i = 0; i < 2; i++){
        for (int j = 0; j < 5; j++){
            memset(&clientAddress, 0, sizeof(clientAddress));
            clientAddressLen = sizeof(clientAddress);
            int clientSocket = -1;
            if ((clientSocket = accept(listeningSocket, (struct sockaddr *)&clientAddress, &clientAddressLen)) == -1){
                printf("listen failed");
                close(listeningSocket);
            }
            printf("A new client connection accepted\n");
            clock_t start = recv_file(clientSocket);
            clock_t end = clock();
            average[j] = calc_time(start,end);
        }
        time_average(average);
        if (i==0)
        {
            printf("algo change\n");
        }
    }
    
   
    close(listeningSocket);
     
    return 0;
}

