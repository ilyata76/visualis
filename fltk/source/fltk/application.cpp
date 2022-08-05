#include "application.hpp"

WidgetList widgetlist = {};

std::list<std::string>* global_log;

void callback_file_new_sconfiguration(Fl_Widget* _w, void*) {

	log("Sconfiguration callback: ", global_log, true);

	Fl_Native_File_Chooser* chooser = new Fl_Native_File_Chooser{ Fl_Native_File_Chooser::BROWSE_FILE };

	chooser->title("Select the sconfiguration file");
	chooser->directory("/");
	
	switch (chooser->show()) {
		case 1:		log("\t Canceled", global_log, true);													break;
		case -1:	log("\t Error: \n\t" + std::string{ chooser->errmsg() }, global_log, true);				break;
		case 0:		log("\t Selected file: \n\t" + std::string{ chooser->filename() }, global_log, true);	break;
		default:																							break;
	}

	delete chooser;
}

void callback_file_new_vampire_configuration_folder(Fl_Widget* _w, void*) {

	log("Vampire config callback: ", global_log, true);
	Fl_Window* choice_window = new Fl_Window{ 100, 100,  30, 30, "choice_window" };

	choice_window->end();
	choice_window->show();

	choice_window->callback([](Fl_Widget* _w, void* _v) { 	
		Fl_Window* current_window = (Fl_Window*)(_v);
		delete current_window;
	}, (void*)(choice_window)); // вызывается при попытке закрыть окно

}

Fl_Menu_Item menu_items[] = {
	{"&File", FL_CTRL + 'f'/*hotkey*/, 0/*callback fun*/, 0, FL_SUBMENU/*flags*/},
		{"&new", FL_CTRL + 'n', 0, 0, FL_SUBMENU},
			{"s&configuration ", FL_CTRL + 'c', callback_file_new_sconfiguration, 0, 0}, /*вызвать поиск файла*/
			{"&vampire configuration ", FL_CTRL + 'v', 0, 0, FL_SUBMENU},  /*вызвать новое окно в котором будут поля или выбрать папку*/
				{"folder ", FL_CTRL + 'v', callback_file_new_vampire_configuration_folder, 0, 0},  /*вызвать новое окно в котором будут поля или выбрать папку*/
				{},
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
	{"Logging", 0, 0, 0, 0}, /*оси*/
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

	if (!create_main_menu(_settings, _log)) throw std::exception{ "[]create_main_menu doesnt work correctly" };

	Fl_Window* main_window = new Fl_Window{ 100, 100,  _settings->width, _settings->height, "main_window"};
	Fl_Box* box = new Fl_Box{ 10, 10, 10, 10, "abobus" };

	main_window->add(widgetlist[WIDGET_MAIN_MENU]); 
		widgetlist.set_tied(WIDGET_MAIN_MENU);
		fl_set_object_boxtype(widgetlist[WIDGET_MAIN_MENU], FL_FLAT_BOX); // FL_NO_BOX может быть как поверх экрана
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
	widgetlist.~WidgetList();
	
	return true;
}

void log(std::string _str, std::list<std::string>* _log, bool _full) {
	if (_full) _log->push_back(_str);
	std::cout << _str << '\n';
}

