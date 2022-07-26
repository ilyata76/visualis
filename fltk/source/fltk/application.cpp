#include "application.hpp"



Settings::Settings() {
	
	this->argc = 0;
	this->argv = {};

	this->width = 300;
	this->height = 300;
	this->gap = 5;

}

Settings::Settings(int argc, char** argv) {
	this->argc = argc;
	this->argv = argv;

	this->width = 300;
	this->height = 300;
	this->gap = 5;

}

Settings::~Settings() {
	//
}

bool windowing(Settings* _settings) {

	WidgetList widgetlist = {};

	widgetlist.add(WIDGET_MAIN_MENU, new Fl_Menu_Bar{ 0, 0, 30, 100 / 10, "label" });
	widgetlist.add(11, new Fl_Menu_Bar{ 0, 0, 30, 100 / 10, "label" });

	Fl_Window* main_window = new Fl_Window{ _settings->width, _settings->height };

	main_window->add(widgetlist[WIDGET_MAIN_MENU]); 
		widgetlist.set_tied(WIDGET_MAIN_MENU);

	std::cout << widgetlist[WIDGET_MAIN_MENU]->label();
	main_window->end();
	main_window->show(_settings->argc, _settings->argv);

	Fl::run();

	delete main_window;
	return true;
}

