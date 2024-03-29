#pragma once
#pragma   comment   (linker,"/NODEFAULTLIB:libc.lib")
#include "GameLib/Framework.h"
#include "File.h"

#define ZLIB_WINAPI
#include <zlib.h>

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

	void loadPNG(const char* filename);

	int size();
	unsigned height();
	unsigned width();
	unsigned* data();

	void drawCell(int dstX, int dstY, int imgX, int imgY, int width, int height) const;
	void draw();
	~Image();
private:
};

