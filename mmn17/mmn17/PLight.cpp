#include "PLight.h"

PLight::PLight(GLenum ln) : color{ 1.0f, 0.554f, 0.554f , 1.0f },
pos{ -1.0, 2.25f, -1.0f , 1.0f },
spread_angle(90.0f),
exponent(1.0f),
light_name(ln),
is_enabled(TRUE)
{}

void PLight::addLight() {
	if(!is_enabled)return;
	glLightfv(light_name, GL_DIFFUSE, color);
	glLightfv(light_name, GL_SPECULAR, color);
	glLightfv(light_name, GL_POSITION, pos);
	glLightf(light_name, GL_SPOT_CUTOFF, spread_angle);
	glLightf(light_name, GL_SPOT_EXPONENT, exponent);
}
void PLight::draw() {
	if (!is_enabled)return;

	glPushMatrix();
	glDisable(GL_LIGHTING);
	glColor4fv(color);
	glutSolidSphere(0.2, 100, 100);
	glEnable(GL_LIGHTING);
	glPopMatrix();
}
void PLight::enable() {
	is_enabled = TRUE;
	glEnable(light_name);
}
void PLight::disable() {
	is_enabled = FALSE;
	glDisable(light_name);
}
