#include "window.hpp"

#include <config.h>
#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Hor_Slider.H>
#include <FL/Fl_Toggle_Button.H>
#include <FL/math.h>
#include <FL/gl.h>
#include <FL/glut.H>
#include <FL/Fl_Gl_Window.H>

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
	this->menu_items[15] = { "Run", 0, this->callbackRun, this, FL_MENU_INACTIVE };
	this->menu_items[16] = { "Help", 0, 0, 0, 0 };
	this->menu_items[17] = { };
	
	this->main_menu->menu(this->menu_items);

	this->resizable_group = new Fl_Group{ 0, this->main_menu->h(),
									this->main_menu->w(), this->h() - this->main_menu->h()
	};

	this->main_menu->box(FL_FLAT_BOX);
	this->main_menu->down_box(FL_FLAT_BOX);

	this->main_menu->color(FL_MY_BACKGROUND); // TODO: настроить
	this->main_menu->down_color(FL_MY_FOCUS); // а то токсично
	this->main_menu->textcolor(FL_MY_TEXT); //

	this->resizable(this->resizable_group); /*задали изменяемую область resble, не задевающую меню*/

	this->color(FL_MY_BACKGROUND);
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


	Fl_Glut_Window* glut_window = new Fl_Glut_Window{ 100, 100, 100, 100, "glut"};

	glut_window->show(settings->argc, settings->argv);

	Fl::scheme("gtk+");
	Fl::run();

	delete main_window;

	return true;
}

void MainWindow::callbackNewSconfiguration(Fl_Widget* _w, void* _v) {
	MainWindow* main_window = static_cast<MainWindow*>(_v);

	main_window->settings->ready_to_visualization = false;

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

	if (main_window->settings->path_to_sconfiguration_file != PATH_PLUG) {

		auto run_button = const_cast<Fl_Menu_Item*>(main_window->main_menu->find_item("Run")); //
							run_button->activate();

		main_window->main_menu->update();
		main_window->main_menu->redraw();

		main_window->settings->ready_to_visualization = true; // TODO: нормальная проверка на файл
	}
	

	delete chooser;
}

void MainWindow::callbackNewVampireConfiguration(Fl_Widget* _w, void* _v) {
	MainWindow* main_window = static_cast<MainWindow*>(_v);

	main_window->settings->ready_to_visualization = false;

	VampireConfigWindow* vamp_window = new VampireConfigWindow{ 100, 100, 400, 200, "choice_window", main_window};

	vamp_window->color(FL_MY_BACKGROUND);
	vamp_window->color2(FL_BLACK);
	vamp_window->labelcolor(FL_BLACK);
	vamp_window->selection_color(FL_BLACK);

	vamp_window->show();
	vamp_window->callback([](Fl_Widget* _w, void* _v) { delete static_cast<VampireConfigWindow*>(_w); });
}

void MainWindow::callbackRun(Fl_Widget* _w, void* _v) {
	MainWindow* main_window = static_cast<MainWindow*>(_v);

	if (main_window->settings->ready_to_visualization) {
		auto x = sconfiguration_parsing(main_window->settings->path_to_sconfiguration_file);
		std::cout << x.size();
	}

}

VampireConfigWindow::VampireConfigWindow(int x, int y, int width, int height, const char* label, MainWindow* main_window) : Fl_Window(x, y, width, height, label) {
	this->settings = main_window->settings;

	const int gappy = 10;
	const int button_height = 25;
	const int distance = button_height + static_cast<int>(1 * gappy);

	this->main_choice = new Fl_Choice { gappy, gappy, 200 - 2 * gappy, button_height, "CHOICE" };
		this->main_choice->add("folder", 0, this->callbackNewFolderVampireConfigurationChoice, this, 0);
		this->main_choice->add("files", 0, this->callbackNewFileVampireConfigurationChoice, this, 0);
		this->main_choice->labeltype(FL_FREE_LABELTYPE); // no label
		this->main_choice->box(_FL_OFLAT_BOX);
		this->main_choice->color(FL_MY_TEXT);
		this->main_choice->down_color(FL_MY_FOCUS);
		this->main_choice->selection_color(FL_MY_FOCUS);
		this->main_choice->color2(FL_MY_FOCUS);
		this->main_choice->textcolor(FL_BLACK);
		this->main_choice->down_box(FL_FLAT_BOX);

	this->text_choice = new Fl_Text_Display{ gappy + 200, gappy, 200 - 2 * gappy, static_cast<int>(button_height + 2) };
	this->buffer_choice = new Fl_Text_Buffer{}; this->buffer_choice->text("Select folder or each file separately");
		this->text_choice->buffer(this->buffer_choice);
		this->text_choice->scrollbar_size(7); // in pixels
		this->text_choice->box(FL_FLAT_BOX);
		this->text_choice->color(FL_MY_BACKGROUND);
		this->text_choice->textcolor(FL_MY_TEXT);
		this->text_choice->scrollbar_align(FL_ALIGN_BOTTOM);
		this->text_choice->selection_color(FL_RED);

	this->button_folder = new Fl_Button { gappy, 2 * distance, 200 - 2 * gappy, button_height, "folder" };
		this->button_folder->hide();
		this->button_folder->callback(this->callbackNewFolderVampireConfigurationButton, this);
		this->button_folder->box(FL_ROUNDED_BOX);
		this->button_folder->down_box(FL_ROUNDED_BOX);
		this->button_folder->color(FL_MY_TEXT);
		this->button_folder->labelcolor(FL_MY_BACKGROUND);
		this->button_folder->selection_color(FL_MY_FOCUS);

	this->text_folder = new Fl_Text_Display{ gappy + 200, 2 * distance, 200 - 2 * gappy, static_cast<int>(button_height + 2) };
	this->buffer_folder = new Fl_Text_Buffer{}; this->buffer_folder->text("select folder");
		this->text_folder->buffer(this->buffer_folder);
		this->text_folder->scrollbar_size(7); // in pixels
		this->text_folder->box(FL_FLAT_BOX);
		this->text_folder->color(FL_MY_BACKGROUND);
		this->text_folder->textcolor(FL_MY_TEXT);
		this->text_folder->scrollbar_align(FL_ALIGN_BOTTOM);
		this->text_folder->selection_color(FL_MY_FOCUS);
		this->text_folder->hide();

	this->button_atoms = new Fl_Button{ gappy, 2 * distance, 200 - 2 * gappy, button_height, "atoms file" };
		this->button_atoms->hide();
		this->button_atoms->callback(this->callbackNewAtomsFileVampireConfigurationButton, this);
		this->button_atoms->color(FL_MY_BACKGROUND);
		this->button_atoms->box(FL_ROUNDED_BOX);
		this->button_atoms->down_box(FL_ROUNDED_BOX);
		this->button_atoms->color(FL_MY_TEXT);
		this->button_atoms->labelcolor(FL_MY_BACKGROUND);
		this->button_atoms->selection_color(FL_MY_FOCUS);
		
	this->text_atoms = new Fl_Text_Display{ gappy + 200, 2 * distance,  200 - 2 * gappy, static_cast<int>(button_height + 2) };
	this->buffer_atoms = new Fl_Text_Buffer{}; this->buffer_atoms->text("select atoms file");
		this->text_atoms->buffer(this->buffer_atoms);
		this->text_atoms->scrollbar_size(7);
		this->text_atoms->box(FL_FLAT_BOX);
		this->text_atoms->color(FL_MY_BACKGROUND);
		this->text_atoms->textcolor(FL_MY_TEXT);
		this->text_atoms->scrollbar_align(FL_ALIGN_BOTTOM);
		this->text_atoms->selection_color(FL_MY_FOCUS);
		this->text_atoms->hide();


	this->button_spins = new Fl_Button{ gappy, 3 * distance, 200 - 2 * gappy, button_height, "spins file" };
		this->button_spins->hide();
		this->button_spins->callback(this->callbackNewSpinsFileVampireConfigurationButton, this);
		this->button_spins->color(FL_MY_BACKGROUND);
		this->button_spins->box(FL_ROUNDED_BOX);
		this->button_spins->down_box(FL_ROUNDED_BOX);
		this->button_spins->color(FL_MY_TEXT);
		this->button_spins->labelcolor(FL_MY_BACKGROUND);
		this->button_spins->selection_color(FL_MY_FOCUS);

	this->text_spins = new Fl_Text_Display{ gappy + 200, 3 * distance,  200 - 2 * gappy, static_cast<int>(button_height + 2) };
	this->buffer_spins = new Fl_Text_Buffer{}; this->buffer_spins->text("select spins file");
		this->text_spins->buffer(this->buffer_spins);
		this->text_spins->scrollbar_size(7);
		this->text_spins->box(FL_FLAT_BOX);
		this->text_spins->color(FL_MY_BACKGROUND);
		this->text_spins->textcolor(FL_MY_TEXT);
		this->text_spins->scrollbar_align(FL_ALIGN_BOTTOM);
		this->text_spins->selection_color(FL_MY_FOCUS);
		this->text_spins->hide();

	this->button_confirm = new Fl_Button{ gappy, 4 * distance, 200 - 2 * gappy, button_height, "confirm" };
		this->button_confirm->hide();
		this->button_confirm->callback(this->callbackConfirmButton, 
					new std::pair<MainWindow*, VampireConfigWindow*>{ main_window, this });
		this->button_confirm->color(FL_MY_BACKGROUND);
		this->button_confirm->box(FL_ROUNDED_BOX);
		this->button_confirm->down_box(FL_ROUNDED_BOX);
		this->button_confirm->color(FL_MY_TEXT);
		this->button_confirm->labelcolor(FL_MY_BACKGROUND);
		this->button_confirm->selection_color(FL_MY_FOCUS);
}

VampireConfigWindow::~VampireConfigWindow() {
	delete this->main_choice;
	delete this->button_folder;
	delete this->button_atoms;
	delete this->button_spins;
	delete this->button_confirm;
	delete this->text_atoms;
	delete this->text_folder;
	delete this->text_spins;
	delete this->buffer_atoms;
	delete this->buffer_folder;
	delete this->buffer_spins;
	delete this->text_choice;
	delete this->buffer_choice;
}

void VampireConfigWindow::callbackNewFolderVampireConfigurationChoice(Fl_Widget* _w, void* _v) {
	VampireConfigWindow* window = static_cast<VampireConfigWindow*>(_v);

	window->button_folder->show();
	window->button_atoms->hide();
	window->button_spins->hide();
	window->button_confirm->hide();
	window->text_atoms->hide();
	window->text_spins->hide();
	window->text_folder->show();
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

	if (window->settings->path_to_folder != PATH_PLUG)
		window->button_confirm->show();
	
	window->buffer_folder->text(window->settings->path_to_folder.c_str());

}

void VampireConfigWindow::callbackNewFileVampireConfigurationChoice(Fl_Widget* _w, void* _v) {
	VampireConfigWindow* window = static_cast<VampireConfigWindow*>(_v);

	window->button_folder->hide();
	window->button_atoms->show();
	window->button_spins->show();
	window->button_confirm->hide();
	window->text_atoms->show();
	window->text_spins->show();
	window->text_folder->hide();
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

	window->buffer_atoms->text(window->settings->path_to_atoms_file.c_str());

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

	window->buffer_spins->text(window->settings->path_to_spins_file.c_str());

	if (window->settings->path_to_atoms_file != PATH_PLUG && window->settings->path_to_spins_file != PATH_PLUG)
		window->button_confirm->show();
}

void VampireConfigWindow::callbackConfirmButton(Fl_Widget* _w, void* _v) {
	auto windows_pair = static_cast<std::pair<MainWindow*, VampireConfigWindow*>*>(_v);

	MainWindow* main_window = static_cast<MainWindow*>(windows_pair->first);
	VampireConfigWindow* vamp_window = static_cast<VampireConfigWindow*>(windows_pair->second);
	
	auto run_button = const_cast<Fl_Menu_Item*>(main_window->main_menu->find_item("Run")); //
		run_button->activate();

	main_window->main_menu->update();
	main_window->main_menu->redraw();

	main_window->settings->ready_to_visualization = true;

	vamp_window->~VampireConfigWindow();

	delete windows_pair;
}
