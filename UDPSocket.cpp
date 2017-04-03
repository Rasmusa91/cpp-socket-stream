#include "UDPSocket.h"

UDPSocket::UDPSocket(int p_Type)
{
	m_Type = p_Type;

	m_RecievedLength = sizeof(m_ClientAdress);

	// Start WSA
	printf("Starting WSA \n");
	WSAStartup(MAKEWORD(2, 2), &m_WSAData);

	// Create socket
	printf("Creating socket \n");
	m_Socket = socket(AF_INET, SOCK_DGRAM, 0);

	// Set information for the socket
	m_ServerAdress.sin_family = AF_INET;
	m_ServerAdress.sin_addr.s_addr = INADDR_ANY;
	m_ServerAdress.sin_port = htons(PORT);

	// Bind the socket
	bind(m_Socket, (struct sockaddr *)&m_ServerAdress, sizeof(m_ServerAdress));
	
	while (true)
	{	
		// Listen for messages
		printf("Waiting for msg \n");
		recvfrom(m_Socket, m_RecieveBuffer, BUFLEN, 0, (struct sockaddr *) &m_ClientAdress, &m_RecievedLength);
		printf("Msg recieved \n");

		// Create the file with the file helper class
		File file("img.png");
		char fileSizeBytes[4];
		file.GetFileSizeBytes(fileSizeBytes, 4);

		// Send the size of the file
		printf("Sending information: 4b/4b");
		sendto(m_Socket, fileSizeBytes, 4, 0, (struct sockaddr *) &m_ClientAdress, sizeof(m_ClientAdress));

		// Transfer
		if (m_Type == TRANSFER)
		{
			// Send the file
			printf("Sending file: %db/%db", file.GetFileSize(), file.GetFileSize());
			sendto(m_Socket, file.GetFileBytes(), file.GetFileSize(), 0, (struct sockaddr *) &m_ClientAdress, sizeof(m_ClientAdress));
		}
		// Stream
		else if (m_Type == STREAM)
		{
			int offset = 0;
			int wantedChunkSize = 100;

			do
			{
				// Get the current chunk
				int chunkSize;
				char * chunk = file.GetChunk(wantedChunkSize, offset, chunkSize);
				offset += chunkSize;

				// Send the chunk
				printf("Sending chunk: %d/%db", offset, file.GetFileSize());
				sendto(m_Socket, chunk, chunkSize, 0, (struct sockaddr *) &m_ClientAdress, sizeof(m_ClientAdress));
			} 
			while (offset >= file.GetFileSize());
		}

		printf("File sent \n");
	}

	closesocket(m_Socket);
	WSACleanup();
}