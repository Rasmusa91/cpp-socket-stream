#pragma comment(lib,"ws2_32.lib")

#define BUFLEN 2048
#define PORT 27015

#include<winsock2.h>

#include "File.h"

using namespace std;

class UDPSocket
{
public:
	static const int TRANSFER = 0;
	static const int STREAM = 1;

private:
	int m_Type;

	WSADATA m_WSAData;
	SOCKET m_Socket;
	struct sockaddr_in m_ServerAdress, m_ClientAdress;
	int m_RecievedLength;
	int m_RecieveBufferLength;
	char m_RecieveBuffer[BUFLEN];

public:
	UDPSocket(int p_Type);
};