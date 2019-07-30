// include libraries
#include <windows.h>
#include <iostream>
#include <fstream>
#include "imGui/imgui.h"
#include "imGui/imgui_impl_freeglut.h"
#include "imGui/imgui_impl_opengl2.h"
#include <GL/freeglut.h>
// include all graphical object used
#include "Camera.h"
#include "PLight.h"
#include "Elephant.h"
#include "MozFloor.h"
#include "Walls.h"
#include "SLight.h"
#include "Teapot.h"
#include "Ball.h"
#include "Table.h"
// define constants - height\width\title
#define WINWIDTH 1200
#define WINHEIGHT 600
#define POSTOP 80
#define POSLEFT 80
#define FLOOR_SIZE 7
#define TITLE "MMN 17 - Elephant Scene"

// set-up and constructor functions for all graphical components
Camera cam; // basic camera
int isElepView; // value for controling gui-input whether Elephant View is picked or Outside View is picked.
MozFloor mozaique_floor; // constructor for moazaique floor
PLight pl = PLight(GL_LIGHT0); // constructor for first point light
SpotLight sl = SpotLight(GL_LIGHT1); //constructor for second point light
Elephant elephant; // constructor for elephant
GLfloat ambient[4] = { 0.3,0.3,0.3,1.0 }; // ambient base color
Walls walls; // constructor for walls
Teapot tp; // constructor for teapot
Ball basketball; // constructor for basketball
Table table; // constructor for table

bool my_tool_active = TRUE; // whether menu is open or closed
void imGuiMenus() {
	ImGui::Begin(TITLE, &my_tool_active,0);
	// menu for camera
	if (ImGui::CollapsingHeader("Camera")) {
			ImGui::Text("Camera Choice");
			ImGui::RadioButton("Outside view", &isElepView, 0); ImGui::SameLine();
			ImGui::RadioButton("Elephant view", &isElepView, 1);
			ImGui::Text("Camera Positioning");
			ImGui::SliderFloat("pos-x", &cam.position[0], -20.0f, 20.0f);
			ImGui::SliderFloat("pox-y", &cam.position[1], -20.0f, 20.0f);
			ImGui::SliderFloat("pos-z", &cam.position[2], -20.0f, 20.0f);
			ImGui::Text("Camera Target - Look At");
			ImGui::SliderFloat("target-x", &cam.center[0], -20.0f, 20.0f);
			ImGui::SliderFloat("target-y", &cam.center[1], -20.0f, 20.0f);
			ImGui::SliderFloat("target-z", &cam.center[2], -20.0f, 20.0f);
	}
	static bool light_on = TRUE;
	static bool spotlight = TRUE;
	// menu for lights
	if (ImGui::CollapsingHeader("Adjust Ambient Light"))
	{
		ImGui::Text("Ambient Light");
		ImGui::ColorEdit4("Ambient light color", reinterpret_cast<float*>(ambient));
		ImGui::Text("First Point Light");
		ImGui::Checkbox("enable light", &light_on);
		ImGui::Text("Point Light Color");
		ImGui::ColorEdit4("pl color", reinterpret_cast<float*>(&pl.color));
		ImGui::Text("Point Light Positioning");
		ImGui::SliderFloat("pl pos-x", &pl.pos[0], -20.0f, 20.0f);
		ImGui::SliderFloat("pl pos-y", &pl.pos[1], -20.0f, 20.0f);
		ImGui::SliderFloat("pl pos-z", &pl.pos[2], -20.0f, 20.0f);
		ImGui::Text("Point Light Spread Angle");
		ImGui::SliderFloat("pl angle", &pl.spread_angle, 0.0f, 90.0f);
		ImGui::Text("Point Light Illuminance Strength");
		ImGui::SliderFloat("pl illuminance", &pl.exponent, 0.0f, 90.0f);

		ImGui::Text("Second Point Light");
		ImGui::Checkbox("enable spotlight", &spotlight);
		ImGui::Text("Spotlight Color");
		ImGui::ColorEdit3("sl color", reinterpret_cast<float*>(&sl.color));
		ImGui::Text("Spotight Positioning");
		ImGui::SliderFloat("sl pos-x", &sl.position[0], -10.0f, 10.0f);
		ImGui::SliderFloat("sl pos-y", &sl.position[1], -10.0f, 10.0f);
		ImGui::SliderFloat("sl pos-z", &sl.position[2], -10.0f, 10.0f);
		ImGui::Text("Spotlight Target - Look At");
		ImGui::SliderFloat("sl target-x", &sl.target[0], -10.0f, 10.0f);
		ImGui::SliderFloat("sl target-y", &sl.target[1], -10.0f, 10.0f);
		ImGui::SliderFloat("sl target-z", &sl.target[2], -10.0f, 10.0f);
		ImGui::Text("Spotlight Spread Angle");
		ImGui::SliderFloat("sl angle", &sl.cutoff, 0.0f, 90.0f);
		ImGui::Text("Spotight Illuminance Strength");
		ImGui::SliderFloat("sl illuminance", &sl.exponent, 0.0f, 90.0f);
		light_on ? pl.enable() : pl.disable();
		spotlight ? sl.enable() : sl.disable();
	}
	// menu for elephant
	if (ImGui::CollapsingHeader("Elephant")) {
		ImGui::Text("Elephant Head Angle");
		ImGui::SliderFloat("HeadVertical", &elephant.headVerticalAngle, -5.0f, 30.0f);
		ImGui::SliderFloat("HeadHorizontal", &elephant.headHorizontalAngle, -30.0f, 30.0f);
		ImGui::Text("Elephant Tail Angle");
		ImGui::SliderFloat("TailVertical", &elephant.tailVerticalAngle, -5.0f, 5.0f);
		ImGui::SliderFloat("TailHorizontal", &elephant.tailHorizontalAngle, -5.0f, 5.0f);
	}
	if (ImGui::CollapsingHeader("Help")) {
		{
			ImGui::Text("Camera:");
			ImGui::Text("Camera Choice:");
			ImGui::TextWrapped(
				(std::string("Outside view refers to an external camera - watching the scene from the outside.\n\n") +
				std::string("Elephant View switches the camera to watch the scene from the eyes of the elephant.\n\n")).c_str());
			ImGui::TextWrapped(
				(std::string("Controling the Camera from Outside View is done through the Camera section under Camera Positioning & Camera target - look at \n\n")).c_str());
			ImGui::TextWrapped((std::string("Controling the Camera from the elephant view is done through the Elephant section under Elephant Head Angle\n\n\n")).c_str());


			ImGui::Text("Lights section:");
			ImGui::TextWrapped((std::string("The controls in the Light section are controling the Light in the scene, 'pointlight' and 'spotlight' are 2") +
				std::string(" light sources that can be turned on a off by the checkboxes. 'Ambient light color' controls the global ambient light value, ") +
				std::string(" The spotlight controls the spotlight position in space and the spotlight target in space. the pointlight controls the pointlight position in space\n\n")).c_str());


			ImGui::Text("Keyboard control:");
			ImGui::TextWrapped((std::string("Using keyboards arrows allow to move the elephant around the floor.\n\n").c_str()));


			ImGui::Text("Elephant section:");
			ImGui::TextWrapped((std::string("The controls in the Elephant section are controlling the head vertical and horizontal orientaion and the") +
				std::string(" tail vertical and horizontal orientation.")).c_str());			

		}
	}
	if (ImGui::Button("Quit"))
	{
		exit(0);
	}
	ImGui::End();
}
//keyboard events handling
void keyboard(int key, int, int) {
	switch (key) {
	case GLUT_KEY_LEFT:  elephant.nextMove = []() { glRotatef(7, 0, 1, 0); };   break;
	case GLUT_KEY_RIGHT: elephant.nextMove = []() { glRotatef(-7, 0, 1, 0); };  break;
	case GLUT_KEY_UP:	 elephant.nextMove = []() { glTranslated(0, 0, -0.2); }; break;
	case GLUT_KEY_DOWN:  elephant.nextMove = []() { glTranslated(0, 0, 0.2); }; break;
	}
	glutPostRedisplay();
}

void drawScene() {
	// set lights
	//set and draw first point light
	glPushMatrix();
	glTranslatef(pl.pos[0], pl.pos[1], pl.pos[2]);
	pl.addLight();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(pl.pos[0], pl.pos[1], pl.pos[2]);
	pl.draw();
	glPopMatrix();
	// set and draw second point light
	glPushMatrix();
	glTranslatef(sl.position[0], sl.position[1], sl.position[2]);
	sl.addlight();
	glPopMatrix();
	glPushMatrix();
	glTranslatef(sl.position[0], sl.position[1], sl.position[2]);
	sl.draw();
	glPopMatrix();

	//draw elephant
	glPushMatrix();
	glMultMatrixf(elephant.local);
	elephant.draw();
	glPopMatrix();
	// draw teapot
	glPushMatrix();
	glTranslatef(-3.0f, -7.25f, -5.0f);
	tp.draw();
	glPopMatrix();
	//draw table
	glPushMatrix();
	glTranslated(-5, -6, -10);
	glScalef(2, 2, 2 );
	table.draw();
	glPopMatrix();
	// draw floor
	glPushMatrix();
	glNormal3d(0, 1, 0);
	glTranslatef(0, -8.0f, -8.0f);
	mozaique_floor.draw(12);
	glPopMatrix();
	walls.draw({ 0,1,2 }, 12,8);
	// set and draw basketball
	glPushMatrix();
	glMultMatrixf(basketball.local);
	basketball.draw();
	glPopMatrix();
}
void display() {
	ImGuiIO& io = ImGui::GetIO();
	//Sets viewport as window size (Normalized Coordinates -> Window Coordinates)
	glViewport(0, 0, (GLsizei)io.DisplaySize.x, (GLsizei)io.DisplaySize.y);
	// set background colors
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
	//prepare for projection operations on matrix stack
	glMatrixMode(GL_PROJECTION);
	// Load I Matrix
	glLoadIdentity();
	// Sets perspective frustum volume viewing matrix.
	// (fov-Angle, aspect, zNear, zFar)
	// We set here a frustum volume between 1.0 to 150.0
	// while debug use zNear as 0.00001 and zFar as 1000000.0. (opengl recommendations)
	gluPerspective(45.0, io.DisplaySize.x / io.DisplaySize.y, 1, 150.0);
	//prepare for modelview operations on matrix stack
	glMatrixMode(GL_MODELVIEW);
	// load I matrix
	glLoadIdentity();

	//update the elephant's transformation matrix
	if (elephant.nextMove) {
		// this is done in order to prevent infinte-loop of movement
		elephant.isMoving = true;
		GLfloat viewModelMatrix[16];
		//get modelview matrix
		glGetFloatv(GL_MODELVIEW_MATRIX, viewModelMatrix);
		// load elephant local location to modelview
		glLoadMatrixf(elephant.local);
		// propogate changes-once on modelview
		elephant.nextMove();
		// reset nextmove to null
		elephant.nextMove = nullptr;
		// set new local location for elephant
		glGetFloatv(GL_MODELVIEW_MATRIX, elephant.local);
		// reload original modelview matrix
		glLoadMatrixf(viewModelMatrix);
	}
	// if elephant view is picked routine
	if (isElepView) {
		GLfloat viewModelMatrix[16];
		// get current location of elephant
		glGetFloatv(GL_MODELVIEW_MATRIX, viewModelMatrix);
		glLoadMatrixf(elephant.local);
		// rotate through current settings of vertical and horizontal angles of the head
		glRotatef(elephant.headVerticalAngle, 1, 0, 0);
		glRotatef(elephant.headHorizontalAngle, 0, 1, 0);
		// rotate 180 degrees in y-axis to locate front of elephant
		glRotatef(180, 0, 1, 0);
		// move a-bit 'up' and a-bit forward to align with the head
		glTranslated(0, 0.75, 2.6);

		GLfloat cameraPose[16];
		// set viewmodel matrix transformations into cameraPose
		glGetFloatv(GL_MODELVIEW_MATRIX, cameraPose);
		// reload original modelview matrix
		glLoadMatrixf(viewModelMatrix);
		// calculate the angle between x-z 
		GLfloat zAngle = atan2(-cameraPose[2], cameraPose[0]);
		// calculate angle between x-y 
		GLfloat yAngle = atan2(-cameraPose[9], cameraPose[5]);
		// apply look at [12,13,14 refer to x,y,z of elephant accordingly]
		gluLookAt(cameraPose[12], cameraPose[13], cameraPose[14],
			sin(zAngle) + cameraPose[12],
			-yAngle + cameraPose[13],
			cos(zAngle) + cameraPose[14],
			0, 1, 0);
	}
	//outside view routine is picked
	else
	{
		gluLookAt(cam.position[0],
			cam.position[1],
			cam.position[2],
			cam.center[0],
			cam.center[1],
			cam.center[2],
			cam.up[0],
			cam.up[1],
			cam.up[2]);
	}

	// set up light model ambient
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambient);

	//draw scene
	drawScene();

	
	// imgui routine for menus
	ImGui_ImplOpenGL2_NewFrame();
	ImGui::NewFrame();
	imGuiMenus();
	// ImGui Render Func
	ImGui::Render();
	// light doesnt work well with imgui menus
	glDisable(GL_LIGHTING);
	ImGui_ImplOpenGL2_RenderDrawData(ImGui::GetDrawData());
	glEnable(GL_LIGHTING);
	//flush and display
	glFlush();
	glutSwapBuffers();
	glutPostRedisplay();
	
}
void main(int argc, char** argv)
{
	//glut normal setup
	glutInit(&argc, argv);
	glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE, GLUT_ACTION_GLUTMAINLOOP_RETURNS);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH | GLUT_MULTISAMPLE);
	glutInitWindowPosition(POSLEFT, POSTOP);
	glutInitWindowSize(WINWIDTH, WINHEIGHT);
	glutCreateWindow(TITLE);
	glutDisplayFunc(display);

	// init Dear ImGui
	ImGui::CreateContext();
	ImGui_ImplFreeGLUT_Init();
	ImGui_ImplFreeGLUT_InstallFuncs();
	ImGui_ImplOpenGL2_Init();
	ImGui::StyleColorsDark();
	//keybaord functions init
	glutSpecialFunc(keyboard);
	// Gaurud Smoothing
	glShadeModel(GL_SMOOTH);
	// enable light
	glEnable(GL_LIGHTING);
	// set up light model
	glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_TRUE);

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_NORMALIZE);
	//set up blending function
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	// init of graphical compnonents
	pl.enable();
	sl.enable();
	walls.init();
	elephant.init();
	basketball.init();
	//glut main loop
	glutMainLoop();

	// imgui Cleanup
	ImGui_ImplOpenGL2_Shutdown();
	ImGui_ImplFreeGLUT_Shutdown();
	ImGui::DestroyContext();

}

