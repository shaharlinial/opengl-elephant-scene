#pragma once
#include <vector>
#include <GL\freeglut.h>
#include "texelLoader.h"

class Walls {
public:
	GLfloat alpha;
	Walls();
	void init();
	void draw(std::vector<int> wallsIndexs, GLfloat spreadWidth, GLfloat spreadHeight);
	~Walls();

private:
	TexelLoader texl;
	GLuint texName;
};
