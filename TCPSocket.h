#pragma comment (lib, "Ws2_32.lib")

#define WIN32_LEAN_AND_MEAN
#define DEFAULT_BUFLEN 512
#define DEFAULT_PORT "27015"

#include <ws2tcpip.h>

#include "File.h"

using namespace std; 

class TCPSocket
{
public:
	static const int TRANSFER = 0;
	static const int STREAM = 1;

private:
	int m_Type;
	int m_Result;

	WSADATA m_WSAData;

	SOCKET m_ListenSocket = INVALID_SOCKET;
	SOCKET m_ClientSocket = INVALID_SOCKET;

	struct addrinfo m_AddrInfoSettings;
	struct addrinfo * m_AddrInfoResult = NULL;

	char m_RecieveBuffer[DEFAULT_BUFLEN];
	int m_RedieveBufferLength = DEFAULT_BUFLEN;

public:
	TCPSocket(int p_Type);
};