#include "CookieJar.h"

void CookieJar::draw()
{
	GLUquadric * disk;
	disk = gluNewQuadric();
	glPushMatrix();
	GLfloat color[4] = { 0.98f, 0.98f, 0.98f, 1.0f };
	GLfloat wood_color[4] = { 0.651f, 0.502f, 0.392f, 1.0f };
	GLfloat handle_color[4] = { 0.1f, 0.1f, 0.1f, 1.0f };

	//glColor4fv(color);

	GLfloat specular[] = { 0.1f, 0.1f, 0.1f },
		shininess = 0.3f;

	glMaterialfv(GL_FRONT, GL_SPECULAR, specular);
	glMaterialf(GL_FRONT, GL_SHININESS, shininess);
	glMaterialf(GL_FRONT, GL_EMISSION, 0);
	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, color);

	//scale to model with higher values
	glScalef(0.3f, 0.3f, 0.3f);

	glPushMatrix();
	glRotatef(90, 1, 0, 0);
	glScalef(1.2, 1.2, 0.1);
	glutSolidCylinder(1, 30, 30, 5);
	glPopMatrix();

	glPushMatrix();
	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, handle_color);
	glTranslatef(0, 0.2, 0);
	glRotatef(45, 0, 1, 0);
	glScalef(0.5, 0.5, 1.0);
	gluDisk(disk, 1, 1.4, 20, 10);
	glPopMatrix();
	glPushMatrix();
	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, wood_color);

	glScalef(1.0, 0.3, 1.0);
	glutSolidSphere(1.2, 30, 30);

	glPopMatrix();
	glPopMatrix();
}