/***********************************************************************
 * Driver program for Client implementation
***********************************************************************/
#include "NetPool.h"
#include "ClientSocket.h"
#include "NetInterface.h"
#include <iostream>
#include <ctime>
#include <chrono>
using namespace std;

#define WORKER_THREADS 1 
#define SERVER_HOST "127.0.0.1"
#define SERVER_PORT 8888

/***********************************************************************
 * Client callback implementation
***********************************************************************/
class ClientNetInterface : public NetInterface {
	private:
	std::thread m_thread;
	clock_t begin,end;

        public:
                void onNewMessage(int s, string msg);
		void startThread(int s);
		void testMessages(int s);
};
void ClientNetInterface::onNewMessage(int s, string msg) {
        cout << endl<< "recvd on: " << s << ", msg: " << msg << endl;
	end = clock();
	double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
        cout << "Elapsed time: " << elapsed_secs << endl;
}
void ClientNetInterface::startThread(int s) {
	m_thread = std::thread(&ClientNetInterface::testMessages, this, s);
}
void ClientNetInterface::testMessages(int s) {
	while(true) {
		std::this_thread::sleep_for(std::chrono::seconds(1));
		std::string testmsg("test msg_" );
		testmsg.append(std::to_string(begin));
		begin = clock();
		sendReply(s, testmsg);
	}
}
/***********************************************************************
 * main 
***********************************************************************/
	

int main() {


	NetPool *np = new NetPool();
	
	ClientNetInterface *cni = new ClientNetInterface();
	ThrQueueController *tqc = new ThrQueueController(WORKER_THREADS, (NetInterface *)cni);
	ClientSocket *cs = new ClientSocket(SERVER_HOST,SERVER_PORT, np);

	np->setThrQueueController(tqc);
	np->addToPool(cs->getSocketID(), cs);
	//client thread to keep sending messages
	cni->startThread(cs->getSocketID());
	for(;;) 
		np->run();

}

