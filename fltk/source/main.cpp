#include "./source/fltk/application.hpp"
#include "./source/fltk/widgetlist.hpp"

#include <FL/Fl_Button.H>
#include <FL/Fl_Menu.H>
#include <FL/Fl_Menu_.H>
#include <FL/Fl_Box.H>

int main(int argc, char** argv) {

	WidgetList* WL = new WidgetList;
	WL->add(1, new Fl_Button(10, 10, 10, 10, "hello"));
	WL->add(2, new Fl_Button(10, 10, 10, 10, "hello"));
	WL->add(3, new Fl_Button(10, 10, 10, 10, "hello"));
	WL->add(4, new Fl_Box(10, 10, 10, 10, "a"));
	std::wcout << (*WL)[4]->label();
	delete WL;
	return 0;
}