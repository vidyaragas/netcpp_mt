#ifndef THRMESSAGEQUEUE_H
#define THRMESSAGEQUEUE_H

#include <cstring>
#include <vector>
#include <deque>
#include <thread>            
#include <mutex>            
#include <condition_variable>

#include "NetInterface.h"

using namespace std;

class ThrMessageQueue 
{
	private:
		std::thread m_thread;
		std::mutex m_mutex;
        	deque<ThrMessage*> m_queue;
		NetInterface *m_interface;

	public:
		ThrMessageQueue(NetInterface *ni);
		void init(void);
		~ThrMessageQueue(void);
		void startThread(void);
		void addToQueue(ThrMessage *tm);
		void removeFromQueue(void);
		void processMessage(ThrMessage *tm);
		inline void setInterface(NetInterface *ni) { m_interface = ni; };
		inline NetInterface* getInterface(void) { return m_interface; };
};

#endif
