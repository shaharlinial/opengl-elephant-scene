#include "MozFloor.h"

MozFloor::MozFloor() :
pos_color{ 0.2f,0.2f,0.2f,0.8f },
bg_color{ 0.7f, 0.7f,0.7f, 0.8f } {};


void MozFloor::change_colors(GLfloat fg[4], GLfloat bg[4]) {
	for (int i = 0; i <= 4; i++) {
		pos_color[i] = fg[i];
		bg_color[i] = bg[i];
	}
}

void MozFloor::draw(int size) {

	glPushMatrix();
	glEnable(GL_BLEND);
	glBegin(GL_QUADS);
	glNormal3d(0, 1, 0);

	GLfloat specular[] = { 1.0f, 1.0f,1.0f },
		shininess = 4.0f;
		//emission[] = { 0.0f, 0.0f, 0.f, 1.0f };
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specular);
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, shininess);
	//glMaterialfv(GL_FRONT, GL_EMISSION, emission);

	for (int x = -size; x < size; x++) {
		for (int z = -size; z < size; z++) {
			glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, (x + z) % 2 == 0 ? pos_color : bg_color);
			glVertex3d(x, 0, z);
			glVertex3d(x + 1, 0, z);
			glVertex3d(x + 1, 0, z + 1);
			glVertex3d(x, 0, z + 1);
		}
	}

	glEnd();
	glDisable(GL_BLEND);
	glPopMatrix();
}
