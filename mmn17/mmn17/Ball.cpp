#include "Ball.h"

Ball::Ball() {
	texl.loadTexel("..\\Assests\\basketball.bmp");
	sphere = gluNewQuadric();
}

void Ball::init() {

	glGenTextures(1, &tex);
	glBindTexture(GL_TEXTURE_2D, tex);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, texl.getWidth(), texl.getHeight(), 0, GL_RGB, GL_UNSIGNED_BYTE, (const GLvoid *)texl.texel);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
}
void Ball::draw() {
	glEnable(GL_TEXTURE_2D);
	GLfloat alpha = 0.9;
	GLfloat viewModelMatrix[16];
	glGetFloatv(GL_MODELVIEW_MATRIX, viewModelMatrix);
	glLoadIdentity();
	glTranslatef(-3.0, -7.2, -2.0);
	glRotatef(45, 0, 1, 0);
	glRotatef(180, 1, 0, 0);
	glGetFloatv(GL_MODELVIEW_MATRIX, local);
	glLoadMatrixf(viewModelMatrix);


	glEnable(GL_BLEND);
	GLfloat amb_dif_mat[4] = { 1.0, 1.0, 1.0 , alpha };
	GLfloat specular[] = { 1.0f, 1.0f, 1.0f },
		shininess = 128.0f;

	glMaterialfv(GL_FRONT, GL_SPECULAR, specular);
	glMaterialf(GL_FRONT, GL_SHININESS, shininess);
	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, amb_dif_mat);

	gluQuadricDrawStyle(sphere, GLU_FILL);
	glBindTexture(GL_TEXTURE_2D, tex);
	gluQuadricTexture(sphere, GL_TRUE);
	gluQuadricNormals(sphere, GLU_SMOOTH);
	gluSphere(sphere, 0.9, 32, 16);
	glDisable(GL_TEXTURE_2D);
	glDisable(GL_BLEND);
}

Ball::~Ball() {
	texl.~TexelLoader();
}


