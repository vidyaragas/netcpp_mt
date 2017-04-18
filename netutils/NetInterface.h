#ifndef NETINTERFACE_H
#define NETINTERFACE_H

#include <cstring>
#include <vector>
#include <deque>
#include <thread>            
#include <mutex>            
#include <condition_variable>

using namespace std;
struct ThrMessage
{
        int method;
        int socket;
        string data;
};

class NetInterface
{
        private:

        public:
                NetInterface(void);
                ~NetInterface(void);
                virtual void onNewMessage(int s, string msg) = 0;
		void sendReply(int socket, string msg);
};

#endif
