#include "window.hpp"

MainWindow::MainWindow(int x, int y, int width, int height, const char* label, Settings* settings) : Fl_Window(x, y, width, height, label) {
	this->settings = settings;
	
	this->settings->width = Fl::w() / 2;
	this->settings->height = Fl::h() / 2;

	this->main_menu = new Fl_Menu_Bar{ 0, 0, settings->width + 2, 25, "main_menu" };

	this->menu_items[0] = { "File", FL_CTRL + 'f'/*hotkey*/, 0/*callback fun*/, 0, FL_SUBMENU/*flags*/ };
		this->menu_items[1] = { "new", FL_CTRL + 'n', 0, 0, FL_SUBMENU };
			this->menu_items[2] = { "sconfiguration ", FL_CTRL + 'c', this->callbackNewSconfiguration, this, 0 };
			this->menu_items[3] = { "vampire configuration ", FL_CTRL + 'v', this->callbackNewVampireConfiguration, this, 0 };
			this->menu_items[4] = { };
		this->menu_items[5] = { "settings", FL_CTRL + 's', 0, 0, FL_SUBMENU };
			this->menu_items[6] = { "save", FL_CTRL + 's', 0, 0, 0 };  /*вызвать поиск папки*/
			this->menu_items[7] = { "get", FL_CTRL + 'g', 0, 0, 0 }; /*вызвать поиск файла*/
			this->menu_items[8] = { };
		this->menu_items[9] = { "save log", FL_CTRL + 'l', 0, 0, 0 };
		this->menu_items[10] = { "reset", FL_CTRL + 'r', 0, 0, 0 };
		this->menu_items[11] = { };
	this->menu_items[12] = { "Settings", FL_CTRL + 's', 0, 0, 0 };
	this->menu_items[13] = { "View", 0, 0, 0, 0 };
	this->menu_items[14] = { "Logging", 0, 0, 0, 0 };
	this->menu_items[15] = { "Run", 0, 0, 0, FL_MENU_INACTIVE };
	this->menu_items[16] = { "Help", 0, 0, 0, 0 };
	this->menu_items[17] = { };
	
	this->main_menu->menu(this->menu_items);

	this->resizable_group = new Fl_Group{ 0, this->main_menu->h(),
									this->main_menu->w(), this->h() - this->main_menu->h()
	};

	fl_set_object_boxtype(this->main_menu, FL_FLAT_BOX);

	this->resizable(this->resizable_group); /*задали изменяемую область resble, не задевающую меню*/

}

MainWindow::~MainWindow() {
	delete this->main_menu;
	delete this->resizable_group;
}

bool windowing(Settings* settings) {

	settings->width = Fl::w() / 2;
	settings->height = Fl::h() / 2;

	MainWindow* main_window = new MainWindow{ 100, 100, settings->width, settings->height, "main_window", settings };
	
	main_window->show(settings->argc, settings->argv);

	Fl::run();

	delete main_window;

	return true;
}

void MainWindow::callbackNewSconfiguration(Fl_Widget* _w, void* _v) {
	MainWindow* main_window = static_cast<MainWindow*>(_v);

	//log("Sconfiguration callback: ", data->log, true);
	//log("\t Creating chooser", data->log, true);
	Fl_Native_File_Chooser* chooser = new Fl_Native_File_Chooser{ Fl_Native_File_Chooser::BROWSE_FILE };
	
	chooser->title("Select the sconfiguration file");
	chooser->directory("/");
	
	switch (chooser->show()) {
		case 1:		/*log("\t Canceled", data->log, true);*/														break;
		case -1:	/*log("\t Error: \n\t\t " + std::string{ chooser->errmsg() }, data->log, true);*/				break;
		case 0:		/*log("\t Selected file: \n\t\t " + std::string{ chooser->filename() }, data->log, true);*/		
					main_window->settings->path_to_sconfiguration_file = chooser->filename();
					main_window->settings->path_to_atoms_file = PATH_PLUG;
					main_window->settings->path_to_spins_file = PATH_PLUG;
					main_window->settings->path_to_folder = PATH_PLUG;
					/*log("\t Saved filename: \n\t\t " + data->settings->path_to_sconfiguration_file, data->log, true);*/
																												break;
		default:																								break;
	};
	
	delete chooser;
}

void MainWindow::callbackNewVampireConfiguration(Fl_Widget* _w, void* _v) {
	MainWindow* main_window = static_cast<MainWindow*>(_v);

	VampireConfigWindow* vamp_window = new VampireConfigWindow{ 100, 100, 200, 200, "choice_window", main_window};

	vamp_window->show();
	vamp_window->callback([](Fl_Widget* _w, void* _v) { delete static_cast<VampireConfigWindow*>(_w); });
}

VampireConfigWindow::VampireConfigWindow(int x, int y, int width, int height, const char* label, MainWindow* main_window) : Fl_Window(x, y, width, height, label) {
	this->settings = main_window->settings;

	const int gappy = 10;
	const int button_height = 25;
	const int distance = button_height + gappy;

	this->main_choice = new Fl_Choice { gappy, gappy, 200 - 2 * gappy, button_height, "CHOICE" };
		this->main_choice->add("folder", 0, this->callbackNewFolderVampireConfigurationChoice, this, 0);
		this->main_choice->add("files", 0, this->callbackNewFileVampireConfigurationChoice, this, 0);
		this->main_choice->labeltype(FL_FREE_LABELTYPE);
	this->button_folder = new Fl_Button { gappy, 2 * distance, 200 - 2 * gappy, button_height, "folder" };
		this->button_folder->hide();
		this->button_folder->callback(this->callbackNewFolderVampireConfigurationButton, this);
	this->button_atoms = new Fl_Button{ gappy, 2 * distance, 200 - 2 * gappy, button_height, "atoms file" };
		this->button_atoms->hide();
		this->button_atoms->callback(this->callbackNewAtomsFileVampireConfigurationButton, this);
	this->button_spins = new Fl_Button{ gappy, 3 * distance, 200 - 2 * gappy, button_height, "spins file" };
		this->button_spins->hide();
		this->button_spins->callback(this->callbackNewSpinsFileVampireConfigurationButton, this);
	this->button_confirm = new Fl_Button{ gappy, 4 * distance, 200 - 2 * gappy, button_height, "confirm" };
		this->button_confirm->hide();
		this->button_confirm->callback(this->callbackConfirmButton, this);

}

VampireConfigWindow::~VampireConfigWindow() {
	delete this->main_choice;
	delete this->button_folder;
	delete this->button_atoms;
	delete this->button_spins;
	delete this->button_confirm;
}

void VampireConfigWindow::callbackNewFolderVampireConfigurationChoice(Fl_Widget* _w, void* _v) {
	VampireConfigWindow* window = static_cast<VampireConfigWindow*>(_v);

	window->button_folder->show();
	window->button_atoms->hide();
	window->button_spins->hide();
	window->button_confirm->hide();
}

void VampireConfigWindow::callbackNewFolderVampireConfigurationButton(Fl_Widget* _w, void* _v) {
	VampireConfigWindow* window = static_cast<VampireConfigWindow*>(_v);

	Fl_Native_File_Chooser* chooser = new Fl_Native_File_Chooser{ Fl_Native_File_Chooser::BROWSE_DIRECTORY };

	chooser->title("Select the vampire-folder");
	chooser->directory("/");

	switch (chooser->show()) {
		case 1:																									break;
		case -1:																								break;
		case 0:
			window->settings->path_to_folder = chooser->filename();
			window->settings->path_to_atoms_file = PATH_PLUG;
			window->settings->path_to_spins_file = PATH_PLUG;
			window->settings->path_to_sconfiguration_file = PATH_PLUG;											break;
		default:																								break;
	};
	
	delete chooser;

	window->button_confirm->show();

	// TODO
}

void VampireConfigWindow::callbackNewFileVampireConfigurationChoice(Fl_Widget* _w, void* _v) {
	VampireConfigWindow* window = static_cast<VampireConfigWindow*>(_v);

	window->button_folder->hide();
	window->button_atoms->show();
	window->button_spins->show();
	window->button_confirm->hide();
}

void VampireConfigWindow::callbackNewAtomsFileVampireConfigurationButton(Fl_Widget* _w, void* _v) {
	VampireConfigWindow* window = static_cast<VampireConfigWindow*>(_v);

	Fl_Native_File_Chooser* chooser = new Fl_Native_File_Chooser{ Fl_Native_File_Chooser::BROWSE_FILE };

	chooser->title("Select the vampire-folder");
	chooser->directory("/");

	switch (chooser->show()) {
		case 1:																									break;
		case -1:																								break;
		case 0:
			window->settings->path_to_folder = PATH_PLUG;
			window->settings->path_to_atoms_file = chooser->filename();
			window->settings->path_to_sconfiguration_file = PATH_PLUG;											break;
		default:																								break;
	};
	
	delete chooser;

	if (window->settings->path_to_atoms_file != PATH_PLUG && window->settings->path_to_spins_file != PATH_PLUG)
		window->button_confirm->show();
}

void VampireConfigWindow::callbackNewSpinsFileVampireConfigurationButton(Fl_Widget* _w, void* _v) {
	VampireConfigWindow* window = static_cast<VampireConfigWindow*>(_v);

	Fl_Native_File_Chooser* chooser = new Fl_Native_File_Chooser{ Fl_Native_File_Chooser::BROWSE_FILE };

	chooser->title("Select the vampire-folder");
	chooser->directory("/");

	switch (chooser->show()) {
		case 1:																									break;
		case -1:																								break;
		case 0:
			window->settings->path_to_folder = PATH_PLUG;
			window->settings->path_to_spins_file = chooser->filename();
			window->settings->path_to_sconfiguration_file = PATH_PLUG;											break;
		default:																								break;
	};
	
	delete chooser;

	if (window->settings->path_to_atoms_file != PATH_PLUG && window->settings->path_to_spins_file != PATH_PLUG)
		window->button_confirm->show();
}

void VampireConfigWindow::callbackConfirmButton(Fl_Widget* _w, void* _v) {
	VampireConfigWindow* window = static_cast<VampireConfigWindow*>(_v);
	
	// TODO

	window->~VampireConfigWindow();
}
