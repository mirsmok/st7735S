/***************************************************************************/
/*                                                                         */    
/* Client program which gets as parameter the server name or               */    
/*     address and tries to send the data into non-blocking server.        */    
/*                                                                         */    
/* The message is sent after 5 seconds of wait                             */    
/*                                                                         */    
/*                                                                         */    
/* based on Beej's program - look in the simple TCp client for further doc.*/    
/*                                                                         */    
/*                                                                         */    
/***************************************************************************/
    #include <stdio.h> 
    #include <stdlib.h> 
    #include <errno.h> 
    #include <string.h> 
    #include <netdb.h> 
    #include <sys/types.h> 
    #include <netinet/in.h> 
    #include <sys/socket.h> 
    #include <unistd.h>

    #define PORT 80    /* the port client will be connecting to */

    #define MAXDATASIZE 100 /* max number of bytes we can get at once */

 int putThingspeakData(void)
{
	int sockfd,field6;  
//	char buf[MAXDATASIZE];
	struct hostent *he;
	struct sockaddr_in their_addr; /* connector's address information */

	char  dest[] = "api.thingspeak.com";
	char data[200];
	data[0]='\0';
//	if (argc != 2) {
//		fprintf(stderr,"usage: client hostname\n");
//		exit(1);
//	}

	if ((he=gethostbyname(dest)) == NULL) {  /* get the host info */
		herror("gethostbyname");
		return -1;
	}

	if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
		perror("socket");
		return -1;
	}

	their_addr.sin_family = AF_INET;      /* host byte order */
	their_addr.sin_port = htons(PORT);    /* short, network byte order */
	their_addr.sin_addr = *((struct in_addr *)he->h_addr);
	bzero(&(their_addr.sin_zero), 8);     /* zero the rest of the struct */

	if (connect(sockfd, (struct sockaddr *)&their_addr, sizeof(struct sockaddr)) == -1) {
		perror("connect");
		return -1;
	}
	strcat(data,"GET https://api.thingspeak.com/update?api_key=LKNC7IOPA202T4QW&field1=");
	char ans[10];
	snprintf(ans,10,"%2.1f",settings.heatingSetpoint)	;
	strcat(data,ans);
	strcat(data,"&field2=");
	snprintf(ans,10,"%2.1f",roomSensor.actualTemperature);
	strcat(data,ans);
	strcat(data,"&field3=");
	snprintf(ans,10,"%2.1f",outputModule.actualTemperature);
	strcat(data,ans);
	strcat(data,"&field4=");
	if(strcmp(outputModule.state.c_str(),"ON")==0) 
		strcat(data,"1");
	else
		strcat(data,"0");
	strcat(data,"&field5=");
	snprintf(ans,10,"%1.2f",roomSensor.batVoltage);
	strcat(data,ans);
	strcat(data,"&field6=");	
	field6=((int)status.error) | ((int)roomSensor.error << 1) | ((int)outputModule.error <<2);
	snprintf(ans,10,"%d",field6);
	strcat(data,ans);
	strcat(data,"\nHost: api.thingspeak.com\n");
	if (send(sockfd, data, strlen(data), 0) == -1){
		perror("send");
		return -1;
	}
//	printf("After the send function \n");
//	sleep(1);
//	if ((numbytes=recv(sockfd, buf, MAXDATASIZE, 0)) == -1) {
//		perror("recv");
//		exit(1);
//	}	

//	buf[numbytes] = '\0';
//	printf("Received in pid=%d, text=: %s \n",getpid(), buf);
//	close(sockfd);
	return 1;
}
