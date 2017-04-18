#ifndef THRQUEUECONTROLLER_H
#define THRQUEUECONTROLLER_H

#include <cstring>
#include <vector>
#include <deque>
#include <thread>            
#include <mutex>            
#include <condition_variable>

#include "ThrMessageQueue.h"

using namespace std;

class ThrQueueController 
{
private:
	vector<ThrMessageQueue*> m_queue;
	int m_size;
	int m_currIndex;
	NetInterface *m_interface;
public:
        ThrQueueController(int a, NetInterface *ni);
	void init(void);
        ~ThrQueueController(void);
        void initThreads(void);
        ThrMessageQueue* getNextThread(void);
	inline void setInterface(NetInterface *ni) { m_interface = ni; };
	inline NetInterface* getInterface(void) { return m_interface; };
	
};

#endif
