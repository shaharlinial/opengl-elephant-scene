#pragma once
#include "GL\freeglut.h"
#include <string>

class TexelLoader{
public:
	TexelLoader();
	unsigned char* loadTexel(std::string filename);
	unsigned char * texel;
	GLsizei getWidth();
	GLsizei getHeight();
	~TexelLoader()=default;
private:
	GLsizei width;
	GLsizei height;
};