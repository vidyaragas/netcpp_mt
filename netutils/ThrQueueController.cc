#include "ThrQueueController.h" 
#include <iostream>
#include <sys/types.h>
#include <sys/socket.h>

using namespace std;
/****************************************************************************
 * ThrQueueController
****************************************************************************/

ThrQueueController::ThrQueueController(int a, NetInterface *ni):m_size(a),m_interface(ni)
{

init();

}

void ThrQueueController::init(void)
{
	initThreads();
} 
void ThrQueueController::initThreads(void)
{
	for(auto i=0; i< m_size;i++){
		cout << i << ".Starting thread" << endl; 
		ThrMessageQueue *tmq = new ThrMessageQueue(getInterface());
		m_queue.push_back(tmq);

	}
	m_currIndex = 0;
}
ThrMessageQueue* ThrQueueController::getNextThread(void)
{
ThrMessageQueue *ret;
		m_currIndex++;
	if(m_currIndex >= m_queue.size() )
		m_currIndex = 0;	
	ret = m_queue.at(m_currIndex);
return ret;
}
ThrQueueController::~ThrQueueController(void)
{

}
