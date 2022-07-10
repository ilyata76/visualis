#pragma once


#ifndef FREEGLUT_DRAWER_HPP
#define FREEGLUT_DRAWER_HPP

	#include "../settings/settings.hpp"
	#include "../libraries/freeglut/include/GL/freeglut.h"
	#include "../vertex-shape/shape.hpp"

	#include <wchar.h>
	#include <ctime>


	constexpr auto MENU_RENDER_MOVEMENTS_BY_ARROWS = 1010;

	constexpr auto MENU_RENDER_MOVEMENTS_BY_ARROWS_SHOW_SENSIVITY = 1011;
	constexpr auto MENU_RENDER_MOVEMENTS_BY_ARROWS_INCREASE_SENSIVITY = 1012;
	constexpr auto MENU_RENDER_MOVEMENTS_BY_ARROWS_DECREASE_SENSIVITY = 1013;
	constexpr auto MENU_RENDER_MOVEMENTS_BY_ARROWS_PRESS_UP = 1014;
	constexpr auto MENU_RENDER_MOVEMENTS_BY_ARROWS_PRESS_DOWN = 1015;
	constexpr auto MENU_RENDER_MOVEMENTS_BY_ARROWS_PRESS_LEFT = 1016;
	constexpr auto MENU_RENDER_MOVEMENTS_BY_ARROWS_PRESS_RIGHT = 1017;

	constexpr auto MENU_RENDER_MOVEMENTS_BY_WASD = 1020;

	constexpr auto MENU_RENDER_MOVEMENTS_BY_WASD_SHOW_SENSIVITY = 1021;
	constexpr auto MENU_RENDER_MOVEMENTS_BY_WASD_INCREASE_SENSIVITY = 1022;
	constexpr auto MENU_RENDER_MOVEMENTS_BY_WASD_DECREASE_SENSIVITY = 1023;
	constexpr auto MENU_RENDER_MOVEMENTS_BY_WASD_PRESS_W = 1024;
	constexpr auto MENU_RENDER_MOVEMENTS_BY_WASD_PRESS_A = 1025;
	constexpr auto MENU_RENDER_MOVEMENTS_BY_WASD_PRESS_S = 1026;
	constexpr auto MENU_RENDER_MOVEMENTS_BY_WASD_PRESS_D = 1027;

	constexpr auto MENU_RENDER_MOVEMENTS_BY_IJKL = 1030;
	constexpr auto MENU_RENDER_MOVEMENTS_BY_IJKL_INCREASE_SENSIVITY = 1031;
	constexpr auto MENU_RENDER_MOVEMENTS_BY_IJKL_DECREASE_SENSIVITY = 1032;
	constexpr auto MENU_RENDER_MOVEMENTS_BY_IJKL_PRESS_I = 1033;
	constexpr auto MENU_RENDER_MOVEMENTS_BY_IJKL_PRESS_J = 1034;
	constexpr auto MENU_RENDER_MOVEMENTS_BY_IJKL_PRESS_K = 1035;
	constexpr auto MENU_RENDER_MOVEMENTS_BY_IJKL_PRESS_L = 1036;

	constexpr auto MENU_RENDER_MOVEMENTS_BY_SHIFTSPACE = 1040;

	constexpr auto MENU_RENDER_MOVEMENTS_BY_SHIFTSPACE_SHOW_SENSIVITY = 1041;
	constexpr auto MENU_RENDER_MOVEMENTS_BY_SHIFTSPACE_INCREASE_SENSIVITY = 1042;
	constexpr auto MENU_RENDER_MOVEMENTS_BY_SHIFTSPACE_DECREASE_SENSIVITY = 1043;
	constexpr auto MENU_RENDER_MOVEMENTS_BY_SHIFTSPACE_PRESS_SHIFT = 1044;
	constexpr auto MENU_RENDER_MOVEMENTS_BY_SHIFTSPACE_PRESS_SPACE = 1045;

	constexpr auto MENU_RENDER_SCALING = 1050;

	constexpr auto MENU_RENDER_SCALING_SHOW_SENSIVITY = 1051;
	constexpr auto MENU_RENDER_SCALING_INCREASE_SENSIVITY = 1052;
	constexpr auto MENU_RENDER_SCALING_DECREASE_SENSIVITY = 1053;
	constexpr auto MENU_RENDER_SCALING_PRESS_PAGE_UP = 1054;
	constexpr auto MENU_RENDER_SCALING_PRESS_PAGE_DOWN = 1055;

	constexpr auto MENU_COLOR_OO = 1060;

	constexpr auto MENU_COLOR_OO_ON = 1061;
	constexpr auto MENU_COLOR_OO_OFF = 1062;

	constexpr auto MENU_SETTINGS_GS = 1070;

	constexpr auto MENU_SETTINGS_GS_SAVE = 1071;
	constexpr auto MENU_SETTINGS_GS_GET = 1072;
	constexpr auto MENU_SETTINGS_GS_RESET = 1073;
	constexpr auto MENU_SETTINGS_GS_RESET_FILE = 1074;
	constexpr auto MENU_SETTINGS_GS_SHOW = 1075;

	constexpr auto MENU_RENDER_INVERT_CONTROL = 1080;
	constexpr auto MENU_RENDER_RESTORE_GAP = 1081;

	constexpr auto MENU_RENDER_SPINRATE_10k = 1090;
	constexpr auto MENU_RENDER_SPINRATE_5k = 1191;
	constexpr auto MENU_RENDER_SPINRATE_1 = 1091;
	constexpr auto MENU_RENDER_SPINRATE_2 = 1092;
	constexpr auto MENU_RENDER_SPINRATE_3 = 1093;
	constexpr auto MENU_RENDER_SPINRATE_4 = 1094;
	constexpr auto MENU_RENDER_SPINRATE_5 = 1095;
	constexpr auto MENU_RENDER_SPINRATE_6 = 1096;
	constexpr auto MENU_RENDER_SPINRATE_7 = 1097;
	constexpr auto MENU_RENDER_SPINRATE_8 = 1098;
	constexpr auto MENU_RENDER_SPINRATE_9 = 1099;
	constexpr auto MENU_RENDER_SPINRATE_10 = 10910;
	constexpr auto MENU_RENDER_SPINRATE_11 = 10911;
	constexpr auto MENU_RENDER_SPINRATE_12 = 10912;
	constexpr auto MENU_RENDER_SPINRATE_13 = 10913;
	constexpr auto MENU_RENDER_SPINRATE_14 = 10914;
	constexpr auto MENU_RENDER_SPINRATE_15 = 10915;
	constexpr auto MENU_RENDER_SPINRATE_16 = 10916;
	constexpr auto MENU_RENDER_SPINRATE_17 = 10917;
	constexpr auto MENU_RENDER_SPINRATE_18 = 10918;
	constexpr auto MENU_RENDER_SPINRATE_19 = 10919;
	constexpr auto MENU_RENDER_SPINRATE_20 = 10920;
	constexpr auto MENU_RENDER_INCREASE_SPINRATE_BY_1 = 10921;
	constexpr auto MENU_RENDER_DECREASE_SPINRATE_BY_1 = 10922;
	constexpr auto MENU_RENDER_SPINRATE_21 = 10923;
	constexpr auto MENU_RENDER_SPINRATE_22 = 10924;
	constexpr auto MENU_RENDER_SPINRATE_23 = 10925;
	constexpr auto MENU_RENDER_SPINRATE_24 = 10926;
	constexpr auto MENU_RENDER_SPINRATE_25 = 10927;
	constexpr auto MENU_RENDER_SPINRATE_26 = 10928;
	constexpr auto MENU_RENDER_SPINRATE_27 = 10929;
	constexpr auto MENU_RENDER_SPINRATE_28 = 10930;
	constexpr auto MENU_RENDER_SPINRATE_29 = 10931;
	constexpr auto MENU_RENDER_SPINRATE_30 = 10932;
	
	constexpr auto MENU_INCREASE_POLYGON_BY_1 = 11901;
	constexpr auto MENU_DECREASE_POLYGON_BY_1 = 11902;
	constexpr auto MENU_SET_POLYGON_5 = 11903;
	constexpr auto MENU_SET_POLYGON_10 = 11904;
	constexpr auto MENU_SET_POLYGON_15 = 11905;
	constexpr auto MENU_SET_POLYGON_20 = 11906;
	
	constexpr auto MENU_COLORING_BACKGROUND = 1100;
	constexpr auto MENU_COLORING_BACKGROUND_WHITE = 1101;
	constexpr auto MENU_COLORING_BACKGROUND_RED = 1102;
	constexpr auto MENU_COLORING_BACKGROUND_GREEN = 1103;
	constexpr auto MENU_COLORING_BACKGROUND_BLUE = 1104;
	constexpr auto MENU_COLORING_BACKGROUND_LIGHTBLUE = 1105;
	constexpr auto MENU_COLORING_BACKGROUND_BLACK = 1106;
	constexpr auto MENU_COLORING_BACKGROUND_LIGHTGREY = 1107;
	constexpr auto MENU_COLORING_BACKGROUND_MAIN = 1108;
	constexpr auto MENU_COLORING_BACKGROUND_SUB0 = 1109;
	constexpr auto MENU_COLORING_BACKGROUND_SUB1 = 1110;
	constexpr auto MENU_COLORING_BACKGROUND_SUB2 = 1111;
	constexpr auto MENU_COLORING_BACKGROUND_SUB3 = 1112;
	
	constexpr auto MENU_RENDER_LIGHTING = 12001;
	constexpr auto MENU_RENDER_MULTILAYER = 12002;
	constexpr auto MENU_RENDER_MULTILAYER_RECALC = 12003;
	constexpr auto MENU_RENDER_MULTIMATERIAL = 12004;
	constexpr auto MENU_RENDER_MULTIMATERIAL_RECALC = 12005;


	constexpr auto SUBWINDOW_AXIS_MENU_USE_CONES = 2001;
	constexpr auto SUBWINDOW_AXIS_MENU_USE_LINES = 2002;
	constexpr auto SUBWINDOW_AXIS_MENU_SHOW_NAMES = 2003;
	constexpr auto SUBWINDOW_AXIS_MENU_HIDE_NAMES = 2004;
	constexpr auto SUBWINDOW_AXIS_MENU_BACGROUND_MAIN = 2005;
	constexpr auto SUBWINDOW_AXIS_MENU_BACGROUND_GREY = 2006;


	constexpr auto MAIN_MENU_GAP = 3001;
	constexpr auto MAIN_MENU_GAP_INCREASE_BY_1 = 3002;
	constexpr auto MAIN_MENU_GAP_DECREASE_BY_1 = 3003;
	constexpr auto MAIN_MENU_GAP_SET_5 = 3004;
	constexpr auto MAIN_MENU_GAP_SET_6 = 3005;
	constexpr auto MAIN_MENU_GAP_SET_7 = 3006;
	constexpr auto MAIN_MENU_GAP_SET_8 = 3007;
	constexpr auto MAIN_MENU_GAP_SET_9 = 3008;
	
	constexpr auto MAIN_MENU_SUBWINDOWS = 3101;
	constexpr auto MAIN_MENU_SUBWINDOWS_DESTROY = 3102;
	constexpr auto MAIN_MENU_SUBWINDOWS_BUILD = 3103;

	constexpr auto FONT_HELVETICA_10 = 4101;
	constexpr auto FONT_HELVETICA_12 = 4102;
	constexpr auto FONT_HELVETICA_18 = 4103;
	constexpr auto FONT_8_BY_13 = 4104;
	constexpr auto FONT_8_BY_15 = 4105;
	constexpr auto FONT_TIMES_ROMAN_10 = 4106;
	constexpr auto FONT_TIMES_ROMAN_24 = 4107;

	constexpr auto MENU_INVERT_BLACK_TEXT_COLOR = 5100;
	constexpr auto CLEAR_LOG = 6100;

	void print_text_3f(double _x, double _y, double _z, std::wstring text, void* FONT);
	void print_text_2f(double _x, double _y, std::wstring text, void* FONT);

	void print_text_3f(double _x, double _y, double _z, std::string text, void* FONT);
	void print_text_2f(double _x, double _y, std::string text, void* FONT);
	

	void create_additional_subwindows();
	void destroy_additional_subwindows();
	void recalculation_subwindows_wh();
	void reshape_reposition_subwindows();
	void postRedisplay();

	void draw_sample(Settings& _settings, std::vector<Vertex>& _vct, int argc, char** argv);

	// WINDOWS

	void display_mainwindow();
	void reshape_mainwindow(int w, int h);

	double distance_between_fonts(void* _font);
	
	void display_subwindow_0();
		void draw_shape(int index);

		void normal_keys(unsigned char key, int x, int y);
		void special_keys(int key, int x, int y);
		void mouse_pressed(int button, int state, int x, int y);
		void passive_mouse_motion(int x, int y);
		void pressed_mouse_motion(int x, int y);
		
	
	void display_subwindow_1();
		void draw_axis_by_cones();
		void draw_axis_by_lines();
	
	void display_subwindow_2();
		void subwindow_2_special_keys(int key, int x, int y);
		void subwindow_2_mouse_pressed(int button, int state, int x, int y);
	
	
	void display_subwindow_3();
		void subwindow_3_special_keys(int key, int x, int y);
		void subwindow_3_mouse_pressed(int button, int state, int x, int y);

	void reshape_subwindow_0(int w, int h);
	void reshape_subwindow_1(int w, int h);
	void reshape_subwindow_2(int w, int h);
	void reshape_subwindow_3(int w, int h);

	void main_menu_init();
		void main_menu(int code);
		void main_menu_gap(int code);
		void main_menu_subwindows(int code);
		void menu_background_main(int code);


	void subwindow_0_menu_init();
		void subwindow_0_menu(int code);
		void menu_movements_by_arrows(int code);
		void menu_movements_by_wasd(int code);
		void menu_movements_by_ijkl(int code);
		void menu_movements_by_shiftspace(int code);
		void menu_scaling(int code);
		void menu_color(int code);
		void menu_settings(int code);
		void menu_spinrate(int code);
			void menu_spinrate_set(int code);
				void menu_spinrate_set_1_10(int code);
				void menu_spinrate_set_11_20(int code);
				void menu_spinrate_set_21_30(int code);
		void menu_shape(int code);
		void menu_polygon(int code);
		void menu_background_sub0(int code);
		void menu_mods(int code);

	void subwindow_1_menu_init();
		void subwindow_1_menu(int code);
		void menu_background_sub1(int code);
		


	void subwindow_2_menu_init();
		void subwindow_2_menu(int code);
		void menu_background_sub2(int code);
		void menu_font_sub2(int code);

	void subwindow_3_menu_init();
		void subwindow_3_menu(int code);
		void menu_background_sub3(int code);
		void menu_font_sub3(int code);

	void log(std::string _str, Rgb _color);
	void log(std::wstring _str);

#endif // !FREEGLUT_DRAWER_HPP
