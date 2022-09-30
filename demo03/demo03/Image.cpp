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
	
	mHeight = imageFile.getUnsigned(12);
	mWidth = imageFile.getUnsigned(16);

	cout << "Image::load："<< mHeight <<"  "<< mWidth << " " << size() << endl;

	mImageData = new unsigned[size()];
	for (int i = 0; i < size(); i++) {
		mImageData[i] = imageFile.getUnsigned(128 + i * 4);
	}
}

void Image::loadPNG(const char* filename)
{

	return;

	imageFile.load(filename);
	char* tempData = imageFile.data();

//	unsigned pos = 8;
//
//	unsigned length;
//	char *chunkType;
//	//new unsigned[size()] data
//	unsigned char* CRC;
//
//
//	length = imageFile.getUnsigned(pos);
//
//	chunkType = &tempData[pos + 4];
//
//	cout << chunkType[0] << chunkType[1] << chunkType[2] << chunkType[3] <<endl ;
//	while (pos<imageFile.size()) {
//		if (chunkType[0] == 'I' && chunkType[1] == 'E' && chunkType[2] == 'N' && chunkType[3] == 'D') {
//			break;
//		}
//
//		
//		if (chunkType[0] == 'I' && chunkType[1] == 'H' && chunkType[2] == 'D' && chunkType[3] == 'R') {
//			mWidth = imageFile.getUnsigned(pos + 8);
//			mHeight = imageFile.getUnsigned(pos + 12);
//			
//			unsigned bitDepth = reinterpret_cast<const unsigned char*>(&tempData[pos + 16])[0];
//			unsigned colourType = reinterpret_cast<const unsigned char*>(&tempData[pos + 17])[0];
//			unsigned compressionMethod = reinterpret_cast<const unsigned char*>(&tempData[pos + 18])[0];
//			unsigned filterMethod = reinterpret_cast<const unsigned char*>(&tempData[pos + 19])[0];
//			unsigned interlaceMethod = reinterpret_cast<const unsigned char*>(&tempData[pos + 20])[0];
//
//			cout << "mHeight:" << mHeight << endl;
//			cout << "mWidth:" << mWidth << endl;
//			cout << "bitDepth:" << bitDepth << endl;
//			cout << "colourType:" << colourType << endl;
//			cout << "compressionMethod:" << compressionMethod << endl;
//			cout << "filterMethod:" << filterMethod << endl;
//			cout << "interlaceMethod:" << interlaceMethod << endl;
//		}
//
//		if (chunkType[0] == 'I' && chunkType[1] == 'D' && chunkType[2] == 'A' && chunkType[3] == 'T') {
//	
//			Byte *compr, *uncompr;
//			compr = new Byte[length*2];
//			uncompr = new Byte[length*20];
//			uLongf test = length * 20;
//
//			compr = reinterpret_cast<Byte*>(&tempData[pos + 8]);
//
//			cout << "test:" << *reinterpret_cast<unsigned *>(&test) << endl;
//
//			//for (int i = 0; i < length*2; i++) {
//			//	compr[i] = ;
//			//}
//
//			//inflateInit2();
//
//			cout << "uncompress:"<<uncompress(uncompr, &test, compr, length*2)<<endl;
//			cout << "test:" << *reinterpret_cast<unsigned *>(&test) << endl;
//\
//			signed dataLen = test / 8;
//			mImageData = new unsigned[mWidth*mHeight];
//
//
//			//for (int i = 0; i < test; i++) {
//			//	cout << uncompr[i] << endl;
//			//}
//
//
//		/*	for (int i = 0; i < dataLen; i++) {
//
//				const unsigned char* up;
//				unsigned result;
//				up = reinterpret_cast<const unsigned char*>(&uncompr[i*8]);
//
//				result = up[0];
//				result |= (up[1] << 8);
//				result |= (up[2] << 24);
//				result |= (up[3] << 16);
//
//				result = up[0];
//				result |= (up[1] << 8);
//				result |= (up[2] << 24);
//				result |= (up[3] << 16);
//
//				mImageData[i] = result;
//			}*/
//
//			
//			for (int y = 0; y < mHeight; y++) {
//				const unsigned char* up = reinterpret_cast<const unsigned char*>(&uncompr[y * (mWidth + 1)]);
//				cout <<"----------" << up[0]  << endl;
//
//				for (int x = 0; x < mWidth; x++) {
//
//					const unsigned char* up = reinterpret_cast<const unsigned char*>(&uncompr[(y * (mWidth + 1) + x + 1)*3]);
//
//					unsigned result;
//					result = up[2];
//					result |= (up[1] << 8);
//					result |= (up[0] << 16);
//					
//					//result |= (up[3] << 24);
//					//cout <<"----------" << up[0] <<"  " << up[1] << "  " << up[2] << "  " << up[3] << endl;
//					//cout <<"==========" <<up[0] << (up[1] << 8) << (up[2] << 16) << (up[3] << 24) << endl;
//					mImageData[y*mWidth + x] = result;
//
//				}
//			}
//
//
//		}
//		
//		pos = pos + 12 + length;
//		length = imageFile.getUnsigned(pos);
//		chunkType = &tempData[pos + 4];
//		cout << chunkType[0] << chunkType[1] << chunkType[2] << chunkType[3] << endl;
//		
//	}
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
			unsigned imageData = mImageData[temp];
			

			if (imageData & 0x80000000) { //判断是否透明
				vram[(dstY + y) * windowWidth + dstX + x] = mImageData[temp];
			}
			else {
				
			}

			
		}
	}

}

Image::~Image()
{
}
