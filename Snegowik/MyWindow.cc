#include "MyWindow.h"
#include <cmath>
#include <chrono>
#include <ctime>

MyWindow::MyWindow()
: Window(WINDOW_WIDTH, WINDOW_HEIGHT)
{
	SDL_SetWindowTitle(_window.get(), "My OpenGL Window");

}

void MyWindow::draw_clock()
{
	for (double a = 0.0; a < 360.0; a += 360.0 / 12.0) {
		glPushMatrix();
		glRotated(a, 0.0, 0.0, 1.0);
		glTranslated(0.0, 0.9, 0.0);
		glBegin(GL_QUADS);
		glColor3d(0.3, 1.0, 1.0);
		glVertex2d(-0.03,  0.06);
		glVertex2d( 0.03,  0.06);
		glVertex2d( 0.03, -0.06);
		glVertex2d(-0.03, -0.06);
		glEnd();
		glPopMatrix();
	}
	for (double a = 0.0; a < 360.0; a += 360.0 / 60.0) {
		glPushMatrix();
		glRotated(a, 0.0, 0.0, 0.5);
		glTranslated(0.0, 0.9, 0.0);
		glBegin(GL_QUADS);
		glColor3d(0.3, 1.0, 1.0);
		glVertex2d(-0.01,  0.06);
		glVertex2d( 0.01,  0.06);
		glVertex2d( 0.01, -0.03);
		glVertex2d(-0.01, -0.03);
		glEnd();
		glPopMatrix();
	}
	glPushMatrix();

	double seconds_angle = fmod(seconds, 60.0) / 60.0 * 360.0;

	glRotated(seconds_angle, 0.0, 0.0, -1.0);
	glBegin(GL_QUADS);
	glColor3d(1.0, 0.0, 0.0);
	glVertex3d( 0.0,   0.0, 0.0);
	glVertex3d(-0.025, 0.1, 0.0);
	glVertex3d( 0.0,   0.9, 0.0);
	glVertex3d( 0.025, 0.1, 0.0);
	glEnd();
	glPopMatrix();

	glPushMatrix();

	double hour_angle=fmod(hours, 12.0) / 12.0 * 360.0;

	glRotated(hour_angle, 0.0, 0.0, -1.0);
	glBegin(GL_QUADS);
	glColor3d(0.0, 1.0, 0.0);
	glVertex3d( 0.0,   0.0, 0.0);
	glVertex3d(-0.050, 0.1, 0.0);
	glVertex3d( 0.0,   0.9, 0.0);
	glVertex3d( 0.050, 0.1, 0.0);
	glEnd();
	glPopMatrix();

	glPushMatrix();

	double minute_angle=fmod(minutes, 60.0) / 60.0 * 360.0;

	glRotated(minute_angle, 0.0, 0.0, -1.0);
	glBegin(GL_QUADS);
	glColor3d(0.0, 1.0, 1.0);
	glVertex3d( 0.0,   0.0, 0.0);
	glVertex3d(-0.050, 0.1, 0.0);
	glVertex3d( 0.0,   0.7, 0.0);
	glVertex3d( 0.050, 0.1, 0.0);
	glEnd();
	glPopMatrix();
}

void MyWindow::render()
{
	static double a = 0.0;
	a += 0.05;

	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

	glLoadIdentity();

	gluLookAt(3.0, 3.0, 2.0, 0.0, 0.0, 0.5, 0.0, 0.0, 1.0);
	glRotated(a, 0.0, 0.0, 1.0);
	glBegin(GL_QUADS);

	glColor3d(0.2, 0.1, 0.1);
		glVertex3d(-1.0,  1.0, 0.0);
		glVertex3d( 1.0,  1.0, 0.0);
		glVertex3d( 1.0, -1.0, 0.0);
		glVertex3d(-1.0, -1.0, 0.0);

	glColor3d(0.2, 0.1, 0.1);
		glVertex3d(-1.0,  1.0, 0.0);
		glVertex3d( 1.0,  1.0, 0.0);
		glVertex3d( 1.0, -1.0, 0.0);
		glVertex3d(-1.0, -1.0, 0.0);

	glColor3d(0, 1, 0);
		glVertex3d( 1.0, -1.0, -0.1);
		glVertex3d( 1.0,  1.0, -0.1);
		glVertex3d( 1.0,  1.0,  0.0);
		glVertex3d( 1.0, -1.0,  0.0);

	glColor3d(0, 1, 0);
		glVertex3d( -1.0, -1.0, -0.1);
		glVertex3d( -1.0,  1.0, -0.1);
		glVertex3d( -1.0,  1.0,  0.0);
		glVertex3d( -1.0, -1.0,  0.0);

	glColor3d(0, 1, 0);
		glVertex3d( -1.0, 1.0, -0.1);
		glVertex3d(  1.0, 1.0, -0.1);
		glVertex3d(  1.0, 1.0,  0.0);
		glVertex3d( -1.0, 1.0,  0.0);

	glColor3d(0, 1, 0);
		glVertex3d(  1.0, -1.0,-0.1);
		glVertex3d( -1.0, -1.0,-0.1);
		glVertex3d( -1.0, -1.0, 0.0);
		glVertex3d(  1.0, -1.0, 0.0);

	glEnd();
	glTranslated(0.0, 0.0, 0.05);
	draw_clock();
}

void MyWindow::setupGL()
{
	glEnable(GL_DEPTH_TEST);
	glClearColor(0.1f, 0.25f, 0.45f, 1.0f);

	double aspect_ratio = double(width())/double(height());
	glMatrixMode(GL_PROJECTION);
	//gluOrtho2D(-aspect_ratio,aspect_ratio,-1,1);

	gluPerspective(45.0, aspect_ratio, 0.1, 20.0);
	glMatrixMode(GL_MODELVIEW);
}

void MyWindow::update()
{
	auto now = std::chrono::high_resolution_clock::now();
	auto tt = std::chrono::high_resolution_clock::to_time_t(now);
	auto local_time = *localtime(&tt);
	seconds = local_time.tm_sec +
			60*local_time.tm_min +
			3600*local_time.tm_hour;
	minutes = (local_time.tm_sec +
			60*local_time.tm_min+
			3600*local_time.tm_hour)/60;
	hours = (local_time.tm_sec +
			60*local_time.tm_min +
			3600*local_time.tm_hour)/3600;
}
