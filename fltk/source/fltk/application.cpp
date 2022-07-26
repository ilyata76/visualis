#include "application.hpp"

Settings::Settings() {
	
	this->argc = 0;
	this->argv = {};

	this->width = 300;
	this->height = 300;
	this->gap = 5;

}

Settings::Settings(int argc, char** argv) {
	this->argc = 0;
	this->argv = {};

	this->width = 300;
	this->height = 300;
	this->gap = 5;
}

Settings::~Settings() {
	//
}
#include <iostream>
bool windowing(Settings* _settings) {
	Fl_Window* main_window = new Fl_Window(_settings->width, _settings->height);

	main_window->end();
	main_window->show(_settings->argc, _settings->argv);

	Fl::run();
	std::wcout << L"abobus\n";
	delete main_window;
	return true;
}

