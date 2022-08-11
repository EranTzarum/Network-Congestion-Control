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

void send_file(FILE *fp, int sockfd){
  int n;
  char symbol;
  fp = fopen("CC.txt", "r");
  char data[SIZE] = {0};

  while(fgets(data, SIZE, fp) != NULL) {
    if (send(sockfd, data, sizeof(data), 0) == -1) {
      perror("[-]Error in sending file.");
      exit(1);
    }
    // printf("%s",data);
    printf("\n");
    bzero(data, SIZE);
  }
    fclose(fp);
    close(sockfd);
}


void ChangeCCAlgo(FILE *fp, int sockfd){
     char buf[1024];
     char symbol;
     socklen_t len;
     
     if(fp != NULL){
          while((symbol = getc(fp)) != EOF){
               strcat(buf, &symbol);
          }
     }

     len = sizeof(buf); 
     if (getsockopt(sockfd, IPPROTO_TCP, TCP_CONGESTION, buf, &len) != 0) { 
     perror("getsockopt");
     return;
     } 

     printf("Current: %s\n", buf); 



     strcpy(buf, "reno"); 
     len = strlen(buf);
     if (setsockopt(sockfd, IPPROTO_TCP, TCP_CONGESTION, buf, len) != 0) {
     perror("setsockopt"); 
     return;
     }
     len = sizeof(buf); 
     if (getsockopt(sockfd, IPPROTO_TCP, TCP_CONGESTION, buf, &len) != 0) {
     perror("getsockopt"); 
     return; 
     } 
     printf("New: %s\n", buf); 

}

int main(){
     int X = 1024 * 1024 - 1; //size of 1MB file
     FILE *filePointer;

     filePointer = fopen("CC.txt","w"); //open file for writhing 
    //  fputs("eran",filePointer);
     fseek(filePointer, X , SEEK_SET); //resize the file to be 1MB 
     fputc('\0', filePointer); //'\0' in the end of file
     fclose(filePointer);

     for (size_t i = 0; i < 2; i++){

          for (size_t j = 0; j < 5; j++){
               
               int sockfd = -1;
               //open socket
               if((sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1){
                    printf("Could not create socket");
                    }
          

               
               struct sockaddr_in serverAddress;
               memset(&serverAddress, 0, sizeof(serverAddress));

               serverAddress.sin_family = AF_INET;
               serverAddress.sin_port = htons(SERVER_PORT);
          
               // serverAddress.sin_addr.s_addr = inet_addr(SERVER_IP_ADDRESS);
               if (inet_pton(AF_INET, (const char*)SERVER_IP_ADDRESS, &serverAddress.sin_addr)<=0){
                    printf("inet_ptopn failed\n");
               }
          
               int connected = -1; //connect to server

               if((connected = connect(sockfd, (struct sockaddr *)&serverAddress, sizeof(serverAddress))) == -1) {
                    perror("Error in socket");
                    exit(1);
               }
               
               if (i > 0 && j == 0)
               {
                   ChangeCCAlgo(filePointer, sockfd);
               }

               printf("[+]Connected to Server.\n");
               
               send_file(filePointer, sockfd);
               
          }

     }

     return 0;

}



