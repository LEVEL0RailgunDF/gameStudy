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
