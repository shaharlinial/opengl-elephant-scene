#pragma once
#include "GL/freeglut.h"
#include <stdlib.h>
#include <string>
#include "texelLoader.h"

class Ball {
public:
	GLfloat local[16];
	Ball();
	void init();
	void draw();
	~Ball();

private:
	TexelLoader texl;
	GLuint tex;
	GLUquadric* sphere;
	GLuint texName;
};
