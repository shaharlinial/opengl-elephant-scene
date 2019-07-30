#include "Camera.h"

// Basic init constructor
Camera::Camera() : position{ 4.0f, 5.0f, 15.0f },
center{ -2.3f, -5.0f, -15.0f },
up{ 0.0f, 1.0f, 0.0f }{};


void Camera::set_pos(float posX, float posY, float posZ) {
	position[0] = posX;
	position[1] = posY;
	position[2] = posZ;
}

void Camera::set_center(float cenX, float cenY, float cenZ) {
	center[0] = cenX;
	center[1] = cenY;
	center[2] = cenZ;
}
void Camera::set_up(float upX, float upY, float upZ) {
	up[0] = upX;
	up[1] = upY;
	up[2] = upZ;
}
//They work nice but didn't use them eventually.
void Camera::move(char direction, float units) {
	switch (direction) {
	case 'L':
		set_pos(position[0]+ units, position[1], position[2]);
		set_center(center[0]+ units, center[1], center[2]);
		break;
	case 'U':
		set_pos(position[0], position[1]+ units, position[2]);
		set_center(center[0], center[1]+units, center[2]);
		break;
	}
}
void Camera::zoom(float units) {
	set_pos(position[0] + units, position[1] + units, position[2] + units);
}



