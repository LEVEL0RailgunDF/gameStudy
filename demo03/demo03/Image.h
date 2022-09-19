#pragma once
#include "File.h"

class Image
{
public:

private:
	const char* mFilename = nullptr;
	int mSize = 0;
	char* mData = nullptr;
	File imageFile;
public:
	Image();
	Image(const char* filename);
	void load(const char* filename);

	//int size();
	//char* data();


	~Image();
private:
};

