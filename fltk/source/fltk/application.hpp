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

	constexpr int WIDGET_CHOICE_BUTTON = 200;
	constexpr int WIDGET_BUTTON_PICK_FOLDER = 201;
	constexpr int WIDGET_BUTTON_PICK_ATOMS_FILE = 202;
	constexpr int WIDGET_BUTTON_PICK_SPINS_FILE = 203;
	constexpr int WIDGET_BUTTON_CONFIRM = 204; // TODO: вынести выше

	constexpr char PATH_PLUG[] = "none";

	class Settings {
		protected:
			int argc;
			char** argv;

			int width; // ширина окна
			int height; // высотка окна
			int gap; // gap, который будет отделять glut окно от границ обычного

			bool ready_to_visualization;

			std::string path_to_folder;

			std::string path_to_sconfiguration_file;

			std::string path_to_spins_file;

			std::string path_to_atoms_file;

		public:
			Settings();
			Settings(int argc, char** argv);
			~Settings();

		friend struct Data;

		friend bool create_main_menu(Data* data);
			friend void callback_file_new_sconfiguration(Fl_Widget* _w, void*);
			friend void callback_file_new_vampire_configuration(Fl_Widget* _w, void*);
			
			friend void callback_confirm(Fl_Widget* _w, void* _v);

		friend void choice_callback_folder(Fl_Widget* _w, void*);
			friend void callback_choice_folder_new(Fl_Widget* _w, void*);
		friend void choice_callback_file(Fl_Widget* _w, void*);
			friend void callback_choice_atoms_new(Fl_Widget* _w, void*);
			friend void callback_choice_spins_new(Fl_Widget* _w, void*);

		friend bool windowing(Data* data);
	};

	struct Data {
		WidgetList* widgetlist;
		std::list<std::string>* log;
		Settings* settings;
		void* VOID;

		Data();
		Data(std::list<std::string>* _log, Settings* _settings);

		~Data();
	};

	void log(std::string _str, std::list<std::string>* log, bool full = false);

	struct Windata {
		Data* data;
		WidgetList* widgets;
		Fl_Window* window;

		Windata(Data* _d, WidgetList* _ws, Fl_Window* _w) : data(_d), widgets(_ws), window(_w) {};
	};

#endif // !MY_APPLICATION_HPP
