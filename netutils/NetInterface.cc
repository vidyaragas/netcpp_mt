#include "NetInterface.h" 
#include <iostream>
#include <sys/types.h>
#include <sys/socket.h>

using namespace std;
/****************************************************************************
 * NetInterface
****************************************************************************/
NetInterface::NetInterface()
{
}

NetInterface::~NetInterface()
{
}
void NetInterface::sendReply(int s, string m)
{
	int siz = m.size();
	send(s , m.c_str() , siz , 0 );

}
