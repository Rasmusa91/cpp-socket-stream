#include "TCPSocket.h"

TCPSocket::TCPSocket(int p_Type)
{
	m_Type = p_Type;

	// Star WSA
	printf("Starting WSA \n");
	m_Result = WSAStartup(MAKEWORD(2, 2), &m_WSAData);

	// Settings of the socket (TCP)
	ZeroMemory(&m_AddrInfoSettings, sizeof(m_AddrInfoSettings));
	m_AddrInfoSettings.ai_family = AF_INET;
	m_AddrInfoSettings.ai_socktype = SOCK_STREAM;
	m_AddrInfoSettings.ai_protocol = IPPROTO_TCP;
	m_AddrInfoSettings.ai_flags = AI_PASSIVE;
	m_Result = getaddrinfo(NULL, DEFAULT_PORT, &m_AddrInfoSettings, &m_AddrInfoResult);

	// Create the listening socket
	printf("Creating listetning socket \n");
	m_ListenSocket = socket(m_AddrInfoResult->ai_family, m_AddrInfoResult->ai_socktype, m_AddrInfoResult->ai_protocol);
	if (m_ListenSocket == INVALID_SOCKET) {
		m_Result = SOCKET_ERROR;
	}

	// Bind the socket
	m_Result = bind(m_ListenSocket, m_AddrInfoResult->ai_addr, (int)m_AddrInfoResult->ai_addrlen);

	// Clean up the address data
	freeaddrinfo(m_AddrInfoResult);

	// Start listening for clients
	printf("Listening for clients \n");
	m_Result = listen(m_ListenSocket, SOMAXCONN);

	// Accept connection
	m_ClientSocket = accept(m_ListenSocket, NULL, NULL);
	if (m_ClientSocket == INVALID_SOCKET) {
		m_Result = SOCKET_ERROR;
	}

	// Closet hte listening socket
	closesocket(m_ListenSocket);

	// Make sure there was no errors on the way
	if (m_Result == 0)
	{
		while (true)
		{
			// Recieve msg from client
			printf("Waiting for msg from client \n");
			recv(m_ClientSocket, m_RecieveBuffer, m_RedieveBufferLength, 0);
			printf("Recieved msg from client, sending image \n");

			// Create the file
			File file("img.png");
			char fileSizeBytes[4];
			file.GetFileSizeBytes(fileSizeBytes, 4);

			// Send the file size in bytes
			send(m_ClientSocket, fileSizeBytes, 4, 0);

			// Transfer
			if (m_Type == TRANSFER)
			{
				// Send the file
				printf("Sending file: %d/%db", file.GetFileSize(), file.GetFileSize());
				send(m_ClientSocket, file.GetFileBytes(), file.GetFileSize(), 0);
			}
			// Stream
			else if (m_Type == STREAM)
			{
				int offset = 0;
				int wantedChunkSize = 100;

				do 
				{
					int chunkSize;
					char * chunk = file.GetChunk(wantedChunkSize, offset, chunkSize);
					offset += chunkSize;

					// Send the chunk
					printf("Sending chunk: %db/%db", offset, file.GetFileSize());
					send(m_ClientSocket, chunk, chunkSize, 0);
				} 
				while (offset >= file.GetFileSize());
			}

			printf("File sent \n");
		}
	}
	else {
		printf("Error");
	}

	// Clean up
	closesocket(m_ClientSocket);
	WSACleanup();
}
