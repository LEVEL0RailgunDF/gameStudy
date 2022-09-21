#pragma once
#include <fstream>
using namespace std;
class File
{
public:
	
private:
	const char* mFilename = nullptr;
	int mSize = 0;
	char* mData = nullptr;

public:
	File();
	File(const char* filename);
	void load(const char* filename);
	unsigned getUnsigned(int position);

	int size();
	char* data();


	~File();
private:

};

