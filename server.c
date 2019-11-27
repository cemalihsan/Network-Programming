#include <stdio.h>
#include <netdb.h> 
#include <netinet/in.h> 
#include <stdlib.h> 
#include <string.h> 
#include <sys/socket.h> 
#include <sys/types.h> 
#include <unistd.h> 
#include <arpa/inet.h> 
#include <ctype.h>
#define MAX 1024


void chat(int sockfd) // Function designed for chat between client and server. 
{ 
    char buff[MAX]; 
    int n; 
    // infinite loop for chat 
    while(1) { 
        
	bzero(buff, MAX); 
  
        n=read(sockfd, buff, sizeof(buff)); // read the message from client and copy it in buffer 
	if(n < 0)
		printf("Error on reading\n");
        
        printf("From client: %s\t To client : ", buff); // print buffer which contains the client contents 
        
	bzero(buff, MAX); 
        n = 0; 
        
        while ((buff[n++] = getchar()) != '\n');// copy server message in the buffer   
  
        n=write(sockfd, buff, sizeof(buff));    // and send that buffer to client 
	
	if(n < 0)
		printf("Error on Writing\n");
  
        // if msg contains "Exit" then server exit and chat ended. 
        if (strncmp("exit", buff, 4) == 0) { 
            printf("Server Exit...\n"); 
            break; 
        } 
    } 
} 
// Driver function 
int main(int argc , char *argv[]) 
{ 
    char buffer[MAX];
    int sockfd, connfd, length, portno; 
    int choice;
    FILE *fp;
    int chars = 0;
    int counter;
    struct sockaddr_in servaddr, client; 

	if(argc < 2){
		printf("Port number not provided.\n");
		printf("Exitting.\n");
		exit(1);		
		}
  
    // socket create and verification 
    sockfd = socket(AF_INET, SOCK_STREAM, 0); 
    if (sockfd < 0) { 
        printf("socket creation failed...\n"); 
        exit(0); 
    } 
    else
        printf("Socket successfully created..\n"); 
    bzero((char *)&servaddr, sizeof(servaddr)); 

    portno=atoi(argv[1]);
  
    // assign IP, PORT 
    servaddr.sin_family = AF_INET; 
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY); 
    servaddr.sin_port = htons(portno); 
  
    // Binding newly created socket to given IP and verification 
    if ((bind(sockfd, (struct sockaddr*)&servaddr, sizeof(servaddr))) != 0) { 
        printf("socket bind failed...\n"); 
        exit(0); 
    } 
    else
        printf("Socket successfully binded..\n"); 
  
    // Now server is ready to listen and verification 
    if ((listen(sockfd, 5)) != 0) { 
        printf("Listen failed...\n"); 
        exit(0); 
    } 
    else
        printf("Server listening..\n"); 
    length = sizeof(client); 
  
    // Accept the data packet from client and verification 
    connfd = accept(sockfd, (struct sockaddr*)&client, &length); 
    if (connfd < 0) { 
        printf("server acccept failed...\n"); 
        exit(0); 
    } 
    else
        printf("server acccept the client...\n"); 

if(portno==9090) {

fp = fopen("ceng421_r.txt","a");            
            
	read(connfd, &counter, sizeof(int));    
          while(chars != counter)
       	   {
        	 read(connfd,buffer,1024); 
	   	 fprintf(fp,"%s",buffer);   
		 chars++;
	   }
     	printf("The file was received successfully\n");

	   printf("The new file created is ceng421.txt\n");

     close(connfd);
     close(sockfd);
   
}
else{
    // Function for chatting between client and server
    chat(connfd); 
    // After chatting close the socket 
    close(sockfd); 	

}
    
} 

