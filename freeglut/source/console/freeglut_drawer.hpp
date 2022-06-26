#pragma once


#ifndef FREEGLUT_DRAWER_HPP
#define FREEGLUT_DRAWER_HPP

	#include "../settings/settings.hpp"
	#include "../libraries/freeglut/include/GL/freeglut.h"
	#include "../vertex-shape/shape.hpp"

	#define MENU_RENDER_MOVEMENTS_BY_ARROWS 1010

	#define MENU_RENDER_MOVEMENTS_BY_ARROWS_SHOW_SENSIVITY 1011
	#define MENU_RENDER_MOVEMENTS_BY_ARROWS_INCREASE_SENSIVITY 1012
	#define MENU_RENDER_MOVEMENTS_BY_ARROWS_DECREASE_SENSIVITY 1013
	#define MENU_RENDER_MOVEMENTS_BY_ARROWS_PRESS_UP 1014
	#define MENU_RENDER_MOVEMENTS_BY_ARROWS_PRESS_DOWN 1015
	#define MENU_RENDER_MOVEMENTS_BY_ARROWS_PRESS_LEFT 1016
	#define MENU_RENDER_MOVEMENTS_BY_ARROWS_PRESS_RIGHT 1017

	#define MENU_RENDER_MOVEMENTS_BY_WASD 1020

	#define MENU_RENDER_MOVEMENTS_BY_WASD_SHOW_SENSIVITY 1021
	#define MENU_RENDER_MOVEMENTS_BY_WASD_INCREASE_SENSIVITY 1022
	#define MENU_RENDER_MOVEMENTS_BY_WASD_DECREASE_SENSIVITY 1023
	#define MENU_RENDER_MOVEMENTS_BY_WASD_PRESS_W 1024
	#define MENU_RENDER_MOVEMENTS_BY_WASD_PRESS_A 1025
	#define MENU_RENDER_MOVEMENTS_BY_WASD_PRESS_S 1026
	#define MENU_RENDER_MOVEMENTS_BY_WASD_PRESS_D 1027

	#define MENU_RENDER_MOVEMENTS_BY_IJKL 1030
	#define MENU_RENDER_MOVEMENTS_BY_IJKL_INCREASE_SENSIVITY 1031
	#define MENU_RENDER_MOVEMENTS_BY_IJKL_DECREASE_SENSIVITY 1032
	#define MENU_RENDER_MOVEMENTS_BY_IJKL_PRESS_I 1033
	#define MENU_RENDER_MOVEMENTS_BY_IJKL_PRESS_J 1034
	#define MENU_RENDER_MOVEMENTS_BY_IJKL_PRESS_K 1035
	#define MENU_RENDER_MOVEMENTS_BY_IJKL_PRESS_L 1036

	#define MENU_RENDER_MOVEMENTS_BY_SHIFTSPACE 1040

	#define MENU_RENDER_MOVEMENTS_BY_SHIFTSPACE_SHOW_SENSIVITY 1041
	#define MENU_RENDER_MOVEMENTS_BY_SHIFTSPACE_INCREASE_SENSIVITY 1042
	#define MENU_RENDER_MOVEMENTS_BY_SHIFTSPACE_DECREASE_SENSIVITY 1043
	#define MENU_RENDER_MOVEMENTS_BY_SHIFTSPACE_PRESS_SHIFT 1044
	#define MENU_RENDER_MOVEMENTS_BY_SHIFTSPACE_PRESS_SPACE 1045

	#define MENU_RENDER_SCALING 1050

	#define MENU_RENDER_SCALING_SHOW_SENSIVITY 1051
	#define MENU_RENDER_SCALING_INCREASE_SENSIVITY 1052
	#define MENU_RENDER_SCALING_DECREASE_SENSIVITY 1053
	#define MENU_RENDER_SCALING_PRESS_PAGE_UP 1054
	#define MENU_RENDER_SCALING_PRESS_PAGE_DOWN 1055

	#define MENU_COLOR_OO 1060

	#define MENU_COLOR_OO_ON 1061
	#define MENU_COLOR_OO_OFF 1062

	#define MENU_SETTINGS_GS 1070

	#define MENU_SETTINGS_GS_SAVE 1071
	#define MENU_SETTINGS_GS_GET 1072
	#define MENU_SETTINGS_GS_RESET 1073
	#define MENU_SETTINGS_GS_RESET_FILE 1074
	#define MENU_SETTINGS_GS_SHOW 1075

	#define MENU_RENDER_INVERT_CONTROL 1080


	#define SUBWINDOW0_MENU_USE_CONES 2001
	#define SUBWINDOW0_MENU_USE_LINES 2002

	void draw_sample(Settings& _settings, std::vector<Vertex>& _vct, int argc, char** argv);
	void display_mainwindow();
	void draw_shape(int index);
	void reshape_mainwindow(int w, int h);
	
	void normal_keys(unsigned char key, int x, int y);
	void special_keys(int key, int x, int y);

	void main_menu_init();
	void main_menu_render(int code);
	void menu_movements_by_arrows(int code);
	void menu_movements_by_wasd(int code);
	void menu_movements_by_ijkl(int code);
	void menu_movements_by_shiftspace(int code);
	void menu_scaling(int code);
	void menu_color(int code);
	void menu_settings(int code);

	//void just_mouse_motion();


	// SUBWINDOWS

	void display_subwindow_0();
	void reshape_subwindow_0(int w, int h);

	void subwindow_0_menu_init();
	void subwindow_0_menu(int code);

	void postRedisplay();


#endif // !FREEGLUT_DRAWER_HPP
