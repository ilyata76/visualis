
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

	WidgetList* WL = new WidgetList;
	Fl_Button* a = new Fl_Button{ 10, 10, 10, 10, "hello" };
	WL->add(1, a);
	//delete a;
	//WL->add(3, new Fl_Button(10, 10, 10, 10, "hello"));
	//WL->add(4, new Fl_Box(10, 10, 10, 10, "a"));
	if ((*WL)[1] != nullptr) std::wcout << (*WL)[1]->label();
	
	Settings* stg = new Settings{argc, argv};
	windowing(stg);
	delete stg;
	delete a;
	delete WL;
	return 0;
}