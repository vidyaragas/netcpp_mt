/********************************************************************
 * Driver class for Server implementation
********************************************************************/
#include "NetPool.h"
#include "ServerSocket.h"
#include "NetInterface.h"
#include <thread>
#include <iostream>
#include <sstream>

#define WORKER_THREADS 5
#define SERVER_PORT 8888

/********************************************************************
 * Implementation of the callback 
********************************************************************/

class ServerNetInterface : public NetInterface {
	public:
		void onNewMessage(int s, string msg);
};

void ServerNetInterface::onNewMessage(int s, string msg) {
	std::ostringstream ss;
	ss << std::this_thread::get_id();
	msg.append(std::string(":"));
	msg.append(ss.str());
	sendReply(s,msg);
	cout << "Thread: " << std::this_thread::get_id() << " Replied to " << s << endl;
}

/********************************************************************
 * main 
********************************************************************/

int main() {

	NetPool *np = new NetPool();

	ServerNetInterface *sni = new ServerNetInterface();

	ThrQueueController *tqc = new ThrQueueController(WORKER_THREADS, (NetInterface *)sni);

	ServerSocket *ss = new ServerSocket(SERVER_PORT, np);

	np->setThrQueueController(tqc);
	np->addToPool(ss->getSocketID(), ss);
	for(;;) 
		np->run();

}
