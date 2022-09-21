#include "Image.h"

Image::Image()
{
}

Image::Image(const char* filename)
{
	load(filename);
}

void Image::load(const char* filename)
{
	//TODO 区别格式
	imageFile.load(filename);
	char* tempData = imageFile.data();

	mHeight = imageFile.getUnsigned(12);
	mWidth = imageFile.getUnsigned(16);

	cout << "Image::load："<< mHeight <<"  "<< mWidth << " " << size() << endl;

	mImageData = new unsigned[size()];
	for (int i = 0; i < size(); i++) {
		mImageData[i] = imageFile.getUnsigned(128 + i * 4);
	}
}

int Image::size()
{
	return 	mHeight * mWidth;
}

unsigned Image::height()
{
	return mHeight;
}

unsigned Image::width()
{
	return mWidth;
}

unsigned* Image::data()
{
	return mImageData;
}

void Image::drawCell(int dstX, int dstY, int imgX, int imgY, int w, int h)
{
	unsigned* vram = Framework::instance().videoMemory();
	unsigned windowWidth = Framework::instance().width();

	for (int y = 0; y < h; y++) {
		for (int x = 0; x < w; x++) {
			int temp = (imgY + y) * mWidth + imgX + x;
			vram[(dstY + y) * windowWidth + dstX + x] = mImageData[temp];
		}
	}

}

Image::~Image()
{
}
