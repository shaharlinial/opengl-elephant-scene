#include "Plate.h"

void Plate::draw()
{
	GLUquadric * disk;
	disk = gluNewQuadric();
	glPushMatrix();
	GLfloat color[4] = { 0.98f, 0.98f, 0.98f, 1.0f };
	GLfloat specular[] = { 0.1f, 0.1f, 0.1f },
		shininess = 0.3f;

	glMaterialfv(GL_FRONT, GL_SPECULAR, specular);
	glMaterialf(GL_FRONT, GL_SHININESS, shininess);
	glMaterialf(GL_FRONT, GL_EMISSION, 0);
	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, color);

	//scale to model with higher values
	glScalef(0.3f, 0.3f, 0.3f);


	glPushMatrix();
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, color);

	glTranslatef(0, 0.1, 0);
	glRotatef(-90, 1, 0 , 0);
	gluDisk(disk, 2, 3, 20, 10);
	glPopMatrix();
	glPushMatrix();

	glScalef(1.0, 0.1, 1.0);
	glutSolidSphere(2.4, 30, 30);

	glPopMatrix();
	glPopMatrix();
}