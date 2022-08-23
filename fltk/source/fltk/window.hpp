#pragma once

#ifndef MY_WINDOW_HPP
#define MY_WINDOW_HPP

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

	#include "source/settings/settings.hpp"

	class MainWindow : public Fl_Window {
		protected:
			Settings* settings;

			Fl_Menu_Item menu_items[100];
			Fl_Menu_Bar* main_menu;

			Fl_Group* resizable_group;

		public:
			MainWindow(int x, int y, int width, int height, const char* label, Settings* settings);
			~MainWindow();

			friend bool windowing(Settings* settings);

		protected:
			static void callbackNewSconfiguration(Fl_Widget* _w, void*);
			static void callbackNewVampireConfiguration(Fl_Widget* _w, void*);

			friend class VampireConfigWindow;

	};

	class VampireConfigWindow : public Fl_Window {

		private:
			Settings* settings;
			Fl_Choice* main_choice;
			Fl_Button* button_folder;
			Fl_Button* button_atoms;
			Fl_Button* button_spins;
			Fl_Button* button_confirm;

		public:
			VampireConfigWindow(int x, int y, int width, int height, const char* label, MainWindow*);
			~VampireConfigWindow();

		protected:
			static void callbackNewFolderVampireConfigurationChoice(Fl_Widget* _w, void* _v);
				static void callbackNewFolderVampireConfigurationButton(Fl_Widget* _w, void* _v);
			
			static void callbackNewFileVampireConfigurationChoice(Fl_Widget* _w, void* _v);
				static void callbackNewAtomsFileVampireConfigurationButton(Fl_Widget* _w, void* _v);
				static void callbackNewSpinsFileVampireConfigurationButton(Fl_Widget* _w, void* _v);

			static void callbackConfirmButton(Fl_Widget* _w, void* _v);
	};

#endif