// BaseSocket.h
#ifndef NETPOOL_H
#define NETPOOL_H 

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/time.h>

#include <map>

#include "BaseSocket.h"
#include "ThrQueueController.h"

class NetPool {
	private:
		std::map<int, BaseSocket*> m_connections;
		fd_set m_readfds;
		int m_max_sd;
		ThrQueueController *m_tqController;
	public:	
		void init(void);
		void addToPool(int id, BaseSocket* bskt);
		void removeFromPool(int sockid);
		void updatePool(void);
		void printPool(void);
		void run(void);
		void setThrQueueController(ThrQueueController *tmc);
		inline ThrQueueController* getThrQueueController() { return m_tqController;};
		NetPool();
		~NetPool();	

};
#endif
