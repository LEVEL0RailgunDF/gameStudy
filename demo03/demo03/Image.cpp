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
	imageFile.load("demo03.dds");
	imageFile.data();

}

Image::~Image()
{
}
