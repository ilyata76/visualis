
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

#include "source/fltk/window.hpp"

#define MY_APPLICATION_HPP

int main(int argc, char** argv) {

	Settings* settings = new Settings{ argc, argv };

	windowing(settings);
	
	//delete settings;

	return 0;
}