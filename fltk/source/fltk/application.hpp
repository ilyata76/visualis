#pragma once

#ifndef MY_APPLICATION_HPP
#define MY_APPLICATION_HPP

	#include <FL/Fl.H>
	#include <FL/Fl_Window.H>
	#include <FL/Fl_Menu.H>
	#include <FL/Fl_Menu_Bar.H>
	#include <FL/Fl_Double_Window.H>
	#include <FL/Fl_Group.H>
	#include <FL/Fl_Box.H>
	
	#include <FL/forms.H> // боксы

#include <FL/Fl_Native_File_Chooser.H>

	#include <source/fltk/widgetlist.hpp>

	#include <vector>
	#include <string>
	#include <list>

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


		friend bool create_main_menu(Settings* _settings, std::list<std::string>* log);
			friend void callback_file_new_sconfiguration(Fl_Widget* _w, void*);
			friend void callback_file_new_vampire_configuration_folder(Fl_Widget* _w, void*);
			friend void callback_file_new_vampire_configuration_file(Fl_Widget* _w, void*);

		friend bool windowing(Settings* _settings, std::list<std::string>* log);
	};

	void log(std::string _str, std::list<std::string>* log, bool full = false);

#endif // !MY_APPLICATION_HPP
