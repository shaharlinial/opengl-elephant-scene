#include "Walls.h"

Walls::Walls():alpha(0.9)
{
	texl.loadTexel("..\\Assests\\Wood_planks_012_basecolor.bmp");
};

void Walls::init() {
	glGenTextures(1, &texName);
	glBindTexture(GL_TEXTURE_2D, texName);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, texl.getWidth(), texl.getHeight(), 0, GL_RGB, GL_UNSIGNED_BYTE, texl.texel);

};

void Walls::draw(std::vector<int> wallsIndexs, GLfloat spreadWidth, GLfloat spreadHeight) {
	int startWidth = -spreadHeight, endWidth = spreadHeight, startHeight = -spreadWidth, endHeight = spreadWidth;
	GLfloat outWidth = spreadHeight;
	GLfloat outHeight = spreadWidth;
	for (int i : wallsIndexs) {
		glPushMatrix();
		glTranslatef(0.0, -outWidth, -outWidth);
		switch (i) {
		case 0:
			glRotatef(90, 0, 1,0);
			glRotatef(90, 0, 0, 1);
			glTranslatef(outWidth, -outHeight, 0.0f);
			break;
		case 1:
			glRotatef(90, 0, 0, 1);
			glTranslatef(outWidth, outHeight, 0);
			break;
		case 2:
			glRotatef(90, 0, 0, 1);
			glTranslatef(outWidth,-outHeight, 0);
			break;
		case 3:
			glRotatef(90, 1, 0, 0);
			glTranslatef(0, outWidth, -outHeight);
			break;
		}

		glEnable(GL_BLEND);
		GLfloat amb_dif_mat[4] = { 1.0, 1.0, 1.0 , alpha };
		GLfloat specular[] = { 1.0f, 1.0f, 1.0f },
			shininess = 128.0f;

		glMaterialfv(GL_FRONT, GL_SPECULAR, specular);
		glMaterialf(GL_FRONT, GL_SHININESS, shininess);
		glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, amb_dif_mat);
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, texName);
		glBegin(GL_QUADS);

		glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, amb_dif_mat);
		//second quarter
		glTexCoord2f(0.0, 0.0); glVertex3f(startWidth, 0, startHeight);
		glTexCoord2f(0.0, 1.0); glVertex3f(0, 0, startHeight);
		glTexCoord2f(1.0, 1.0); glVertex3f(0, 0, 0);
		glTexCoord2f(1.0, 0.0); glVertex3f(startWidth, 0, 0);
		//third quarter
		glTexCoord2f(0.0, 0.0); glVertex3f(startWidth, 0, 0);
		glTexCoord2f(0.0, 1.0); glVertex3f(0, 0, 0);
		glTexCoord2f(1.0, 1.0); glVertex3f(0, 0, endHeight);
		glTexCoord2f(1.0, 0.0); glVertex3f(startWidth, 0, endHeight);
		// fourth quarter
		glTexCoord2f(0.0, 0.0); glVertex3f(0, 0, 0);
		glTexCoord2f(0.0, 1.0); glVertex3f(endWidth, 0, 0);
		glTexCoord2f(1.0, 1.0); glVertex3f(endWidth, 0, endHeight);
		glTexCoord2f(1.0, 0.0); glVertex3f(0, 0, endHeight);
		// first quarter
		glTexCoord2f(0.0, 0.0); glVertex3f(0, 0, startHeight);
		glTexCoord2f(0.0, 1.0); glVertex3f(endWidth, 0, startHeight);
		glTexCoord2f(1.0, 1.0); glVertex3f(endWidth, 0, 0);
		glTexCoord2f(1.0, 0.0); glVertex3f(0, 0, 0);
		glEnd();
		glDisable(GL_TEXTURE_2D);

		glEnd();
		glDisable(GL_BLEND);
		glPopMatrix();
	}
}

Walls::~Walls() {
	texl.~TexelLoader();
}