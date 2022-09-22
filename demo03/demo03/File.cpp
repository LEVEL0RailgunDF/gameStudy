#include "File.h"

File::File()
{
}

File::File(const char* filename)
{
	load(filename);
}

void File::load(const char* filename)
{
	this->mFilename = filename;
	
	ifstream infile;
	infile.open(filename,ios::binary);
	infile.seekg(0,ifstream::end);
	mSize = static_cast<int>(infile.tellg());

	infile.seekg(0, ifstream::beg);

	mData = new char[mSize];
	infile.read(mData,mSize);

}

unsigned File::getUnsigned(int position)
{
	const unsigned char *up;
	unsigned result;
	up = reinterpret_cast<const unsigned char*>(&mData[position]);

	result = up[3];
	result |= (up[2] << 8);
	result |= (up[0] << 24);
	result |= (up[1] << 16);
	return result;
}



int File::size()
{
	return this->mSize;
}

char* File::data()
{
	return mData;
}

File::~File()
{
}
