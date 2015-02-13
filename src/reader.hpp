#pragma once

#include <string>
#include <iostream>
#include <fstream>
#include <ios>

#include "misc.h"

uint readUInt(std::istream &is)
{
	uint var;
	(((var = is.get()<<24) |= is.get()<<16) |= is.get()<<8) |= is.get();
	return var;
}

class Image
{
public:
	
	uint sx;
	uint sy;
	
	uint digit;
	real *data;
	
	Image(uint sx, uint sy)
	{
		data = new real[sx*sy];
	}
	
	~Image()
	{
		delete data;
	}
};

class ImageSet
{
public:
	
	uint size;
	uint size_x, size_y;
	
	Image **images;
	
	ImageSet(uint s, uint sx, uint sy)
	{
		size = s;
		size_x = sx;
		size_y = sy;
		images = new Image*[size];
	}
	
	~ImageSet()
	{
		delete images;
	}
};

ImageSet *createImageSet(std::string labels, std::string images)
{
	std::ifstream ls(labels), is(images);
	if(!ls.is_open() || !is.is_open())
	{
		std::cerr << "files not found" << std::endl;
		ls.close();
		is.close();
		return nullptr;
	}
	
	uint magic,lnum,inum,rows,cols;
	
	magic = readUInt(ls);
	lnum = readUInt(ls);
	
	if(magic != 2049)
	{
		std::cerr << labels << " is not a label file" << std::endl;
		return nullptr;
	}
	
	magic = readUInt(is);
	inum = readUInt(is);
	rows = readUInt(is);
	cols = readUInt(is);
	
	if(magic != 2051)
	{
		std::cerr << labels << " is not a image file" << std::endl;
		return nullptr;
	}
	
	if(lnum != inum)
	{
		std::cerr << "image and label numbers doesn't match" << std::endl;
		return nullptr;
	}
	
	ImageSet *set = new ImageSet(inum,cols,rows);
	
	char buf;
	for(uint i = 0; i < inum; ++i)
	{
		set->images[i] = new Image(cols,rows);
		
		ls.get(buf);
		set->images[i]->digit = static_cast<uint>(buf);
		
		for(uint iy = 0; iy < rows; ++iy)
		{
			for(uint ix = 0; ix < cols; ++ix)
			{
				is.get(buf);
				set->images[i]->data[iy*cols + ix] = static_cast<real>(*reinterpret_cast<unsigned char*>(&buf))/255.0;
			}
		}
	}
	
	ls.close();
	is.close();
	
	return set;
}

void destroyImageSet(ImageSet *set)
{
	for(uint i = 0; i < set->size; ++i)
	{
		delete set->images[i];
	}
	delete set;
}
