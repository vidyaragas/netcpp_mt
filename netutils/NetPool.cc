#include "NetPool.h"

#include <iostream>

using namespace std;

NetPool::NetPool(void)
{
	init();
}
void NetPool::init(void){

}
void NetPool::addToPool(int socket, BaseSocket* nb){
	m_connections.insert(std::pair<int, BaseSocket*>(socket, nb));
	printPool();
}
void NetPool::removeFromPool(int sockid){
	cout << "Removing Socket FD: " << sockid << endl;

	auto it = m_connections.begin();
	while(it != m_connections.end())
	{
		if(it->first == sockid)
			break;
		it++;
	}

	if (it != m_connections.end()){
		auto nb = it->second;
		delete nb;
		m_connections.erase(it);
	}
	printPool();
}

void NetPool::printPool() {

	cout << "========================Pool entries ================================" << endl;
	for (auto element : m_connections)
		cout << element.first << endl;
	cout << "=====================================================================" << endl;
}
void NetPool::updatePool() {
	FD_ZERO(&m_readfds);
	int socket;
	m_max_sd = 0;
	auto it = m_connections.begin();
	while(it != m_connections.end())
	{
		socket = it->first;
		FD_SET(socket, &m_readfds);
		if(socket > m_max_sd)
			m_max_sd = socket;
		it++;
	}

}
void NetPool::setThrQueueController(ThrQueueController *tmc)
{
	m_tqController = tmc;
}
void NetPool::run() {

	updatePool();
	int activity;
	activity = select( m_max_sd + 1 , &m_readfds , NULL , NULL , NULL);

        if ((activity < 0) && (errno!=EINTR))
        {
            cerr << "select error" << endl;
        }
	
	int current_fd;
	BaseSocket *current_bs;
	// check which conneciton has activity
	for (auto it = m_connections.begin(); it != m_connections.end(); it++) {
                current_fd = it->first;
                current_bs = it->second;

		if(FD_ISSET(current_fd, &m_readfds)){
			current_bs->newEvent();
		}
        }
}

NetPool::~NetPool(void)
{

}

