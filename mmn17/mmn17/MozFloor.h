#pragma once
#include "GL/freeglut.h"

class MozFloor{
public:
	MozFloor();
	void draw(int quad_size);
	void change_colors(GLfloat pos_color[4], GLfloat bg_color[4]);
	GLfloat pos_color[4];
	GLfloat bg_color[4];
};