#include "application.hpp"

WidgetList widgetlist = {};

std::list<std::string>* global_log;

void callback(Fl_Widget* _w, void*) {
	log("sconfiguration?", global_log, true);
}

Fl_Menu_Item menu_items[] = {
	{"&File", FL_CTRL + 'f'/*hotkey*/, 0/*callback fun*/, 0, FL_SUBMENU/*flags*/},
		{"&new", FL_CTRL + 'n', 0, 0, FL_SUBMENU},
			{"s&configuration ", FL_CTRL + 'c', callback, 0, 0}, /*вызвать поиск файла*/
			{"&vampire configuration ", FL_CTRL + 'v', 0, 0, 0},  /*вызвать новое окно в котором будут поля или выбрать папку*/
			{}, /*больше не submenu*/
		{"&settings", FL_CTRL + 's', 0, 0, FL_SUBMENU},
			{"&save", FL_CTRL + 's', 0, 0, 0},  /*вызвать поиск папки*/
			{"&get", FL_CTRL + 'g', 0, 0, 0}, /*вызвать поиск файла*/
			{},
		{"save &log", FL_CTRL + 'l', 0, 0, 0},
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

bool create_main_menu(Settings* _settings, std::list<std::string>* _log) {
	if (widgetlist.add(WIDGET_MAIN_MENU, new Fl_Menu_Bar{ -1, -1, _settings->width + 2, 25, "main_menu" })) {
		Fl_Menu_Bar* menu = static_cast<Fl_Menu_Bar*>(widgetlist[WIDGET_MAIN_MENU]);
		menu->menu(menu_items);
		return true;
	}
	else return false;
}

bool windowing(Settings* _settings, std::list<std::string>* _log) {
	global_log = _log;

	_settings->width = Fl::w() / 2;
	_settings->height = Fl::h() / 2;

	if (!create_main_menu(_settings, _log)) throw std::exception("[]create_main_menu doesnt work correctly");

	Fl_Window* main_window = new Fl_Window{ 0, 0,  _settings->width, _settings->height, "main_window"};
	Fl_Box* box = new Fl_Box(10, 10, 10, 10, "abobus");

	main_window->add(widgetlist[WIDGET_MAIN_MENU]); 
		widgetlist.set_tied(WIDGET_MAIN_MENU);
		// widgetlist.set_untied(WIDGET_MAIN_MENU); будет крашить, что верно!

	main_window->end();

	Fl_Group* resble = new Fl_Group{ 0, widgetlist[WIDGET_MAIN_MENU]->h(), 
									widgetlist[WIDGET_MAIN_MENU]->w(), main_window->h() - widgetlist[WIDGET_MAIN_MENU]->h() 
									};

	main_window->resizable(resble); /*задали изменяемую область resble, не задевающую меню*/
	
	main_window->show(_settings->argc, _settings->argv);
	
	Fl::run();

	delete resble;
	delete main_window;
	
	return true;
}

void log(std::string _str, std::list<std::string>* _log, bool _full) {
	if (_full) _log->push_back(_str);
	std::cout << _str << '\n';
}

