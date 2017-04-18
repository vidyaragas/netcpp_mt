// ServerSocket.h
#ifndef SERVERSOCKET_H
#define SERVERSOCKET_H 

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/time.h>
#include <unistd.h> 
#include <string> 

#include "BaseSocket.h" 

class NetPool;

class ServerSocket : public BaseSocket {
	private:
		int m_port;
		struct sockaddr_in m_address;
		NetPool *p_netPool;
	public:
		ServerSocket(int port, NetPool *np);
		void init(void);
		void newEvent(void);
		NetPool* getNetPool(void);
		~ServerSocket();
};

#endif
