//#include "application.hpp"
//
//Fl_Menu_Item menu_items[100];
//
//void callback_file_new_sconfiguration(Fl_Widget* _w, void* _v) {
//
//	Data* data = (Data*)_v;
//
//	log("Sconfiguration callback: ", data->log, true);
//	log("\t Creating chooser", data->log, true);
//	Fl_Native_File_Chooser* chooser = new Fl_Native_File_Chooser{ Fl_Native_File_Chooser::BROWSE_FILE };
//
//	chooser->title("Select the sconfiguration file");
//	chooser->directory("/");
//
//	switch (chooser->show()) {
//		case 1:		log("\t Canceled", data->log, true);														break;
//		case -1:	log("\t Error: \n\t\t " + std::string{ chooser->errmsg() }, data->log, true);				break;
//		case 0:		log("\t Selected file: \n\t\t " + std::string{ chooser->filename() }, data->log, true);		
//					data->settings->path_to_sconfiguration_file = chooser->filename();
//					data->settings->path_to_atoms_file = PATH_PLUG;
//					data->settings->path_to_spins_file = PATH_PLUG;
//					data->settings->path_to_folder = PATH_PLUG;
//					log("\t Saved filename: \n\t\t " + data->settings->path_to_sconfiguration_file, data->log, true);
//																												break;
//		default:																								break;
//	};
//
//	delete chooser;
//}
//
//void choice_callback_folder(Fl_Widget* _w, void* _v) {
//	Windata* wd = static_cast<Windata*>(_v);
//
//	wd->window->label("FOLDER CHOICE\n");
//	
//	auto* button = static_cast<Fl_Button*>((*wd->widgets)[WIDGET_BUTTON_PICK_FOLDER]);
//		button->show();
//
//	button = static_cast<Fl_Button*>((*wd->widgets)[WIDGET_BUTTON_PICK_ATOMS_FILE]);
//		button->hide();
//
//	button = static_cast<Fl_Button*>((*wd->widgets)[WIDGET_BUTTON_PICK_SPINS_FILE]);
//		button->hide();
//
//	button = static_cast<Fl_Button*>((*wd->widgets)[WIDGET_BUTTON_CONFIRM]);
//		button->hide();
//}
//
//void callback_choice_folder_new(Fl_Widget* _w, void* _v) {
//	
//	Windata* wd = static_cast<Windata*>(_v);
//	
//	log("Choice folder callback: ", wd->data->log, true);
//	log("\t Creating chooser", wd->data->log, true);
//	Fl_Native_File_Chooser* chooser = new Fl_Native_File_Chooser{ Fl_Native_File_Chooser::BROWSE_DIRECTORY };
//
//	chooser->title("Select the vampire-folder");
//	chooser->directory("/");
//
//	switch (chooser->show()) {
//		case 1:		log("\t Canceled", wd->data->log, true);														break;
//		case -1:	log("\t Error: \n\t\t " + std::string{ chooser->errmsg() }, wd->data->log, true);				break;
//		case 0:		log("\t Selected folder: \n\t\t " + std::string{ chooser->filename() }, wd->data->log, true);
//					wd->data->settings->path_to_folder = chooser->filename();
//					wd->data->settings->path_to_atoms_file = PATH_PLUG;
//					wd->data->settings->path_to_spins_file = PATH_PLUG;
//					wd->data->settings->path_to_sconfiguration_file = PATH_PLUG;
//					log("\t Saved directory: \n\t\t " + wd->data->settings->path_to_folder, wd->data->log, true);
//																												break;
//		default:																								break;
//	};
//
//	auto* button = static_cast<Fl_Button*>((*wd->widgets)[WIDGET_BUTTON_CONFIRM]);
//		button->show();
//
//	delete chooser;
//
//}
//
//void choice_callback_file(Fl_Widget* _w, void* _v) {
//	Windata* wd = static_cast<Windata*>(_v);
//
//	wd->window->label("FILE CHOICE\n");
//	
//	auto* button = static_cast<Fl_Button*>((*wd->widgets)[WIDGET_BUTTON_PICK_FOLDER]);
//		button->hide();
//
//	button = static_cast<Fl_Button*>((*wd->widgets)[WIDGET_BUTTON_PICK_ATOMS_FILE]);
//		button->show();
//
//	button = static_cast<Fl_Button*>((*wd->widgets)[WIDGET_BUTTON_PICK_SPINS_FILE]);
//		button->show();
//
//	button = static_cast<Fl_Button*>((*wd->widgets)[WIDGET_BUTTON_CONFIRM]);
//		button->hide();
//}
//
//void callback_choice_atoms_new(Fl_Widget* _w, void* _v) {
//	
//	Windata* wd = static_cast<Windata*>(_v);
//	
//	log("Choice atoms file callback: ", wd->data->log, true);
//	log("\t Creating chooser", wd->data->log, true);
//	Fl_Native_File_Chooser* chooser = new Fl_Native_File_Chooser{ Fl_Native_File_Chooser::BROWSE_FILE };
//
//	chooser->title("Select the atoms file");
//	chooser->directory("/");
//
//	switch (chooser->show()) {
//		case 1:		log("\t Canceled", wd->data->log, true);														break;
//		case -1:	log("\t Error: \n\t\t " + std::string{ chooser->errmsg() }, wd->data->log, true);				break;
//		case 0:		log("\t Selected file: \n\t\t " + std::string{ chooser->filename() }, wd->data->log, true);
//					wd->data->settings->path_to_folder = PATH_PLUG;
//					wd->data->settings->path_to_atoms_file = chooser->filename();
//					//wd->data->settings->path_to_spins_file = PATH_PLUG;
//					wd->data->settings->path_to_sconfiguration_file = PATH_PLUG;
//					log("\t Saved file: \n\t\t " + wd->data->settings->path_to_atoms_file, wd->data->log, true);
//																												break;
//		default:																								break;
//	};
//
//	if (wd->data->settings->path_to_atoms_file != PATH_PLUG && wd->data->settings->path_to_spins_file != PATH_PLUG) {
//		auto* button = static_cast<Fl_Button*>((*wd->widgets)[WIDGET_BUTTON_CONFIRM]);
//			button->show();
//	}
//
//	delete chooser;
//
//}
//
//void callback_choice_spins_new(Fl_Widget* _w, void* _v) {
//	
//	Windata* wd = static_cast<Windata*>(_v);
//	
//	log("Choice spins file callback: ", wd->data->log, true);
//	log("\t Creating chooser", wd->data->log, true);
//	Fl_Native_File_Chooser* chooser = new Fl_Native_File_Chooser{ Fl_Native_File_Chooser::BROWSE_FILE };
//
//	chooser->title("Select the spins file");
//	chooser->directory("/");
//
//	switch (chooser->show()) {
//		case 1:		log("\t Canceled", wd->data->log, true);														break;
//		case -1:	log("\t Error: \n\t\t " + std::string{ chooser->errmsg() }, wd->data->log, true);				break;
//		case 0:		log("\t Selected file: \n\t\t " + std::string{ chooser->filename() }, wd->data->log, true);
//					wd->data->settings->path_to_folder = PATH_PLUG;
//					//wd->data->settings->path_to_atoms_file = PATH_PLUG;
//					wd->data->settings->path_to_spins_file = chooser->filename();
//					wd->data->settings->path_to_sconfiguration_file = PATH_PLUG;
//					log("\t Saved file: \n\t\t " + wd->data->settings->path_to_spins_file, wd->data->log, true);
//																												break;
//		default:																								break;
//	};
//
//	if (wd->data->settings->path_to_atoms_file != PATH_PLUG && wd->data->settings->path_to_spins_file != PATH_PLUG) {
//		auto* button = static_cast<Fl_Button*>((*wd->widgets)[WIDGET_BUTTON_CONFIRM]);
//			button->show();
//	}
//
//	delete chooser;
//
//}
//
//void callback_file_new_vampire_configuration(Fl_Widget* _w, void* _v) {
//
//	Data* data = (Data*)_v;
//
//	WidgetList* widgets = new WidgetList;
//
//	const int gappy = 10;
//	const int button_height = 25;
//	const int distance = button_height + gappy;
//
//	log("Vampire config callback: ", data->log, true);
//	log("\t Creating choice_window", data->log, true);
//	
//	Fl_Window* choice_window = new Fl_Window{ 100, 100, 200, 200, "choice_window" };
//
//	Windata* fulldata = new Windata{ data, widgets, choice_window };
//
//	widgets->add(WIDGET_CHOICE_BUTTON, new Fl_Choice{ gappy, gappy, 200 - 2 * gappy, button_height, "CHOICE" });
//	widgets->add(WIDGET_BUTTON_PICK_FOLDER, new Fl_Button{ gappy, 2 * distance, 200 - 2 * gappy, button_height, "folder" });
//	widgets->add(WIDGET_BUTTON_PICK_ATOMS_FILE, new Fl_Button{ gappy, 2 * distance, 200 - 2 * gappy, button_height, "atoms file" });
//	widgets->add(WIDGET_BUTTON_PICK_SPINS_FILE, new Fl_Button{ gappy, 3 * distance, 200 - 2 * gappy, button_height, "spins file" });
//	widgets->add(WIDGET_BUTTON_CONFIRM, new Fl_Button{ gappy, 4 * distance, 200 - 2 * gappy, button_height, "confirm" });
//
//		choice_window->add((*widgets)[WIDGET_CHOICE_BUTTON]);
//		choice_window->add((*widgets)[WIDGET_BUTTON_PICK_FOLDER]);
//		choice_window->add((*widgets)[WIDGET_BUTTON_PICK_ATOMS_FILE]);
//		choice_window->add((*widgets)[WIDGET_BUTTON_PICK_SPINS_FILE]);
//		choice_window->add((*widgets)[WIDGET_BUTTON_CONFIRM]);
//			widgets->set_tied(WIDGET_CHOICE_BUTTON);
//			widgets->set_tied(WIDGET_BUTTON_PICK_FOLDER);
//			widgets->set_tied(WIDGET_BUTTON_PICK_ATOMS_FILE);
//			widgets->set_tied(WIDGET_BUTTON_PICK_SPINS_FILE);
//			widgets->set_tied(WIDGET_BUTTON_CONFIRM);
//
//
//
//		auto* choice_button = static_cast<Fl_Choice*>((*widgets)[WIDGET_CHOICE_BUTTON]);
//			choice_button->labeltype(FL_FREE_LABELTYPE);
//			choice_button->add("folder", 0, choice_callback_folder, fulldata, 0);
//			choice_button->add("files", 0, choice_callback_file, fulldata, 0);
//
//		auto* button = static_cast<Fl_Button*>((*widgets)[WIDGET_BUTTON_PICK_FOLDER]);
//			button->callback(callback_choice_folder_new, fulldata);
//			button->hide();
//			// TODO: все кнопкам здесь коллбеки
//			
//		button = static_cast<Fl_Button*>((*widgets)[WIDGET_BUTTON_PICK_ATOMS_FILE]);
//			button->callback(callback_choice_atoms_new, fulldata);
//			button->hide();
//			
//		button = static_cast<Fl_Button*>((*widgets)[WIDGET_BUTTON_PICK_SPINS_FILE]);
//			button->callback(callback_choice_spins_new, fulldata);
//			button->hide();
//			
//		button = static_cast<Fl_Button*>((*widgets)[WIDGET_BUTTON_CONFIRM]);
//			button->callback(callback_confirm, fulldata);
//			button->hide();
//
//
//	choice_window->end();
//	choice_window->show();
//
//	// местный widgetlist стоит сюда тоже запихнуть =)
//
//	choice_window->callback([](Fl_Widget* _w, void* _v) { 
//		Windata* wdp = (Windata*)(_v);
//		log("\t Deleting choice_window", wdp->data->log, true);
//		//wdp->window->hide();
//		delete wdp->window; 
//		delete wdp->widgets;
//		delete wdp;
//		// а здесь вызвать его деструктор
//		}, (void*)(fulldata) ); // вызывается при попытке закрыть окно
//
//
//	// TODO: ещё ничего не готово
//}
//
//void callback_confirm(Fl_Widget* _w, void* _v) {
//
//	Windata* wd = static_cast<Windata*>(_v);
//
//	if ((wd->data->settings->path_to_folder != PATH_PLUG) 
//		||
//		(wd->data->settings->path_to_atoms_file != PATH_PLUG && wd->data->settings->path_to_spins_file != PATH_PLUG)
//		||
//		(wd->data->settings->path_to_sconfiguration_file != PATH_PLUG))
//		wd->data->settings->ready_to_visualization = true;
//
//	log("\t Configuration", wd->data->log, true);
//	
//
//	Data* d = wd->data;
//	Fl_Menu_* mw = static_cast<Fl_Menu_Bar*>((*d->widgetlist)[WIDGET_MAIN_MENU]); 
//	mw->value(0); // обнуление
//	const Fl_Menu_Item* run_button = mw->mvalue()->next(4); //получаем Run (next пропускает подменю)
//	run_button->active();
//	mw->window()->redraw();
//
//	log("\t Deleting choice_window", wd->data->log, true);
//		delete wd->window;
//		delete wd->widgets;
//		delete wd;
//
//}
//
//Settings::Settings() {
//	
//	this->argc = 0;
//	this->argv = {};
//
//	this->width = 300;
//	this->height = 300;
//	this->gap = 5;
//
//	this->path_to_folder = PATH_PLUG;
//	this->path_to_sconfiguration_file = PATH_PLUG;
//	this->path_to_spins_file = PATH_PLUG;
//	this->path_to_atoms_file = PATH_PLUG;
//
//	this->ready_to_visualization = false;
//}
//
//Settings::Settings(int argc, char** argv) {
//
//	this->argc = argc;
//	this->argv = argv;
//
//	this->width = 300;
//	this->height = 300;
//	this->gap = 5;
//
//	this->path_to_folder = PATH_PLUG;
//	this->path_to_sconfiguration_file = PATH_PLUG;
//	this->path_to_spins_file = PATH_PLUG;
//	this->path_to_atoms_file = PATH_PLUG;
//
//	this->ready_to_visualization = false;
//}
//
//Settings::~Settings() {
//	//
//}
//
//bool create_main_menu(Data* data) {
//	
//	if (data->widgetlist->add(WIDGET_MAIN_MENU, new Fl_Menu_Bar{ -1, -1, data->settings->width + 2, 25, "main_menu" })) {
//		
//		Fl_Menu_Bar* menu = static_cast<Fl_Menu_Bar*>((*data->widgetlist)[WIDGET_MAIN_MENU]);
//			
//		menu_items[0] = { "&File", FL_CTRL + 'f'/*hotkey*/, 0/*callback fun*/, 0, FL_SUBMENU/*flags*/ };
//			menu_items[1] = { "&new", FL_CTRL + 'n', 0, 0, FL_SUBMENU };
//				menu_items[2] = { "s&configuration ", FL_CTRL + 'c', callback_file_new_sconfiguration, data, 0 };
//				menu_items[3] = { "&vampire configuration ", FL_CTRL + 'v', callback_file_new_vampire_configuration, data, 0 };
//				menu_items[4] = { };
//			menu_items[5] = { "&settings", FL_CTRL + 's', 0, 0, FL_SUBMENU };
//				menu_items[6] = { "&save", FL_CTRL + 's', 0, 0, 0 };  /*вызвать поиск папки*/
//				menu_items[7] = { "&get", FL_CTRL + 'g', 0, 0, 0 }; /*вызвать поиск файла*/
//				menu_items[8] = { };
//			menu_items[9] = { "save &log", FL_CTRL + 'l', 0, 0, 0 };
//			menu_items[10] = { "&reset", FL_CTRL + 'r', 0, 0, 0 };
//			menu_items[11] = { };
//		menu_items[12] = { "&Settings", FL_CTRL + 's', 0, 0, 0 };
//		menu_items[13] = { "View", 0, 0, 0, 0 };
//		menu_items[14] = { "Logging", 0, 0, 0, 0 };
//		menu_items[15] = { "Run", 0, 0, 0, FL_MENU_INACTIVE };
//		menu_items[16] = { "Help", 0, 0, 0, 0 };
//
//		menu->menu(menu_items);
//
//		//Fl_Menu_* men = menu;
//		//auto button = men->mvalue()->next(4);
//		//std::cout << button->label();
//		//std::cout << button->active();
//		//button->label();
//		//std::cout << button->flags;
//		//menu_items[16] = { "Run", 0, 0, 0, 0 };
//		//menu->redraw();
//		//menu->window()->redraw();
//
//		return true;
//	}
//	else return false;
//}
//
//bool windowing(Data* data) {
//
//	data->settings->width = Fl::w() / 2;
//	data->settings->height = Fl::h() / 2;
//
//	if (!create_main_menu(data)) throw std::exception{ "[]create_main_menu doesnt work correctly" };
//
//	Fl_Window* main_window = new Fl_Window{ 100, 100,  data->settings->width, data->settings->height, "main_window"};
//	Fl_Box* box = new Fl_Box{ 10, 10, 10, 10, "abobus" };
//
//	main_window->add((*data->widgetlist)[WIDGET_MAIN_MENU]);
//		(*data->widgetlist).set_tied(WIDGET_MAIN_MENU);
//			fl_set_object_boxtype((*data->widgetlist)[WIDGET_MAIN_MENU], FL_FLAT_BOX); // FL_NO_BOX может быть как поверх экрана
//		// widgetlist.set_untied(WIDGET_MAIN_MENU); будет крашить, что верно!
//
//	main_window->end();
//
//	Fl_Group* resble = new Fl_Group{ 0, (*data->widgetlist)[WIDGET_MAIN_MENU]->h(),
//									(*data->widgetlist)[WIDGET_MAIN_MENU]->w(), main_window->h() - (*data->widgetlist)[WIDGET_MAIN_MENU]->h()
//									};
//
//	main_window->resizable(resble); /*задали изменяемую область resble, не задевающую меню*/
//	
//	main_window->show(data->settings->argc, data->settings->argv);
//	
//	Fl::run();
//
//	delete resble;
//	delete main_window;
//	
//	return true;
//}
//
//void log(std::string _str, std::list<std::string>* _log, bool _full) {
//	if (_full) _log->push_back(_str);
//	std::cout << _str << '\n';
//}
//
//Data::Data() {
//	this->widgetlist = new WidgetList{};
//	this->log = new std::list<std::string> {};
//	this->settings = new Settings {};
//	this->VOID = nullptr;
//}
//
//Data::Data(std::list<std::string>* _log, Settings* _settings) {
//	this->widgetlist = new WidgetList{};
//	this->log = _log;
//	this->settings = _settings;
//	this->VOID = nullptr;
//}
//
//Data::~Data() {
//	delete this->widgetlist;
//	delete this->log;
//	delete this->settings;
//}
