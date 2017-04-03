#pragma once

#include<string>
#include <fstream>

using namespace std;

class File
{
private:
	char * m_FileBytes;
	int m_FileSize;

public:
	File(string p_FileName);
	~File();

	char * GetFileBytes();
	int GetFileSize();
	void GetFileSizeBytes(char p_Result[], int p_Size);

	char * GetChunk(int p_WantedSize, int p_Offset, int & p_ChunkSize);
};