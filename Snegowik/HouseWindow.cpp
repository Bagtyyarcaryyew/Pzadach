#include "HouseWindow.h"
#include <memory>

HouseWindow::HouseWindow()
:Window (WINDOW_WIDTH, WINDOW_HEIGHT),
 _house_model("house_model.txt")
{
	SDL_SetWindowTitle(_window.get(), "House Window");
	SDL_SetRelativeMouseMode(SDL_TRUE);
}

void HouseWindow::update() {
	_angle1 += 0.10;
	_angle2 += 0.10;
	_angle3 += 0.10;
	_angle4 += 0.10;
}

void HouseWindow::render() {

	auto eye = _player.position();
	auto center = _player.center();

	glm::vec3 moon_position  {12.f, 12.f, 60.f};
	glm::vec3 light_position {0.f, 0.f, 0.f};

	glm::vec3 lamp_position   {0.0, 0.0, -0.05};
	glm::vec3 light2_position {0.f, 0.f, 1.f};

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	gluLookAt(eye.x, eye.y, eye.z,
			center.x, center.y, center.z,
			  0.0, 0.0, 1.0);
	//небо
	glPushMatrix();
	glTranslated(eye.x, eye.y, eye.z);
	glDisable(GL_LIGHTING);
	glDisable(GL_FOG);

	Texture::enable();
	_stars.bind();
	draw_sphere(32, 16, 100.0);
	glEnable(GL_LIGHTING);
	glPopMatrix();

	glPushMatrix();
	//луна
	GLfloat white[4] {1.f, 1.f, 1.f, 1.f};
	GLfloat black[4] {0.f, 0.f, 0.f, 1.f};

	glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, white);
	glTranslated(moon_position.x, moon_position.y, moon_position.z);
	glLightfv(GL_LIGHT0, GL_POSITION, &light_position[0]);
	glRotated(-80.0, 0.0f, 1.0f, 0.0f);
	_moon_texture.bind();
	draw_sphere(32, 16, 2.5);
	glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, black);

	glEnable(GL_FOG);
	glPopMatrix();

	Texture::disable();

//	glDisable(GL_LIGHTING);
//	//Рисование skybox, skydome ...
//	glEnable(GL_LIGHTING);

	/*
	 * Хотим:
	 * - Плоскость / кривая поверхность - белого цвета (снег)
	 * - В центре елка. Ствол - цилиндр, ветки - несколько конусов
	 * - Вокруг елки несколько снеговиков: 3 сферы, нос - конус, руки - цилиндры, глаза - сферы и тп
	 */

	glBegin(GL_QUADS);
	glNormal3d(0.0, 0.0, 1.0);
	for (int i = -150; i <150; ++i)
		for (int j = -150; j <150; ++j){
			glVertex3d(i+0, j+0, 0.0);
			glVertex3d(i+1, j+0, 0.0);
			glVertex3d(i+1, j+1, 0.0);
			glVertex3d(i+0, j+1, 0.0);
	}
	glEnd();
	//ёлка
	glPushMatrix();
	glTranslated(10.0, 0.0, 0.7);
	Texture::enable();
	_stvol_texture.bind();
	draw_cylinder(12, 0.5, 7.0);
	glTranslated(0.0, 0.0, 2.5);
	_elka_texture.bind();
	draw_cone(12, 4, 5);
	glTranslated(0.0, 0.0, 3.0);
	_elka_texture.bind();
	draw_cone(12, 3, 4);
	glTranslated(0.0, 0.0, 2.5);
	_elka_texture.bind();
	draw_cone(12, 2, 4);
	glPopMatrix();

//1 снеговик
	glPushMatrix();
	Texture::disable();
	glRotated(_angle1, 0.0, 0.0, 1.0);
	glTranslated(0.0, 0.0, 0.75);
	draw_sphere(16, 10, 1.0);
	glTranslated(0.0, 0.0, 1.25);
	draw_sphere(12, 8, 0.7);
	glTranslated(0.0, 0.0, 0.9);
	draw_sphere(10, 6, 0.4);
	//нос
	Texture::enable();
	_nos.bind();
	glRotated(90.0, 1.0, 1.0, 0.0);
	draw_cone(8, 0.1, 1.0);
	_stvol_texture.bind();
	glTranslated(0.05, 0.0, -0.05);
	glRotated(90.0, 1.0, 0.0, 0.0);
	draw_cylinder(8, 0.07, 1.5);
	_stvol_texture.bind();
	glTranslated(-0.10, 0.0, 0.05);
	glRotated(90.0, 0.0, 1.0, 0.0);
	draw_cylinder(8, 0.07, 1.5);
	_pug_texture.bind();
	glTranslated(-0.4, 0.7, 0.5);
	draw_sphere(10, 6, 0.1);
	_pug_texture.bind();
	glTranslated(-0.3, 0.05, 0.3);
	draw_sphere(10, 6, 0.1);
	_pug_texture.bind();
	glTranslated(1.0, -0.4, -0.7);
	draw_sphere(10, 6, 0.05);
	_pug_texture.bind();
	glTranslated(-0.3, 0.0, -0.3);
	draw_sphere(10, 6, 0.05);
	glPopMatrix();
	Texture::disable();
	//2 снеговик
	glPushMatrix();
	glTranslated(20.0, 0.0, 0.75);
	glRotated(_angle2, 0.0, 0.0, 1.0);
	draw_sphere(16, 10, 1.0);
	glTranslated(0.0, 0.0, 1.25);
	draw_sphere(12, 8, 0.7);
	glTranslated(0.0, 0.0, 0.9);
	draw_sphere(10, 6, 0.4);
	//нос
	Texture::enable();
	_nos.bind();
	glRotated(90.0, 1.0, 1.0, 0.0);
	draw_cone(8, 0.1, 1.0);
	_stvol_texture.bind();
	glTranslated(0.05, 0.0, -0.05);
	glRotated(90.0, 1.0, 0.0, 0.0);
	draw_cylinder(8, 0.07, 1.5);
	_stvol_texture.bind();
	glTranslated(-0.10, 0.0, 0.05);
	glRotated(90.0, 0.0, 1.0, 0.0);
	draw_cylinder(8, 0.07, 1.5);
	_pug_texture.bind();
	glTranslated(-0.4, 0.7, 0.5);
	draw_sphere(10, 6, 0.1);
	_pug_texture.bind();
	glTranslated(-0.3, 0.05, 0.3);
	draw_sphere(10, 6, 0.1);
	_pug_texture.bind();
	glTranslated(1.0, -0.4, -0.7);
	draw_sphere(10, 6, 0.05);
	_pug_texture.bind();
	glTranslated(-0.3, 0.0, -0.3);
	draw_sphere(10, 6, 0.05);
	glPopMatrix();
	Texture::disable();
	//3 снеговик
	glPushMatrix();
	glTranslated(10.0, 10.0, 0.75);
	glRotated(_angle3, 0.0, 0.0, 1.0);
	draw_sphere(16, 10, 1.0);
	glTranslated(0.0, 0.0, 1.25);
	draw_sphere(12, 8, 0.7);
	glTranslated(0.0, 0.0, 0.9);
	draw_sphere(10, 6, 0.4);
	//нос
	Texture::enable();
	_nos.bind();
	glRotated(90.0, 1.0, 1.0, 0.0);
	draw_cone(8, 0.1, 1.0);
	_stvol_texture.bind();
	glTranslated(0.05, 0.0, -0.05);
	glRotated(90.0, 1.0, 0.0, 0.0);
	draw_cylinder(8, 0.07, 1.5);
	_stvol_texture.bind();
	glTranslated(-0.10, 0.0, 0.05);
	glRotated(90.0, 0.0, 1.0, 0.0);
	draw_cylinder(8, 0.07, 1.5);
	_pug_texture.bind();
	glTranslated(-0.4, 0.7, 0.5);
	draw_sphere(10, 6, 0.1);
	_pug_texture.bind();
	glTranslated(-0.3, 0.05, 0.3);
	draw_sphere(10, 6, 0.1);
	_pug_texture.bind();
	glTranslated(1.0, -0.4, -0.7);
	draw_sphere(10, 6, 0.05);
	_pug_texture.bind();
	glTranslated(-0.3, 0.0, -0.3);
	draw_sphere(10, 6, 0.05);
	glPopMatrix();
	Texture::disable();
	//4 снеговик
	glPushMatrix();
	glTranslated(10.0, -10.0, 0.75);
	glRotated(_angle3, 0.0, 0.0, 1.0);
	draw_sphere(16, 10, 1.0);
	glTranslated(0.0, 0.0, 1.25);
	draw_sphere(12, 8, 0.7);
	glTranslated(0.0, 0.0, 0.9);
	draw_sphere(10, 6, 0.4);
	//нос
	Texture::enable();
	_nos.bind();
	glRotated(90.0, 1.0, 1.0, 0.0);
	draw_cone(8, 0.1, 1.0);
	glTranslated(0.05, 0.0, -0.05);
	glRotated(90.0, 1.0, 0.0, 0.0);
	_stvol_texture.bind();
	draw_cylinder(8, 0.07, 1.5);
	glTranslated(-0.10, 0.0, 0.05);
	glRotated(90.0, 0.0, 1.0, 0.0);
	_stvol_texture.bind();
	draw_cylinder(8, 0.07, 1.5);
	_pug_texture.bind();
	glTranslated(-0.4, 0.7, 0.5);
	draw_sphere(10, 6, 0.1);
	_pug_texture.bind();
	glTranslated(-0.3, 0.05, 0.3);
	draw_sphere(10, 6, 0.1);
	_pug_texture.bind();
	glTranslated(1.0, -0.4, -0.7);
	draw_sphere(10, 6, 0.05);
	_pug_texture.bind();
	glTranslated(-0.3, 0.0, -0.3);
	draw_sphere(10, 6, 0.05);
	glPopMatrix();

    //дома
	glPushMatrix();
	glTranslated(10.0, 20.0, 0.0);
	glRotated(90.0, 0.0, 0.0, 1.0);
	_house_texture.bind();
	_house_model.draw();
	glTranslated(-40.0, 0.0, 0.0);
	glRotated(180.0, 0.0, 0.0, 1.0);
	_house_texture.bind();
	_house_model.draw();
	glTranslated(-20.0, 20.0, 0.0);
	glRotated(-90.0, 0.0, 0.0, 1.0);
	_house_texture.bind();
	_house_model.draw();
	glTranslated(40.0, 0.0, 0.0);
	glRotated(-180.0, 0.0, 0.0, 1.0);
	_house_texture.bind();
	_house_model.draw();
	glPopMatrix();

	GLfloat light1_diffuse[] = {0.9, 0.5, 0.0};
	GLfloat light1_position[] = {0.0, 0.0, 1.0, 1.0};
	GLfloat light1_spot_direction[] = {0.0, 0.0, 1.0};
	//фонарь
	glPushMatrix();
	_fonar_texture.bind();
	glTranslated(21.0, 11.0, 0.0);
	glRotated(-45.0, 0.0, 0.0, 1.0);
	draw_cylinder(8, 0.1, 7.0);
	_fonar_texture.bind();
	glTranslated(0.0, 0.0, 6.9);
	glRotated(90.0, 1.0, 0.0, 0.0);
	draw_cylinder(8, 0.1, 3.0);
	_fonar_texture.bind();
	glTranslated(0.0, 0.1, 3.0);
	glRotated(90.0, 1.0, 0.0, 0.0);
	draw_cylinder(8, 0.1, 1.0);
	_fonar2_texture.bind();
	glTranslated(0.0, 0.0, 1.3);

	glEnable(GL_LIGHT1);
	glLightfv(GL_LIGHT1, GL_POSITION, light1_position);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, light1_diffuse);
	glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, light1_spot_direction);
	glLightf(GL_LIGHT1, GL_SPOT_CUTOFF, 60);
	glLightf(GL_LIGHT1, GL_SPOT_EXPONENT, 3.0);

	glRotated(180.0, 1.0, 0.0, 0.0);
	draw_cone(8.0, 0.5, 1.0);
	glTranslated(0.0, 0.0, -0.1);
	_lamp_texture.bind();
	draw_sphere(10, 6, 0.1);
	glPopMatrix();
	Texture::disable();

//	_cylinder_texture.bind();
//	_cone_texture.bind();
//	_earth_texture.bind();
//	draw_prism(6, 1, 2);
//	draw_cylinder(12, 1, 2);
//	draw_pyramid(4, 1, 2);
//	draw_cone(12, 1, 2);
//  draw_disco_ball(16, 8, 2.0);
//	draw_sphere(16, 8, 2.0);

}

void HouseWindow::setupGL() {

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_TEXTURE);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_FOG);

	//GLfloat fog_color[4] {0.3f, 0.3f, 0.3f, 1.0f};

	glFogf(GL_FOG_END, 70.f);
	glFogf(GL_FOG_DENSITY, 0.2f);
	glFogi(GL_FOG_MODE, GL_LINEAR);

	//glFogfv(GL_FOG_COLOR, fog_color);

	glClearColor(0.1f, 0.25f, 0.45f, 1.0f);

	double aspect_ratio = double(width()) / double(height());

	glMatrixMode(GL_PROJECTION);
	gluPerspective(45.0, aspect_ratio, 0.1, 120.0);
	glMatrixMode(GL_MODELVIEW);
}

void HouseWindow::handle_event(const SDL_Event &event)
{
	switch(event.type) {
	case SDL_MOUSEMOTION:
		_player.turn_phi   (-event.motion.xrel * Player::TURN_ANGLE);
		_player.turn_theta ( event.motion.yrel * Player::TURN_ANGLE);
		break;
	case SDL_KEYDOWN:
		if (event.key.keysym.scancode == SDL_SCANCODE_F)
			_player.toggle_fly();
		break;
	}
}

void HouseWindow::handle_keys(const Uint8 *keys)
{
	if (keys[SDL_SCANCODE_W]) _player.move_forward();
	if (keys[SDL_SCANCODE_S]) _player.move_backward();
	if (keys[SDL_SCANCODE_A]) _player.move_left();
	if (keys[SDL_SCANCODE_D]) _player.move_right();
}
