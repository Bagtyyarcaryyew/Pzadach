#ifndef HOUSEWINDOW_H_
#define HOUSEWINDOW_H_

#include "Window.h"
#include "Model.h"
#include "Texture.h"
#include "Primitives.h"
#include "Player.h"


class HouseWindow: public Window {
private:
	Model _house_model;
	Texture _house_texture {"Houses.png"};
	Texture _stars {"stars.jpg"};
	Texture _stvol_texture {"stvol.jpg"};
	Texture _elka_texture {"elka.png"};
	Texture _moon_texture {"moon.jpg"};
	Texture _pug_texture {"pugovki.png"};
	Texture _fonar_texture {"stolb.png"};
	Texture _fonar2_texture {"fonar.png"};
	Texture _lamp_texture {"lamp.png"};
	Texture _nos {"morkovka.png"};

	double _angle1 = 0.0;
	double _angle2 = 0.0;
	double _angle3 = 0.0;
	double _angle4 = 0.0;

	Player _player {glm::vec3(3.f, 3.f, 3.0f), 0.f, 1.6f};
public:
	static constexpr int WINDOW_WIDTH = 1024;
	static constexpr int WINDOW_HEIGHT = 720;

	virtual void handle_event(const SDL_Event &event);
	virtual void handle_keys(const Uint8 *keys);
	virtual void update() override;
	virtual void render() override;
	virtual void setupGL() override;

public:
	HouseWindow();
	virtual ~HouseWindow() = default;
};

#endif /* HOUSEWINDOW_H_ */
