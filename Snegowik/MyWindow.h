#ifndef MYWINDOW_H_
#define MYWINDOW_H_

#include "Window.h"

class MyWindow: public Window
{
public:
	static constexpr int WINDOW_WIDTH  = 1024;
	static constexpr int WINDOW_HEIGHT = 720;

	virtual void update() override;
	virtual void render() override;
	virtual void setupGL() override;

protected:
	double seconds { 0.0 };
	double hours   { 0.0 };
	double minutes { 0.0 };

	void draw_clock();

public:
	MyWindow();
	virtual ~MyWindow() = default;



};

#endif /* MYWINDOW_H_ */
