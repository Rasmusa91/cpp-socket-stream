#include "TCPSocket.h"
#include "UDPSocket.h"

int main()
{
	//printf("Starting TCP (transfer) \n");
	//TCPSocket tcpSocketTransfer(TCPSocket::TRANSFER);

	//printf("Starting TCP (stream) \n");
	//TCPSocket tcpSocketStream(TCPSocket::STREAM);

	printf("Starting UDP (transfer) \n");
	UDPSocket udpSocketTransfer(TCPSocket::TRANSFER);

	//printf("Starting UDP (stream) \n");
	//TCPSocket udpSocketStream(TCPSocket::STREAM);

	return 0;
}