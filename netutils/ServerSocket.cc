#include <iostream>
#include <string.h>

#include "ServerSocket.h"
#include "ClientSocket.h"
#include "NetPool.h"
#include "NetInterface.h"

using namespace std;

 /****************************************************************************
 *
 *****************************************************************************/
ServerSocket::ServerSocket(int port, NetPool *np): m_port(port), p_netPool(np)
{
	init();
}
void ServerSocket::init() {
    	m_address.sin_family = AF_INET;
    	m_address.sin_addr.s_addr = INADDR_ANY;
    	m_address.sin_port = htons( m_port );

	if (bind(m_socket, (struct sockaddr *)&m_address, sizeof(m_address))<0) {
        	cerr << "bind failed" << endl;
        	exit(EXIT_FAILURE);
    	}

	if (listen(m_socket, 10) < 0)
    	{
        	cerr << "listen" << endl; 
        	exit(EXIT_FAILURE);
    	}


	
}
void ServerSocket::newEvent(void) {
	cout << "ServerSocket::newEvent " << endl;
	//the new event here would be to accept the connection request
	int addrlen = sizeof(m_address);
	int new_socket;	
	if((new_socket = accept(m_socket, (struct sockaddr *)&m_address, (socklen_t*)&addrlen))<0)
	{ 
		cerr << "accept" << endl;
                exit(EXIT_FAILURE);
        }
	cout << "New connection, socket fd: " << new_socket << endl;
	//"ip is " << inet_ntoa(m_address.sin_addr)  << ", port: " << ntohs(m_address.sin_port) << endl;
	ClientSocket *cs = new ClientSocket(new_socket, this->getNetPool());
	(this->getNetPool())->addToPool(new_socket, cs);	
}

NetPool* ServerSocket::getNetPool(void) {
	return p_netPool;
}
ServerSocket::~ServerSocket(void)
{
}
