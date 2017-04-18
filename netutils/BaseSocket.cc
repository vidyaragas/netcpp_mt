#include "BaseSocket.h"

#include <iostream>
#include <string.h>

#include "NetPool.h"
#include "NetInterface.h"

using namespace std;
/***********************************************************************************/
BaseSocket::BaseSocket(void) : m_socket(0) 
{
	init();
}
/***********************************************************************************/
void BaseSocket::init(void){

	 //create socket
	 if( (m_socket = socket(AF_INET , SOCK_STREAM , 0)) == 0) {
	 	cerr << "socket failed" << endl;
	 	exit(EXIT_FAILURE);
	 }

	 int opt = 1;
	 if( setsockopt(m_socket, SOL_SOCKET, SO_REUSEADDR, (char *)&opt, sizeof(opt)) < 0 ) {
        	cerr << "setsockopt" << endl ;
        	exit(EXIT_FAILURE);
    	}


	 
}
/***********************************************************************************/
void BaseSocket::newEvent(void) {
	char buffer[1024];
	int valread = 0; 	
	if ((valread = read( m_socket , buffer, 1024)) == 0)
               {
		struct sockaddr_in address;
		int addrlen = sizeof(address);
                    //Somebody disconnected , get his details and print
                     getpeername(m_socket , (struct sockaddr*)&address , (socklen_t*)&addrlen);
		    cout << "Host disconnected, port#: " << m_socket << endl;

                    //Close the socket and mark as 0 in list for reuse
                     close( m_socket );
                   //call netpool to clearup this socket 
                   getNetPool()->removeFromPool(m_socket);
                }
                 else
                {
                buffer[valread] = '\0';
		//move the message to processing thread
		//
		ThrMessage *tm = new ThrMessage();
		tm->method = 0;
		tm->socket = m_socket;
		std::string a(buffer);
		tm->data = a;
		getNetPool()->getThrQueueController()->getNextThread()->addToQueue(tm);
                    //send(m_socket , buffer , strlen(buffer) , 0 );
		    //cerr << m_socket << " : " << buffer << endl;
                }
}

/***********************************************************************************/
int BaseSocket::getSocketID(void) {
	return m_socket;
}
/***********************************************************************************/
void BaseSocket::setSocketID(int sockid) {
	m_socket = sockid;
}

/***********************************************************************************/
NetPool* BaseSocket::getNetPool(void) {
	return p_netPool;
}
/***********************************************************************************/
BaseSocket::~BaseSocket(void)
{

}
