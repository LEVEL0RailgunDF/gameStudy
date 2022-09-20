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

	const unsigned char *theight = reinterpret_cast<const unsigned char*>(& tempData[12]);
	const unsigned char*twidth = reinterpret_cast<const unsigned char*>(& tempData[16]);
	const unsigned char* timageData = reinterpret_cast<const unsigned char*>(&tempData[128]);

	cout << theight[0] << theight[1] << theight[2] << theight[3] <<endl;
	cout << twidth[0] << twidth[1] << twidth[2] << twidth[3] << endl;

	mHeight = theight[0];
	mHeight |= (theight[1] << 8);
	mHeight |= (theight[2] << 16);
	mHeight |= (theight[3] << 24);

	mWidth = twidth[0];
	mWidth |= (twidth[1] << 8);
	mWidth |= (twidth[2] << 16);
	mWidth |= (twidth[3] << 24);


	cout << "Image::load："<< mHeight <<"  "<< mWidth << " " << size() << endl;

	mImageData = new unsigned[size()];
	for (int i = 0; i < size(); i++) {
		const unsigned char* timageData = reinterpret_cast<const unsigned char*>(&tempData[128 + i*4]);
		mImageData[i] = timageData[0];
		mImageData[i] |= (timageData[1] << 8);
		mImageData[i] |= (timageData[2] << 16);
		mImageData[i] |= (timageData[3] << 24);
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
