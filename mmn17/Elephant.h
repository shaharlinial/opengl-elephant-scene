#pragma once
#include <GL\freeglut.h>
#include <functional>

class Elephant
{
public:
	Elephant();
	GLfloat local[16];	//local coordinate system transformation matrix
	GLfloat headHorizontalAngle;
	GLfloat headVerticalAngle;
	GLfloat tailHorizontalAngle;
	GLfloat tailVerticalAngle;
	std::function<void()> nextMove;
	bool isMoving;
	void place(GLfloat x, GLfloat y, GLfloat z);
	void init();
	void draw();
	~Elephant() = default;
private:
	void updateConstantMovement();
	GLfloat legsAngle;
	bool legsMovementDirectionForward;
};

