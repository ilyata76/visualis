
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

	std::list<std::string>* log = new std::list<std::string>;

	Settings* stg = new Settings{argc, argv};
	windowing(stg, log);
	
	delete stg;

	return 0;
}