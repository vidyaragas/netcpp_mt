// ClientSocket.h
#ifndef CLIENTSOCKET_H
#define CLIENTSOCKET_H 

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/time.h>
#include <unistd.h> 
#include <string> 

#include "BaseSocket.h"

class NetPool;

class ClientSocket : public BaseSocket {
	private:
		NetPool *p_netPool;
		struct sockaddr_in m_address;
	public:
		ClientSocket(std::string host, int port,NetPool *np);
		ClientSocket(int socket,NetPool *np);
		void init(void);
		//void newEvent(void);
		NetPool* getNetPool(void);
		~ClientSocket();
};
#endif
