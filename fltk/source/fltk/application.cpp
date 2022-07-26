#include "application.hpp"

WidgetList widgetlist = {};

Fl_Menu_Item menu_items[] = {
	{"&File", FL_CTRL + 'f'/*hotkey*/, 0/*callback fun*/, 0, FL_SUBMENU/*flags*/},
		{"&new", FL_CTRL + 'n', 0, 0, FL_SUBMENU},
			{"s&configuration ", FL_CTRL + 'c', 0, 0, 0}, /*вызвать поиск файла*/
			{"&vampire configuration ", FL_CTRL + 'v', 0, 0, 0},  /*вызвать новое окно в котором будут поля или выбрать папку*/
			{}, /*больше не submenu*/
		{"&settings", FL_CTRL + 's', 0, 0, FL_SUBMENU},
			{"&save", FL_CTRL + 's', 0, 0, 0},  /*вызвать поиск папки*/
			{"&get", FL_CTRL + 'g', 0, 0, 0}, /*вызвать поиск файла*/
			{},
		{"&reset", FL_CTRL + 'r', 0, 0, 0},
		{"&exit", FL_CTRL + 'e', 0, 0, 0},
		{}, /*больше не submenu*/
	{"&Settings", FL_CTRL + 's', 0, 0, 0}, /*здесь всё в подменю будет в том числе мод multimaterial, multilayer и пр. и цвет вообще всё*/
	{"View", 0, 0, 0, 0}, /*оси*/
	{"Run", 0, 0, 0, FL_MENU_INACTIVE},
	{"Help", 0, 0, 0, 0},
};

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

bool create_main_menu(Settings* _settings) {
	if (widgetlist.add(WIDGET_MAIN_MENU, new Fl_Menu_Bar{ -1, -1, _settings->width + 2, _settings->height / 10, "main_menu" })) {
		Fl_Menu_Bar* menu = static_cast<Fl_Menu_Bar*>(widgetlist[WIDGET_MAIN_MENU]);
		menu->menu(menu_items);
		return true;
	}
	else return false;
}

bool windowing(Settings* _settings) {

	if (!create_main_menu(_settings)) throw std::exception("[]create_main_menu doesnt work correctly");

	Fl_Window* main_window = new Fl_Window{ _settings->width, _settings->height };

	main_window->add(widgetlist[WIDGET_MAIN_MENU]); 
		widgetlist.set_tied(WIDGET_MAIN_MENU);
		// widgetlist.set_untied(WIDGET_MAIN_MENU); будет крашить, что верно!

	main_window->end();
	main_window->show(_settings->argc, _settings->argv);

	Fl::run();

	delete main_window;
	
	return true;
}

