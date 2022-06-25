#pragma once


#ifndef FREEGLUT_DRAWER_HPP
#define FREEGLUT_DRAWER_HPP

	#include "../settings/settings.hpp"
	#include "../libraries/freeglut/include/GL/freeglut.h"
	#include "../vertex-shape/shape.hpp"

	void draw_sample(Settings& _settings, std::vector<Vertex>& _vct, int argc, char** argv);
	void display_mainwindow();
	void draw_shape(int index);
	void reshape_mainwindow(int w, int h);

#endif // !FREEGLUT_DRAWER_HPP
