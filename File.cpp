#include "File.h"

File::File(string p_FileName)
{
	// Read the file
	ifstream file(p_FileName, ios::binary);
	file.seekg(0, ios::end);
	
	// Get the size of the file
	m_FileSize = (int) file.tellg();
	
	// Initialize the array that stores the bytes of the file
	m_FileBytes = new char[m_FileSize];
	
	// Read the file to the array
	file.seekg(0, ios::beg);
	file.read(m_FileBytes, m_FileSize);
	file.close();
}

// Destroy pointers
File::~File()
{
	delete m_FileBytes;
}

// Get the byte array of the file
char * File::GetFileBytes()
{
	return m_FileBytes;
}

// Get the size of the file
int File::GetFileSize()
{
	return m_FileSize;
}

// Get the size of the file in bytes
void File::GetFileSizeBytes(char p_Result[], int p_Size)
{
	for (int i = 0; i < p_Size; i++) {
		p_Result[3 - i] = (m_FileSize >> (i * 8));
	}
}

// Get a chunk of the byte array of the file
char * File::GetChunk(int p_WantedSize, int p_Offset, int & p_ChunkSize)
{
	p_ChunkSize = p_WantedSize;

	// If the wanted chunk size exceeds the amount of bytes in the array, limit the chunk size
	if (m_FileSize - p_Offset < p_ChunkSize) {
		p_ChunkSize = m_FileSize - p_Offset;
	}

	// Get the bytes of the chunk
	char * chunk = new char[p_ChunkSize];
	for (int i = 0; i < p_ChunkSize; i++) {
		chunk[i] = m_FileBytes[i + p_Offset];
	}

	return chunk;
}