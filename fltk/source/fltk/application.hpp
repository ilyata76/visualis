#pragma once

#ifndef MY_APPLICATION_HPP
#define MY_APPLICATION_HPP

	#include <FL/Fl.H>
	#include <FL/Fl_Window.H>
	#include <FL/Fl_Menu.H>
	#include <FL/Fl_Menu_Bar.H>

	#include <source/fltk/widgetlist.hpp>

	#include <vector>

	constexpr auto WIDGET_MAIN_MENU = 1000;

	class Settings {
		protected:
			int argc;
			char** argv;

			int width; // ширина окна
			int height; // высотка окна
			int gap; // gap, который будет отделять glut окно от границ обычного

		public:
			Settings();
			Settings(int argc, char** argv);
			~Settings();

		friend bool windowing(Settings* _settings);
	};

	

#endif // !MY_APPLICATION_HPP
