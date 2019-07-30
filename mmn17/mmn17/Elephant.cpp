#include "Elephant.h"
#include <GL\freeglut.h>

Elephant::Elephant() :headHorizontalAngle(0.0f),
headVerticalAngle(5.0f),
tailHorizontalAngle(0.0f),
tailVerticalAngle(0.0f),
legsAngle(0.0f),
legsMovementDirectionForward(true),
nextMove(nullptr),
isMoving(false) {};

void Elephant::init() {
	GLfloat viewModelMatrix[16];
	glGetFloatv(GL_MODELVIEW_MATRIX, viewModelMatrix);
	glLoadIdentity();
	glTranslatef(5.0f, -6.2f, -8.93);
	glRotatef(145.0f, 0.0f, 1.0f, 0.0f);
	glScalef(0.8f, 0.8f, 0.8f);
	glGetFloatv(GL_MODELVIEW_MATRIX, local);
	glLoadMatrixf(viewModelMatrix);
}
void Elephant::place(GLfloat x, GLfloat y, GLfloat z) {
	GLfloat viewModelMatrix[16];
	glGetFloatv(GL_MODELVIEW_MATRIX, viewModelMatrix);
	glLoadIdentity();

	glRotatef(-90.0f, 0.0f, 1.0f, 0.0f);
	glScalef(1.0f, 1.0f, 1.0f);
	glTranslatef(x, y, z);

	glGetFloatv(GL_MODELVIEW_MATRIX, local);
	glLoadMatrixf(viewModelMatrix);
}
void Elephant::draw() {
	updateConstantMovement();

	glPushMatrix();
	GLfloat body_color[4] = { 0.4f, 0.4, 0.4, 1.0f };
	GLfloat head_color[4] = { 0.2f, 0.2f, 0.2f, 1.0f };
	glColor4fv(body_color);

	GLfloat eleph_specular[] = { 0.20f, 0.20f, 0.20f },
		eleph_shininess = 0.8f;

	glMaterialfv(GL_FRONT, GL_SPECULAR, eleph_specular);
	glMaterialf(GL_FRONT, GL_SHININESS, eleph_shininess);
	glMaterialf(GL_FRONT, GL_EMISSION, 0);
	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, body_color);

	//torso
	glPushMatrix();
	glScalef(1.667f, 1.11f, 2.3333f);
	glTranslatef(0.0f, 0.7f, 0.0f);
	glutSolidSphere(1, 30, 30);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(0.0f, 0.7f, 2.0f);
	glScalef(1.2f, 0.9f, 0.9f);
	glutSolidSphere(1, 30, 30);
	glPopMatrix();
	
	
	//head rotation
	glPushMatrix();
	glRotatef(headVerticalAngle, 1, 0, 0);
	glRotatef(headHorizontalAngle, 0, 1, 0);
	//head
	glColor4fv(head_color);
	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, head_color);
	glPushMatrix();
	glTranslated(0.0f, 1.1f, -2.3f);
	glScalef(1.0f , 1.02f , 1.0f );

	glutSolidSphere(1, 30, 30);
	glPopMatrix();
	//nose
	//first-part-nose
	glPushMatrix();
	glTranslated(0.0f, 0.0f, 1.0f);
	glTranslated(0.0f, 1.0f, -4.3f);
	glRotatef(-60, 1, 0, 0);
	glScalef(0.1f, 0.1f, 0.5f);
	glutSolidSphere(1, 30, 30);
	glPopMatrix();
	//second-part-nose
	glPushMatrix();
	glTranslated(0.0f, 0.0f, 1.0f);
	glTranslated(0.0f, 0.5f, -4.55f);
	glRotatef(-70, 1, 0, 0);
	glScalef(0.1f, 0.1f, 0.38f);
	glutSolidSphere(1, 30, 30);
	glPopMatrix();
	//third-part-nose
	glPushMatrix();
	glTranslated(0.0f, 0.0f, 1.0f);
	glTranslated(0.0f, -0.05f, -4.6f);
	glRotatef(-95, 1, 0, 0);
	glScalef(0.1f, 0.1f, 0.55f);
	glutSolidSphere(1, 30, 30);
	glPopMatrix();
	//forth-part-nose
	glPushMatrix();
	glTranslated(0.0f, 0.0f, 1.0f);
	glTranslated(0.0f, -0.55f, -4.46f);
	glRotatef(-130, 1, 0, 0);
	glScalef(0.1f, 0.1f, 0.3f);
	glutSolidSphere(1, 30, 30);
	glPopMatrix();
	//fifth-part-nose
	glPushMatrix();
	glTranslated(0.0f, 0.0f, 1.0f);
	glTranslated(0.0f, -0.65f, -4.2f);
	glScalef(0.15f, 0.15f, 0.15f);
	glutSolidSphere(1, 30, 30);
	glPopMatrix();

	//ears
	glPushMatrix();
	glTranslated(-0.9f, 1.0f, -2.0f);
	glScalef(0.2f, 1.2f, 0.9f);
	glutSolidSphere(1, 30, 30);
	glPopMatrix();

	glPushMatrix();
	glTranslated(0.9f, 1.0f, -2.0f);
	glScalef(0.2f, 1.2f, 0.9f);
	glutSolidSphere(1, 30, 30);
	glPopMatrix();
	//end head
		////eyes
	GLfloat eyes_specular[] = { 1.0f, 1.0f, 1.0f },
		eyes_shininess = 1.0f;
	GLfloat white[] = { 1,1,1,1 };
	GLfloat black[] = { 0,0,0,1 };
	glColor4fv(white);
	glMaterialfv(GL_FRONT, GL_SPECULAR, eyes_specular);
	glMaterialf(GL_FRONT, GL_SHININESS, eyes_shininess);
	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, white);
	//white-frame-eyes
	//white-frame-left
	glPushMatrix();
	glTranslated(0.35f, 1.5f, -3.2f);
	glRotatef(90, 1, 0, 0);
	glScalef(0.2f, 0.2f, 0.2f);
	glScalef(0.9f, 0.2f, 1.2f);
	glutSolidSphere(1, 30, 30);
	glPopMatrix();
	//white-frame-right
	glPushMatrix();
	glTranslated(-0.35f, 1.5f, -3.2f);
	glRotatef(90, 1, 0, 0);
	glScalef(0.2f, 0.2f, 0.2f);
	glScalef(0.9f, 0.2f, 1.2f);
	glutSolidSphere(1, 30, 30);
	glPopMatrix();
	//black-left
	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, black);
	glColor4fv(black);
	glPushMatrix();
	glTranslated(0.35f, 1.4f, -3.25f);
	glRotatef(90, 1, 0, 0);
	glScalef(0.1f, 0.1f, 0.1f);
	glScalef(0.9f, 0.2f, 1.2f);
	glutSolidSphere(1, 30, 30);
	glPopMatrix();
	//black-right
	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, black);
	glColor4fv(black);
	glPushMatrix();
	glTranslated(-0.35f, 1.4f, -3.25f);
	glRotatef(90, 1, 0, 0);
	glScalef(0.1f, 0.1f, 0.1f);
	glScalef(0.9f, 0.2f, 1.2f);
	glutSolidSphere(1, 30, 30);
	glPopMatrix();
	glPopMatrix();

	//legs
	glColor4fv(body_color);
	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, body_color);
	glPushMatrix();
	glRotatef(legsAngle, 1, 0, 0);
	glPushMatrix();
	glTranslated(0.8f, -0.8f, -1.5f);
	glScalef(0.35f, 1.6f , 0.35f );
	glutSolidSphere(1, 30, 30);
	glPopMatrix();
	glPushMatrix();
	glTranslated(0.8f, -2.0f, -1.5f);
	glScalef(0.4f, 0.4f, 0.4f);
	glutSolidSphere(1, 30, 30);
	glPopMatrix();
	glPopMatrix();

	glPushMatrix();
	glRotatef(legsAngle, 1, 0, 0);
	glPushMatrix();
	glTranslated(0.8f, -0.8f, 1.5f);
	glScalef(0.35f, 1.6f, 0.35f);
	glutSolidSphere(1, 30, 30);
	glPopMatrix();
	glPushMatrix();
	glTranslated(0.8f, -2.0f, 1.5f);
	glScalef(0.4f, 0.4f, 0.4f);
	glutSolidSphere(1, 30, 30);
	glPopMatrix();
	glPopMatrix();

	glPushMatrix();
	glRotatef(legsAngle, 1, 0, 0);
	glPushMatrix();
	glTranslated(-0.8f, -0.8f, -1.5f);
	glScalef(0.35f, 1.6f, 0.35f);
	glutSolidSphere(1, 30, 30);
	glPopMatrix();
	glPushMatrix();
	glTranslated(-0.8f, -2.0f, -1.5f);
	glScalef(0.4f, 0.4f, 0.4f);
	glutSolidSphere(1, 30, 30);
	glPopMatrix();
	glPopMatrix();

	glPushMatrix();
	glRotatef(legsAngle, 1, 0, 0);
	glPushMatrix();
	glTranslated(-0.8f, -0.8f, 1.5f);
	glScalef(0.35f, 1.6f, 0.35f);
	glutSolidSphere(1, 30, 30);
	glPopMatrix();
	glPushMatrix();
	glTranslated(-0.8f, -2.0f, 1.5f);
	glScalef(0.4f, 0.4f, 0.4f);
	glutSolidSphere(1, 30, 30);
	glPopMatrix();
	glPopMatrix();

	//tail
	glPushMatrix();
	glRotatef(tailVerticalAngle, 1, 0, 0);
	glRotatef(tailHorizontalAngle, 0, 1, 0);
	glPushMatrix();
	glTranslated(0.0f, -0.2f, 3.2f);
	glRotatef(-30, 1, 0, 0);

	glScalef(0.2f , 1.8f, 0.2f);
	glutSolidSphere(1, 30, 30);
	glPopMatrix();
	glPushMatrix();
	glTranslated(0.0f, -1.6f, 4.0f);
	glRotatef(-30, 1, 0, 0);
	glRotatef(tailVerticalAngle, 1, 0, 0);
	glRotatef(tailHorizontalAngle, 0, 1, 0);
	glScalef(0.13f, 0.13f, 0.13f);
	glutSolidSphere(1, 30, 30);
	glPopMatrix();
	glPopMatrix();

	glPopMatrix();

	glPopMatrix();
	
}

void Elephant::updateConstantMovement() {
	if (isMoving) {
		if (legsAngle > 8 || legsAngle < -8)
		{
			legsMovementDirectionForward = !legsMovementDirectionForward;
		}
		if (legsMovementDirectionForward)
		{
			legsAngle += 3.0;
		}
		else {
			legsAngle -= 3.0;
		}
		isMoving = false;
	}
}