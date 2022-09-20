#pragma once

#include "GameLib/Framework.h"
#include "File.h"
using namespace GameLib;


class Image
{
public:

private:
	const char* mFilename = nullptr;
	unsigned mHeight;
	unsigned mWidth;
	unsigned* mImageData;
	char* mData = nullptr;
	File imageFile;
public:
	Image();
	Image(const char* filename);
	void load(const char* filename);

	int size();
	unsigned height();
	unsigned width();
	unsigned* data();


	~Image();
private:
};

