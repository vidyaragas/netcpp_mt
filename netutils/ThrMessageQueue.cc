#include "ThrMessageQueue.h" 
#include <iostream>
#include <sys/types.h>
#include <sys/socket.h>

using namespace std;
/****************************************************************************
 * ThrMessageQue
****************************************************************************/
ThrMessageQueue::ThrMessageQueue(NetInterface *ni):m_interface(ni)
{
	init();
} 
void ThrMessageQueue::init()
{

m_thread = std::thread(&ThrMessageQueue::startThread, this);

}
void ThrMessageQueue::startThread()
{
	while(true) {
	//std::this_thread::sleep_for (std::chrono::seconds(10));
		if(!m_queue.empty()){
			ThrMessage *tm = m_queue.front();
			processMessage(tm);
			removeFromQueue();
			delete tm;	
		}
	}
}
void ThrMessageQueue::addToQueue(ThrMessage *tm)
{
	m_mutex.lock();
	m_queue.push_back(tm); 
	m_mutex.unlock();
	
}
void ThrMessageQueue::removeFromQueue()
{
	m_mutex.lock();
	m_queue.pop_front(); 
	m_mutex.unlock();

}
void ThrMessageQueue::processMessage(ThrMessage *tm)
{
	getInterface()->onNewMessage(tm->socket, tm->data);
}
ThrMessageQueue::~ThrMessageQueue()
{

}
