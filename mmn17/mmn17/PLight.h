#pragma once
#include "GL/freeglut.h"

class PLight{
public:
	GLfloat color[4];
	GLfloat pos[4];
	GLfloat spread_angle;
	GLfloat exponent;
	GLenum light_name;
	bool is_enabled;

	PLight(GLenum light_name);
	void addLight();
	void draw();
	void disable();
	void enable();
	~PLight() = default;

};
