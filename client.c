#include <netdb.h> 
#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 
#include <sys/socket.h>
#include <netinet/in.h> 
#include <unistd.h> 
#include <sys/types.h> 
#include <arpa/inet.h> 
#include <ctype.h>
#define MAX 1024

void chat(int sockfd) 
{ 
    char buff[MAX];
    int n; 
   
printf("Enter your Message : ");

while(1) { 
        
	bzero(buff, MAX); 
       			  
        		n = 0; 
        	
	while ((buff[n++] = getchar()) != '\n'); 
        
		
		write(sockfd, buff, sizeof(buff)); 
        	
		bzero(buff, sizeof(buff)); 
        	
		read(sockfd, buff, sizeof(buff)); 
        		
			printf("From Server: %s\t To Server : ", buff); 

        if ((strncmp(buff, "exit", 4)) == 0) { 
            printf("Client Exit...\n"); 
            break; 
        } 
    } 
} 
  
int main(int argc , char *argv[]) 
{ 
    char buffer[MAX],character,chars;
    int sockfd, connfd,portno; 
    int input;
    int counter = 0;
    FILE *fd;
    struct sockaddr_in servaddr; 

	if(argc < 2){
		printf("Usage %s Port Number\n", argv[0]);
		printf("Exitting\n");
		exit(0);
}
  
    // socket create and varification 
    sockfd = socket(AF_INET, SOCK_STREAM, 0); 
    if (sockfd == -1) { 
        printf("socket creation failed...\n"); 
        exit(0); 
    } 
    else
        printf("Socket successfully created..\n"); 
    bzero(&servaddr, sizeof(servaddr)); 
  
    portno=atoi(argv[1]);

    
    // assign IP, PORT 
    servaddr.sin_family = AF_INET; 
    servaddr.sin_addr.s_addr = inet_addr("127.0.0.1"); 
    servaddr.sin_port = htons(portno); 
  
    // connect the client socket to server socket 
    if (connect(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr)) != 0) { 
        printf("connection with the server failed...\n"); 
        exit(0); 
    } 
    else
        printf("connected to the server..\n"); 


if(portno==9090) {

bzero(buffer,1024);
    
	fd=fopen("ceng421.txt","r");

    while((character=fgetc(fd))!=EOF)			//Counting number of words in the file
	{	
		fscanf(fd , "%s" , buffer);
		if(isspace(character)||character=='\t')
		counter++;	
	}

	write(sockfd, &counter, sizeof(int));
     	rewind(fd);
       
    while(chars != EOF)
      {
		fscanf(fd,"%s",buffer);
		write(sockfd,buffer,1023);
		chars = fgetc(fd);
      }
	printf("The file was sent successfully\n");
    
    close(sockfd);
}
else{

    // function for chat 

    chat(sockfd); 
    
    // close the socket 

    close(sockfd);

} 
}
