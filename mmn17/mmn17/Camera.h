#pragma once
#include "GL/freeglut.h"

class Camera {
public:
	Camera();
	void move(char direction, float units);
	void zoom(float units);
	void set_pos(float posX, float poxY, float posZ);
	void set_center(float cenX, float cenY, float cenZ);
	void set_up(float upX, float upY, float upZ);
	~Camera() = default;
	GLfloat position[3];
	GLfloat center[3];
	GLfloat up[3];
};