#define TRUE 1 
#define FALSE 0 

class sockServ
{
        public:
                sockServ();
		int opt = TRUE;
        	int master_socket , addrlen , new_socket , client_socket[30] ,
                max_clients  , activity, i , valread, port, sd;
        	int max_sd;
        	struct sockaddr_in address;
		struct timeval tv;
        	char buffer[1025]; //data buffer of 1K

        	//set of socket descriptors
        	fd_set readfds;
		        //a message 
		const char *message = "ECHO Daemon v1.0 \r\n";


                void init(int port,int max_clients);
                void check(void);
		void (*clientCallBack)(void);
};
