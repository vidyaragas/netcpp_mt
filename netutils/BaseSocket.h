// BaseSocket.h
#ifndef BASESOCKET_H
#define BASESOCKET_H 

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/time.h>
#include <unistd.h> 
#include <string> 

class NetPool;

class BaseSocket {
	protected:
		int m_socket;
		NetPool *p_netPool;
		
	public:
		void init(void);
		BaseSocket();
		int getSocketID(void);
		void setSocketID(int);
		virtual void newEvent(void);
		virtual NetPool* getNetPool(void);
		virtual ~BaseSocket();	

};
#endif
