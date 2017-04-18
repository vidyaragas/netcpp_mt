#include "ClientSocket.h"

#include <iostream>
#include <string.h>

#include "NetPool.h"
#include "NetInterface.h"

using namespace std;

 /****************************************************************************
 *
 *****************************************************************************/
ClientSocket::ClientSocket(std::string host, int port, NetPool *np)
{
          if( (m_socket = socket(AF_INET , SOCK_STREAM , 0)) == 0) {
                         cerr << "socket failed" << endl;
                          exit(EXIT_FAILURE);
           }
	memset(&m_address, '0', sizeof(m_address)); 

    	m_address.sin_family = AF_INET;
    	m_address.sin_addr.s_addr = inet_addr(host.c_str());
    	m_address.sin_port = htons( port );
 

    if( connect(m_socket, (struct sockaddr *)&m_address, sizeof(m_address)) < 0)
    {
                         cerr << "Error: Connect failed" << endl;
                          exit(EXIT_FAILURE);
    }

    p_netPool = np; 

}
ClientSocket::ClientSocket(int socket, NetPool *np)
{
	m_socket = socket;
	p_netPool = np;
	init();
}
void ClientSocket::init() {
	
}
//void ClientSocket::newEvent(void) {
//	cout << "ClientSocket::newEvent " << endl;
//}

NetPool* ClientSocket::getNetPool(void) {
	return p_netPool;
}
ClientSocket::~ClientSocket(void)
{
}

