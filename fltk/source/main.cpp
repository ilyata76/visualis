
#include "./source/fltk/application.hpp"
#include "./source/fltk/widgetlist.hpp"

#include <FL/Fl_Button.H>
#include <FL/Fl_Menu.H>
#include <FL/Fl_Menu_.H>
#include <FL/Fl_Box.H>

#include <vector>

#include <source/libraries/exceptio/src/assert.hpp>
#include <source/libraries/exceptio/src/assert_3rd.hpp>
#include <source/libraries/exceptio/src/exceptio.hpp>

int main(int argc, char** argv) {

	Data* data = new Data{ new std::list<std::string>, new Settings{argc, argv} };

	windowing(data);
	
	data->~Data(); // деструктор сам удалит лог и stg

	return 0;
}