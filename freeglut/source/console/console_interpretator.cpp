#include "./console_interpretator.hpp"

// TODO: Asserts на пустые параметры


Interpretator::Interpretator() {
	this->prompt = L"vvis > ";
	set_command_maps(*this);
}

unsigned char Interpretator::loop(int argc, char** argv, std::vector<std::wstring> _commands) {
	print_logo(std::wcout);
	std::wstring str;
	std::vector<std::wstring> command_vector;

	this->argc = argc; this->argv = argv;

	do {
		if (_commands.empty()) {
			std::wcout << this->prompt; std::getline(std::wcin, str);
			command_vector = line_to_vector(str); 
		} else {
			command_vector = _commands; _commands = {};
		}

		if (by_synonyms(str) == L"exit") goto end_0;

		if (command_vector.size() < 1) continue;

		switch (get_second_from_map(this->main_command, to_lower_wstr(command_vector[0]))) {
			case INTER_COMMAND_HELP:		std::wcout << L'\n'; if (!this->help_handler(command_vector)) std::wcout << "\tUnsuccessfully\n"; std::wcout << std::endl;		break;
			case INTER_COMMAND_SETTINGS:	std::wcout << L'\n'; if (!this->settings_handler(command_vector)) std::wcout << "\tUnsuccessfully\n"; std::wcout << std::endl;	break;
			case INTER_COMMAND_RESTART:		std::wcout << L'\n'; if (!this->restart_handler(command_vector)) std::wcout << "\tUnsuccessfully\n"; else goto end_2; std::wcout << std::endl;	break;
			case INTER_COMMAND_RESET:		std::wcout << L'\n'; if (!this->reset_handler(command_vector)) std::wcout << "\tUnsuccessfully\n"; std::wcout << std::endl;	break;
			case INTER_COMMAND_SET:			std::wcout << L'\n'; if (!this->set_handler(command_vector)) std::wcout << "\tUnsuccessfully\n"; std::wcout << std::endl;		break;
			case INTER_COMMAND_UNSET:		std::wcout << L'\n'; if (!this->unset_handler(command_vector)) std::wcout << "\tUnsuccessfully\n"; std::wcout << std::endl;		break;
			case INTER_COMMAND_CONVERT:		std::wcout << L'\n'; if (!this->convert_handler(command_vector)) std::wcout << "\tUnsuccessfully\n"; std::wcout << std::endl;		break;
			case INTER_COMMAND_VISUALIZE:	std::wcout << L'\n'; if (!this->visualize_handler(command_vector)) std::wcout << "\tUnsuccessfully\n"; std::wcout << std::endl;		break;

			case VVIS_UNKNOWW_MAP_SECOND: std::wcout << L"\n\tUnknow command: " << command_vector[0] << L'\n' << std::endl; break;
			default: break;
		};


	} while (by_synonyms(str) != L"exit");
	


	end_0: return 0;
	end_1: return 1;
	end_2: return 2;
}

bool Interpretator::settings_handler(std::vector<std::wstring> _commands) {

	if (_commands.size() < 2) { std::wcout << L"\tEmpty subcommand\n"; return false; }

	switch (get_second_from_map(this->settings_sub_command, to_lower_wstr(_commands[1]))) {

		case INTER_COMMAND_SETTINGS_SHOW: {

			if (_commands.size() < 3) return settings_handler({L"settings", L"show", L"default"});

			switch (get_second_from_map(this->settings_show_sub_command, to_lower_wstr(_commands[2]))) {
				case INTER_COMMAND_SETTINGS_SHOW_ALL:		std::wcout << this->app_settings;						break;
				case INTER_COMMAND_SETTINGS_SHOW_CONSOLE:	this->app_settings.print_only_global(std::wcout);		break;
				case INTER_COMMAND_SETTINGS_SHOW_FREEGLUT:	this->app_settings.print_only_freeglut(std::wcout);		break;
				case INTER_COMMAND_SETTINGS_SHOW_DEFAULT:	this->app_settings.print_only_global(std::wcout);		break;
				
				case VVIS_UNKNOWW_MAP_SECOND: std::wcout << L"\tUnknow subcommand: " << _commands[2] << L'\n'; return false; break;
				default: break;
			};

		} break;
	
		case INTER_COMMAND_SETTINGS_SAVE:	if(this->app_settings.save(L'a')) std::wcout << "\tSettings has been saved\n"; else std::wcout << "\tSettings NOT has been saved\n"; 	break;
	
		case INTER_COMMAND_SETTINGS_GET:	if(this->app_settings.get(L'a')) std::wcout << "\tSettings has been loaded\n"; else std::wcout << "\tSettings NOT has been loaded\n";	break;

		case INTER_COMMAND_SETTINGS_RESET: reset_handler({L"reset"}); break;

		case VVIS_UNKNOWW_MAP_SECOND: std::wcout << L"\tUnknow subcommand: " << _commands[1] << L'\n'; return false; break;
		default: break;

	}

	return true;
}

bool Interpretator::help_handler(std::vector<std::wstring> _commands) {

	if (_commands.size() < 2) { 
		std::wcout << L"\tUsage : help <subcommand: {settings, set, unset, convert, visualize, reset, restart}>\n";
		std::wcout << L"\tExit  : exit\n";
		return true;
	}

	switch (get_second_from_map(this->help_sub_command, to_lower_wstr(_commands[1]))) {

		case INTER_COMMAND_HELP_SETTINGS:	

			std::wcout << L"\tsettings show\n";
				std::wcout << L"\t  -- <nothing> : shows CONSOLE settings (paths, filenumber etc.)\n";
				std::wcout << L"\t  -- all       : shows ALL settings (including spinrate, main_window, console_settings, window(freeglut)_settings)\n";
				std::wcout << L"\t  -- console   : shows only CONSOLE settings (paths, filenumber etc.)\n";
				std::wcout << L"\t  -- window    : shows only WINDOW(freeglut)_settings (coloring, positions etc.)\n";

			std::wcout << L"\n";
			std::wcout << L"\tsettings save\n";
				std::wcout << L"\t  -- <nothing> : saves ALL settings in visualis-settings.json file by path (in order of importance):\n";
				std::wcout << L"\t               : path to settings file, path to settings folder, path to folder\n";

			std::wcout << L"\n";
			std::wcout << L"\tsettings get\n";
				std::wcout << L"\t  -- <nothing> : restores ALL settings from visualis-settings.json file by path (in order of importance):\n";
				std::wcout << L"\t               : path to settings file, path to settings folder, path to folder\n";
			
			std::wcout << L"\n";
			std::wcout << L"\tsettings reset\n";
				std::wcout << L"\t  -- <nothing> : resets ALL settings in console (not file)\n";
				std::wcout << L"\t               : also command \"reset\" does the same \n";

			std::wcout << L"\n";
			std::wcout << L"\tAliases: settings, setting, setgs, setg, sgs\n";
			break;

		case INTER_COMMAND_HELP_SET:		

			std::wcout << L"\tset folderpath\n";
				std::wcout << L"\t -- <path>/<\"path\">             : sets path to folder with sconfiguration file or convertible files\n";
				std::wcout << L"\t                                : Example: set folderpath ../temp/b\n";
				std::wcout << L"\t                                : Aliases: folderpath, folpath, folp, folderp\n";
			
			std::wcout << L"\n";
			std::wcout << L"\tset filenumber\n";
				std::wcout << L"\t -- <int>                       : sets number of sconfiguration file or spins-file for v6\n";
				std::wcout << L"\t                                : Example: set filenumber 30\n";
				std::wcout << L"\t                                : Aliases: filenumber, fnumber, fn, filen\n";
			
			std::wcout << L"\n";
			std::wcout << L"\tset filepath\n";
				std::wcout << L"\t -- <path>/<\"path\">             : sets path to sconfiguration-xxx.vvis file\n";
				std::wcout << L"\t                                : Example: set filepath ../temp/b/sconfiguration-00000030.vvis\n";
				std::wcout << L"\t                                : Aliases: filepath, fpath, fp, filep\n";
			
			std::wcout << L"\n";
			std::wcout << L"\tset spinindex\n";
				std::wcout << L"\t -- <int>                       : sets which spin will be drawn\n";
				std::wcout << L"\t                                : Example: set spinindex 10\n";
				std::wcout << L"\t                                : Aliases: spinindex, sindex, si, spini\n";
			
			std::wcout << L"\n";
			std::wcout << L"\tset settingsfolder\n";
				std::wcout << L"\t -- <path>/<\"path\">             : sets path to folder with visualis-settings.json file\n";
				std::wcout << L"\t                                : Example: set settingsfolder ../temp/b\n";
				std::wcout << L"\t                                : Aliases: settingsfolder, sgsfolder, sgsfol\n";
			
			std::wcout << L"\n";
			std::wcout << L"\tset settingsfile\n";
				std::wcout << L"\t -- <path>/<\"path\">             : sets path to visualis-settings.json file\n";
				std::wcout << L"\t                                : Example: set settingsfile D:/global_settings/visualis-settings.json\n";
				std::wcout << L"\t                                : Aliases: settingsfile, sgsfile, sgsf\n";
			
			std::wcout << L"\n";
			std::wcout << L"\tset coloring\n";
				std::wcout << L"\t -- <y/n>                       : sets coloring of sample\n";
				std::wcout << L"\t                                : Example: set coloring true\n";
				std::wcout << L"\t                                : Aliases: cg\n";
			
			std::wcout << L"\n";
			std::wcout << L"\tset backgroundcolor\n";
				std::wcout << L"\t -- <int> <int> <int>           : sets coloring RGB mode of background of main window\n";
				std::wcout << L"\t                                : Note: int between 0 and 255 is expected\n";
				std::wcout << L"\t                                : Example: set backgroundcolor 200 250 100\n";
				std::wcout << L"\t -- <int> <int> <int> <int>     : sets coloring RGB mode of background of subwindow (1st parameter)\n";
				std::wcout << L"\t                                : Note: first int parameter between 0 and 3 is expected\n";
				std::wcout << L"\t                                : Example: set backgroundcolor 2 200 250 100\n";
				std::wcout << L"\t                                : Aliases: bgc\n";
			
			std::wcout << L"\n";
			std::wcout << L"\tset fullscreen\n";
				std::wcout << L"\t -- <y/n>                       : sets fullscreen mode of window\n";
				std::wcout << L"\t                                : Example: set fullscreen yes\n";
				std::wcout << L"\t                                : Aliases: fullscreen\n";
			
			std::wcout << L"\n";
			std::wcout << L"\tset shape\n";
				std::wcout << L"\t -- <char>                      : sets a shape with which the sample will be built\n";
				std::wcout << L"\t                                : Note: n - nothing, c - cone, s - sphere, a - arrow \n";
				std::wcout << L"\t                                : Example: set shape c\n";
				std::wcout << L"\t                                : Aliases: shape\n";
			
			std::wcout << L"\n";
			std::wcout << L"\tset translationbyelement\n";
				std::wcout << L"\t -- <y/n>                       : if true: left-left; false: left-right\n";
				std::wcout << L"\t                                : Example: set translationbyelement no\n";
				std::wcout << L"\t                                : Aliases: translationbyelement, tbe\n";
			
			std::wcout << L"\n";
			std::wcout << L"\tset estrangementchanges\n";
				std::wcout << L"\t -- <double>                    : changing by shift/space buttons\n";
				std::wcout << L"\t                                : Example: set estrangementchanges 0.4\n";
				std::wcout << L"\t                                : Aliases: estrangementchanges, echanges, ech\n";

			std::wcout << L"\n";
			std::wcout << L"\tset scalingchanges\n";
				std::wcout << L"\t -- <double> <double> <double>  : changing by page up/down buttons\n";
				std::wcout << L"\t                                : Note: x, y, z\n";
				std::wcout << L"\t                                : Example: set scalingchanges 0.3 0.3 0.3\n";
				std::wcout << L"\t                                : Aliases: scalingchanges, schanges, sch\n";

			std::wcout << L"\n";
			std::wcout << L"\tset translationchanges\n";
				std::wcout << L"\t -- <double> <double> <double>  : changing by arrow buttons\n";
				std::wcout << L"\t                                : Note: x, y, z\n";
				std::wcout << L"\t                                : Example: set translationchanges 1.0 1.0 1.5\n";
				std::wcout << L"\t                                : Aliases: translationchanges, tchanges, tch\n";
			
			std::wcout << L"\n";
			std::wcout << L"\tset camerachanges\n";
				std::wcout << L"\t -- <double> <double> <double>  : changing by wasd/ijkl buttons\n";
				std::wcout << L"\t                                : Note: x, y, z\n";
				std::wcout << L"\t                                : Example: set camerachanges 0.5 0.5 0.5\n";
				std::wcout << L"\t                                : Aliases: camerachanges, cchanges, cch\n";
			
			std::wcout << L"\n";
			std::wcout << L"\tset spinrate\n";
				std::wcout << L"\t -- <int>                       : sets each what spin will be built\n";
				std::wcout << L"\t                                : Note: one in one, one in two, one in ten \n";
				std::wcout << L"\t                                : Example: set spinrate 10\n";
				std::wcout << L"\t                                : Aliases: spinrate, spinr, sr, srate\n";
			
			std::wcout << L"\n";
			std::wcout << L"\tset gap\n";
				std::wcout << L"\t -- <int>                       : sets the gap between subwindows (axises, logs, stats, drawer area)\n";
				std::wcout << L"\t                                : Note: >= 0 \n";
				std::wcout << L"\t                                : Example: set gap 10\n";
				std::wcout << L"\t                                : Aliases: gap\n";
			
			std::wcout << L"\n";
			std::wcout << L"\tset subwindowing\n";
				std::wcout << L"\t -- <y/n>                       : subwindowing mode\n";
				std::wcout << L"\t                                : Note: if \"no\" - only drawer area \n";
				std::wcout << L"\t                                : Example: set subwindowing 1\n";
				std::wcout << L"\t                                : Aliases: subwindowing, subwg\n";
			
			std::wcout << L"\n";
			std::wcout << L"\tset polygonrate\n";
				std::wcout << L"\t -- <int>                       : how many polygons of shape\n";
				std::wcout << L"\t                                : Note: >= 1\n";
				std::wcout << L"\t                                : Example: set polygonrate 1\n";
				std::wcout << L"\t                                : Aliases: polygonrate, pr\n";
			
			std::wcout << L"\n";
			std::wcout << L"\tset multilayer\n";
				std::wcout << L"\t -- <y/n>                       : every layer will be colored\n";
				std::wcout << L"\t                                : Aliases: multilayer\n";
			
			std::wcout << L"\n";
			std::wcout << L"\tset multimaterial\n";
				std::wcout << L"\t -- <y/n>                       : every material will be colored\n";
				std::wcout << L"\t                                : Aliases: multimaterial\n";
			
			std::wcout << L"\n";
			std::wcout << L"\tset layer\n";
				std::wcout << L"\t -- <int> <int> <int> <int> <str> : sets colored mode to layer by index\n";
				std::wcout << L"\t                                  : Note: first parameter is INDEX, 2-4 - RGB (255 max),\n";
				std::wcout << L"\t                                  : Note: str parameter (optional) - name\n";
				std::wcout << L"\t                                  : Aliases: layer\n";
			
			std::wcout << L"\n";
			std::wcout << L"\tset material\n";
				std::wcout << L"\t -- <int> <int> <int> <int> <str> : sets colored mode to material by index\n";
				std::wcout << L"\t                                  : Note: first parameter is INDEX, 2-4 - RGB (255 max),\n";
				std::wcout << L"\t                                  : Note: str parameter (optional) - name\n";
				std::wcout << L"\t                                  : Aliases: layer\n";
			
			std::wcout << L"\n";
			std::wcout << L"\tAliases: set\n";

			break;

		case INTER_COMMAND_HELP_UNSET:			

			std::wcout << L"\tunset\n";
				std::wcout << L"\t -- <set_subcommand>   : unsets (restoring to the initial) option (see <help set>)\n";
			
			std::wcout << L"\n";
			std::wcout << L"\tAliases: unset, uset\n";
			break;

		case INTER_COMMAND_HELP_CONVERT:		
			
			std::wcout << L"\tconvert\n";
				std::wcout << L"\t -- v6   : converting vampire6 data to sconfiguration file\n";
				std::wcout << L"\t         : Note: expected: spins-xxx.data, atoms-coords.data \n";
				std::wcout << L"\t         : Aliases: vampire6, v6, vampire5, v5\n";			
					
			std::wcout << L"\n";
			std::wcout << L"\tAliases: convert, con\n";
			break;

		case INTER_COMMAND_HELP_VISUALIZE:		
			
			std::wcout << L"\tconvert file\n";
				std::wcout << L"\t --  : starts visualization by file (filepath)\n";
				std::wcout << L"\t     : Note: expected: sconfiguration file \n";

			std::wcout << L"\n";
			std::wcout << L"\tconvert folder\n";
				std::wcout << L"\t --  : starts visualization by folder path (filefolder + filenumber)\n";
				std::wcout << L"\t     : Note: expected: valid filefolder with sconfiguration file, filenumber \n";
			
			std::wcout << L"\n";
			std::wcout << L"\tAliases: visualize, vis\n";

			std::wcout << "\n\n\n\n";
			std::wcout << L"\t\tINWIDONW (drawer area)\n\n";
				std::wcout << L"\t -- keys\n";
				std::wcout << L"\t\tGlobal translation: arrow keys \n";
				std::wcout << L"\t\tCamera: WASD \n";
				std::wcout << L"\t\tGlobal rotation: IJKL \n";
				std::wcout << L"\t\tEstrangement: L_CTRL or L_SHIFT / SPACEBAR \n";
				std::wcout << L"\t\tExit: ESC \n";
				std::wcout << L"\t\tGlobal scaling: PAGE_UP/PAGE_DOWN \n";

				std::wcout << L"\t -- mouse\n";
				std::wcout << L"\t\tPressed mouse button & in movement: global translation (as with arrows)\n";
				std::wcout << L"\t\tPressed mouse button & ALT & in movement: global rotation (as by IJKL)\n";
				std::wcout << L"\t\tScrolls: changing estrangement (as by shift/space)\n";
				std::wcout << L"\t\tRight button: popup menu\n";

			std::wcout << "\n\n\n\n";
			std::wcout << L"\t\tINWIDONW (stats, logs)\n\n";
				std::wcout << L"\t -- keys\n";
				std::wcout << L"\t\tUp/down text motion: arrow keys \n";

				std::wcout << L"\t -- mouse\n";
				std::wcout << L"\t\tScrolls: scrolls text\n";
				std::wcout << L"\t\tRight button: popup menu\n";

			break;

		case INTER_COMMAND_HELP_RESET:			
			
			std::wcout << L"\treset\n";
			std::wcout << L"\t --  : resets ALL settings here\n";

			std::wcout << L"\n";
			std::wcout << L"\tAliases: reset, settings reset\n";
			break;

		case INTER_COMMAND_HELP_RESTART:	
			
			std::wcout << L"\trestart\n";
			std::wcout << L"\t --  : fully restars the program\n";

			std::wcout << L"\n";
			std::wcout << L"\tAliases: restart\n";
			break;

		case VVIS_UNKNOWW_MAP_SECOND: std::wcout << L"\tUnknow subcommand: " << _commands[1] << L'\n'; return false; break;
		default: break;

	}


	return true;
}

bool Interpretator::reset_handler(std::vector<std::wstring> _commands) {
	std::string temp = this->app_settings.global_settings.path_to_settings_file;
	this->app_settings = Settings();
	set_command_maps(*this);
	this->app_settings.global_settings.path_to_settings_file = temp;
	std::wcout << L"\tSuccessful\n";
	return true;
}

bool Interpretator::restart_handler(std::vector<std::wstring> _commands) {
	std::string temp = this->app_settings.global_settings.path_to_settings_file;
	this->app_settings = Settings();
	set_command_maps(*this);
	this->app_settings.global_settings.path_to_settings_file = temp;
	std::wcout << L"\tSuccessful\n";
	return true;
}

bool Interpretator::set_handler(std::vector<std::wstring> _commands) {
	
	if (_commands.size() < 2) { std::wcout << L"\tEmpty subcommand\n"; return false; }
	
	switch (get_second_from_map(this->set_sub_command, to_lower_wstr(_commands[1]))) {
	
		case INTER_COMMAND_SET_FOLDERPATH: { 
			if (_commands.size() < 3) { std::wcout << L"\tEmpty path\n"; return false; }
			if (_commands[2].size() > 0) {
				remove_quotations(_commands[2]);
				this->app_settings.global_settings.path_to_folder = wstr2str(_commands[2]);
				std::wcout << L"\tPath to folder \"" << str2wstr(this->app_settings.global_settings.path_to_folder) << L"\" has been set up\n";
			} else std::wcout << L"\n\tEmpty path\n";
		} break;
		
		case INTER_COMMAND_SET_FILEPATH: {
			if (_commands.size() < 3) { std::wcout << L"\tEmpty path\n"; return false; }
			if (!contains_substr(wstr2str(_commands[2]), VVIS_VVIS_FILE_FORMAT_WSTR) || !contains_substr(wstr2str(_commands[2]), VVIS_VVIS_FILE_START_NAME_WSTR)) { std::wcout << L"\tWrong file name\n"; return false; }
			if (_commands[2].size() > 0) {
				remove_quotations(_commands[2]);
				this->app_settings.global_settings.path_to_sconfiguration_file = wstr2str(_commands[2]);
				std::wcout << L"\tPath to sconfiguration file \"" << str2wstr(this->app_settings.global_settings.path_to_sconfiguration_file) << L"\" has been set up\n";
			} else std::wcout << L"\n\tEmpty path\n";
		} break;

		case INTER_COMMAND_SET_FILENUMBER: if (_commands.size() < 3) { std::wcout << L"\tEmpty instruction\n"; return false; }
							if (!is_number(_commands[2])) { std::wcout << L"\tNot number\n"; return false; }
							else { this->app_settings.global_settings.number_of_file = std::stoi(_commands[2]);
						std::wcout << L"\tFile number \"" << this->app_settings.global_settings.number_of_file << L"\" has been set up\n"; } break;

		case INTER_COMMAND_SET_SPININDEX: if (_commands.size() < 3) { std::wcout << L"\tEmpty instruction\n"; return false; }
							if (!is_number(_commands[2])) { std::wcout << L"\tNot number\n"; return false; }
							else { this->app_settings.global_settings.index_of_spin = std::stoi(_commands[2]);
						std::wcout << L"\tSpin index \"" << this->app_settings.global_settings.index_of_spin << L"\" has been set up\n"; } break;

		case INTER_COMMAND_SET_SETTINGSFOLDER : {
			if (_commands.size() < 3) { std::wcout << L"\tEmpty path\n"; return false; }
			if (_commands[2].size() > 0) {
				remove_quotations(_commands[2]);
				this->app_settings.global_settings.path_to_settings_file_folder = wstr2str(_commands[2]);
				std::wcout << L"\tPath to settings folder \"" << str2wstr(this->app_settings.global_settings.path_to_settings_file_folder) << L"\" has been set up\n";
			} else std::wcout << L"\n\tEmpty path\n";
		} break;

		case INTER_COMMAND_SET_SETTINGSFILE: {
			if (_commands.size() < 3) { std::wcout << L"\tEmpty path\n"; return false; }
			if (!contains_substr(wstr2str(_commands[2]), VVIS_SETTINGS_FILE_NAME_WSTR)) { std::wcout << L"\tWrong file name\n"; return false; }
			if (_commands[2].size() > 0) {
				remove_quotations(_commands[2]);
				this->app_settings.global_settings.path_to_settings_file = wstr2str(_commands[2]);
				std::wcout << L"\tPath to settings file \"" << str2wstr(this->app_settings.global_settings.path_to_settings_file) << L"\" has been set up\n";
			} else std::wcout << L"\n\tEmpty path\n";
		} break;


		case INTER_COMMAND_SET_COLORING: if (_commands.size() < 3) { std::wcout << L"\tEmpty instruction\n"; return false; } 
									   this->app_settings.freeglut_settings.coloring_sample = by_synonyms(_commands[2]) == L"yes" ? true : false;
									   std::wcout << L"\tColoring setting \"" << std::boolalpha << this->app_settings.freeglut_settings.coloring_sample << L"\" has been set up\n";
									   break;


		case INTER_COMMAND_SET_BACKGROUNDCOLOR: 
			
			switch (_commands.size()) {

				case 5 : 

					if (_commands.size() < 5 || !is_number(_commands[2]) || !is_number(_commands[3])
						|| !is_number(_commands[4]) || !is_double(_commands[2]) || !is_double(_commands[3]) || !is_double(_commands[4])
						|| std::stod(_commands[2]) > 255 || std::stod(_commands[3]) > 255
						|| std::stod(_commands[4]) > 255) {
						std::wcout << L"\tIncorrect format\n"; return false;
					}

					this->app_settings.main_window.backgroundcolor.red = std::stod(_commands[2]) / 255.0;
					this->app_settings.main_window.backgroundcolor.green = std::stod(_commands[3]) / 255.0;
					this->app_settings.main_window.backgroundcolor.blue = std::stod(_commands[4]) / 255.0;

					std::wcout << L"\tColoring background of main window ("
						<< this->app_settings.main_window.backgroundcolor.red * 255.0 << ", "
						<< this->app_settings.main_window.backgroundcolor.green * 255.0 << ", "
						<< this->app_settings.main_window.backgroundcolor.blue * 255.0
						<< L") has been set up\n";

					break;


				case 6: {

					if (_commands.size() < 6 || !is_number(_commands[2]) || !is_number(_commands[3])
						|| !is_number(_commands[4]) || !is_number(_commands[5])
						|| !is_double(_commands[3]) || !is_double(_commands[4]) || !is_double(_commands[5])
						|| std::stod(_commands[3]) > 255 || std::stod(_commands[4]) > 255
						|| std::stod(_commands[5]) > 255) {
						std::wcout << L"\tIncorrect format\n"; return false;
					}

					int number = std::stoi(_commands[2]);

					if (this->app_settings.subwindows.size() <= number) { std::wcout << L"\tSubwindow " << number << "doesnt exists\n"; return false; }

					this->app_settings.subwindows[number].backgroundcolor.red = std::stod(_commands[3]) / 255.0;
					this->app_settings.subwindows[number].backgroundcolor.green = std::stod(_commands[4]) / 255.0;
					this->app_settings.subwindows[number].backgroundcolor.blue = std::stod(_commands[5]) / 255.0;

					std::wcout << L"\tColoring background subwindow " << number << " ("
						<< this->app_settings.subwindows[number].backgroundcolor.red * 255.0 << ", "
						<< this->app_settings.subwindows[number].backgroundcolor.green * 255.0 << ", "
						<< this->app_settings.subwindows[number].backgroundcolor.blue * 255.0
						<< L") has been set up\n";

				}
					break;



				default: 
					std::wcout << L"\tIncorrect format\n"; return false;
					break;


			}
											  
				break;

		case INTER_COMMAND_SET_FULLSCREEN: if (_commands.size() < 3) { std::wcout << L"\tEmpty instruction\n"; return false; }
										 this->app_settings.freeglut_settings.fullscreen = by_synonyms(_commands[2]) == L"yes" ? true : false;
										 std::wcout << L"\tFullscreen setting \"" << std::boolalpha << this->app_settings.freeglut_settings.fullscreen << L"\" has been set up\n";
										 break;

		case INTER_COMMAND_SET_SHAPE:	if (_commands.size() < 3) { std::wcout << L"\tEmpty instruction\n"; return false; }
										if (_commands[2] == VVIS_SHAPE_CONE_WSTR || _commands[2] == L"c") {
											this->app_settings.freeglut_settings.shape = VVIS_SHAPE_CONE; 
											this->app_settings.freeglut_settings.shape_wstr = VVIS_SHAPE_CONE_WSTR; 
										} else if (_commands[2] == VVIS_SHAPE_NOTHING_WSTR || _commands[2] == L"n") {
											this->app_settings.freeglut_settings.shape = VVIS_SHAPE_NOTHING;
											this->app_settings.freeglut_settings.shape_wstr = VVIS_SHAPE_NOTHING_WSTR;
										} else if (_commands[2] == VVIS_SHAPE_SPHERE_WSTR || _commands[2] == L"s") {
											this->app_settings.freeglut_settings.shape = VVIS_SHAPE_SPHERE;
											this->app_settings.freeglut_settings.shape_wstr = VVIS_SHAPE_SPHERE_WSTR;
										} else if (_commands[2] == VVIS_SHAPE_ARROW_WSTR || _commands[2] == L"a") {
											this->app_settings.freeglut_settings.shape = VVIS_SHAPE_ARROW;
											this->app_settings.freeglut_settings.shape_wstr = VVIS_SHAPE_ARROW_WSTR;
										}
										std::wcout << L"\tShape \"" << this->app_settings.freeglut_settings.shape << "/" << this->app_settings.freeglut_settings.shape_wstr << L"\" has been set up\n";
										break;

		case INTER_COMMAND_SET_TRANSLATION_BY_ELEMENT:	if (_commands.size() < 3) { std::wcout << L"\tEmpty instruction\n"; return false; }
														this->app_settings.freeglut_settings.translation_by_element = by_synonyms(_commands[2]) == L"yes" ? 1 : -1;
														std::wcout << L"\tTranslation by element setting \"" << std::boolalpha << (this->app_settings.freeglut_settings.translation_by_element == -1 ? false : true) << L"\" has been set up\n";
														break;

		case INTER_COMMAND_SET_ESTRANGEMENT_CHANGES:	if (_commands.size() < 3 || !is_double(_commands[2])) { std::wcout << L"\tIncorrect format\n"; return false; }
														this->app_settings.freeglut_settings.estrangement_changes = std::stod(_commands[2]);
														std::wcout << L"\tEstrangement changes: \"" << this->app_settings.freeglut_settings.estrangement_changes << "\" has been set up\n";
														break;

		case INTER_COMMAND_SET_SCALING_CHANGES: if (_commands.size() < 5 ||
												!is_double(_commands[2]) || !is_double(_commands[3]) || !is_double(_commands[4])) 
												{ std::wcout << L"\tIncorrect format\n"; return false; }
											  this->app_settings.freeglut_settings.scaling_parameters_changes.x = std::stod(_commands[2]);
											  this->app_settings.freeglut_settings.scaling_parameters_changes.y = std::stod(_commands[3]);
											  this->app_settings.freeglut_settings.scaling_parameters_changes.z = std::stod(_commands[4]);
											  std::wcout << L"\tScaling parameters changes: \"(" << this->app_settings.freeglut_settings.scaling_parameters_changes.x << ", "
												  << this->app_settings.freeglut_settings.scaling_parameters_changes.y << ", "
												  << this->app_settings.freeglut_settings.scaling_parameters_changes.z
												  << ")\" has been set up\n";
											  break;

		case INTER_COMMAND_SET_TRANSLATION_CHANGES: if (_commands.size() < 5
													|| !is_double(_commands[2]) || !is_double(_commands[3]) || !is_double(_commands[4])) 
													{ std::wcout << L"\tIncorrect format\n"; return false; }
											  this->app_settings.freeglut_settings.translation_changes.x = std::stod(_commands[2]);
											  this->app_settings.freeglut_settings.translation_changes.y = std::stod(_commands[3]);
											  this->app_settings.freeglut_settings.translation_changes.z = std::stod(_commands[4]);
											  std::wcout << L"\tTranslation changes: \"(" << this->app_settings.freeglut_settings.translation_changes.x << ", "
												  << this->app_settings.freeglut_settings.translation_changes.y << ", "
												  << this->app_settings.freeglut_settings.translation_changes.z
												  << ")\" has been set up\n";
											  break;

		case INTER_COMMAND_SET_CAMERA_CHANGES:		if (_commands.size() < 5
													|| !is_double(_commands[2]) || !is_double(_commands[3]) || !is_double(_commands[4])) 
													{ std::wcout << L"\tIncorrect format\n"; return false; }
											 this->app_settings.freeglut_settings.camera_changes.x = std::stod(_commands[2]);
											 this->app_settings.freeglut_settings.camera_changes.y = std::stod(_commands[3]);
											 this->app_settings.freeglut_settings.camera_changes.z = std::stod(_commands[4]);
											 std::wcout << L"\tCamera changes: \"(" << this->app_settings.freeglut_settings.camera_changes.x << ", "
												 << this->app_settings.freeglut_settings.camera_changes.y << ", "
												 << this->app_settings.freeglut_settings.camera_changes.z
												 << ")\" has been set up\n";
											 break;


		case INTER_COMMAND_SET_SPINRATE: if (_commands.size() < 3) { std::wcout << L"\tEmpty instruction\n"; return false; }
									   if (!is_number(_commands[2])) { std::wcout << L"\tNot number\n"; return false; }
									   this->app_settings.freeglut_settings.spinrate = std::stoi(_commands[2]);
									   std::wcout << L"\tSpinrate \"" << this->app_settings.freeglut_settings.spinrate << L"\" has been set up\n";
									   break;

		case INTER_COMMAND_SET_SUBWINDOWING:  if (_commands.size() < 3) { std::wcout << L"\tEmpty instruction\n"; return false; }
										   this->app_settings.freeglut_settings.use_additional_subwindows = by_synonyms(_commands[2]) == L"yes" ? true : false;
										   std::wcout << L"\tSubwindowing setting \"" << std::boolalpha << this->app_settings.freeglut_settings.use_additional_subwindows << L"\" has been set up\n";
										   break;

		case INTER_COMMAND_SET_GAP: if (_commands.size() < 3) { std::wcout << L"\tEmpty instruction\n"; return false; }
								  if (!is_number(_commands[2])) { std::wcout << L"\tNot number\n"; return false; }
									else { this->app_settings.freeglut_settings.gap = std::stoi(_commands[2]);
								std::wcout << L"\tGap number \"" << this->app_settings.freeglut_settings.gap << L"\" has been set up\n"; } break;

		case INTER_COMMAND_SET_POLIGONRATE: if (_commands.size() < 3) { std::wcout << L"\tEmpty instruction\n"; return false; }
										  if (!is_number(_commands[2])) { std::wcout << L"\tNot number\n"; return false; }
										  else { this->app_settings.freeglut_settings.polygonrate = std::stoi(_commands[2]);
								std::wcout << L"\tPoligonrate number \"" << this->app_settings.freeglut_settings.polygonrate << L"\" has been set up\n"; } break;


		case INTER_COMMAND_SET_LAYER: { 
										if (_commands.size() < 6
										|| !is_number(_commands[2]) || !is_number(_commands[3]) || !is_number(_commands[4]) || !is_number(_commands[5])
										) { std::wcout << L"\tIncorrect format\n"; return false; }

										Layer a;
										Rgb color = Rgb(std::stoi(_commands[3]) / 255.0, std::stoi(_commands[4]) / 255.0, std::stoi(_commands[5]) / 255.0);

										if (_commands.size() == 6) {
											a = Layer(color, std::stoi(_commands[2]));
										} else {
											a = Layer(color, _commands[6], std::stoi(_commands[2]));
										}

										if (!layer_in_vector(this->app_settings.other_settings.layers, std::stoi(_commands[2])))
											this->app_settings.other_settings.layers.push_back(a);
										else
											set_layer(this->app_settings.other_settings.layers, std::stoi(_commands[2]), a);

										std::wcout << L"\tSuccesful\n";

									} break;

		case INTER_COMMAND_SET_MATERIAL: { 
										if (_commands.size() < 6
										|| !is_number(_commands[2]) || !is_number(_commands[3]) || !is_number(_commands[4]) || !is_number(_commands[5])
										) { std::wcout << L"\tIncorrect format\n"; return false; }

										Material a;
										Rgb color = Rgb(std::stoi(_commands[3]) / 255.0, std::stoi(_commands[4]) / 255.0, std::stoi(_commands[5]) / 255.0);

										if (_commands.size() == 6) {
											a = Material(color, std::stoi(_commands[2]));
										} else {
											a = Material(color, _commands[6], std::stoi(_commands[2]));
										}

										if (!material_in_vector(this->app_settings.other_settings.materials, std::stoi(_commands[2])))
											this->app_settings.other_settings.materials.push_back(a);
										else
											set_material(this->app_settings.other_settings.materials, std::stoi(_commands[2]), a);

										std::wcout << L"\tSuccesful\n";

									} break;

		case INTER_COMMAND_SET_MULTIMATERIAL: if (_commands.size() < 3) { std::wcout << L"\tEmpty instruction\n"; return false; }
											this->app_settings.other_settings.multimaterialing = by_synonyms(_commands[2]) == L"yes" ? true : false;
											std::wcout << L"\tMultimaterial setting \"" << std::boolalpha << this->app_settings.other_settings.multimaterialing << L"\" has been set up\n";
											break;

		case INTER_COMMAND_SET_MULTILAYER: if (_commands.size() < 3) { std::wcout << L"\tEmpty instruction\n"; return false; }
										 this->app_settings.other_settings.multilayering = by_synonyms(_commands[2]) == L"yes" ? true : false;
										 std::wcout << L"\tMultilayer setting \"" << std::boolalpha << this->app_settings.other_settings.multilayering << L"\" has been set up\n";
										 break;

		case VVIS_UNKNOWW_MAP_SECOND: std::wcout << L"\tUnknow subcommand: " << _commands[1] << L'\n'; return false; break;
		default: break;

	}


	return true;
}

bool Interpretator::unset_handler(std::vector<std::wstring> _commands) {
	
	if (_commands.size() < 2) { std::wcout << L"\tEmpty subcommand\n"; return false; }
	
	switch (get_second_from_map(this->set_sub_command, to_lower_wstr(_commands[1]))) {

		case INTER_COMMAND_SET_FOLDERPATH: std::wcout << L"\tSuccessful\n"; this->app_settings.global_settings.path_to_folder = VVIS_PATH_PLUG_WSTR; break;

		case INTER_COMMAND_SET_FILEPATH: std::wcout << L"\tSuccessful\n"; this->app_settings.global_settings.path_to_sconfiguration_file = VVIS_PATH_PLUG_WSTR; break;

		case INTER_COMMAND_SET_FILENUMBER: std::wcout << L"\tSuccessful\n"; this->app_settings.global_settings.number_of_file = VVIS_INT_PLUG; break;

		case INTER_COMMAND_SET_SPININDEX: std::wcout << L"\tSuccessful\n"; this->app_settings.global_settings.index_of_spin = VVIS_DRAW_ALL; break;

		case INTER_COMMAND_SET_SETTINGSFILE: std::wcout << L"\tSuccessful\n"; this->app_settings.global_settings.path_to_settings_file = VVIS_PATH_PLUG_WSTR; break;

		case INTER_COMMAND_SET_SETTINGSFOLDER: std::wcout << L"\tSuccessful\n"; this->app_settings.global_settings.path_to_settings_file_folder = VVIS_PATH_PLUG_WSTR; break;

		case INTER_COMMAND_SET_COLORING: std::wcout << L"\tSuccessful\n"; this->app_settings.freeglut_settings.coloring_sample = false; break;

		case INTER_COMMAND_SET_BACKGROUNDCOLOR: std::wcout << L"\tSuccessful\n"; this->app_settings.subwindows[0].backgroundcolor = Rgb(1.0, 1.0, 1.0); break;

		case INTER_COMMAND_SET_FULLSCREEN: std::wcout << L"\tSuccessful\n"; this->app_settings.freeglut_settings.fullscreen = false; break;

		case INTER_COMMAND_SET_SHAPE:	std::wcout << L"\tSuccessful\n"; this->app_settings.freeglut_settings.shape = VVIS_SHAPE_CONE;
										this->app_settings.freeglut_settings.shape_wstr = VVIS_SHAPE_CONE_WSTR;
										break;

		case INTER_COMMAND_SET_TRANSLATION_BY_ELEMENT: std::wcout << L"\tSuccessful\n"; this->app_settings.freeglut_settings.translation_by_element = -1; break;

		case INTER_COMMAND_SET_ESTRANGEMENT_CHANGES: std::wcout << L"\tSuccessful\n"; this->app_settings.freeglut_settings.estrangement_changes = VVIS_ESTRAGNEMENT_CHANGES; break;

		case INTER_COMMAND_SET_SCALING_CHANGES:		std::wcout << L"\tSuccessful\n"; 
													this->app_settings.freeglut_settings.scaling_parameters_changes.x = VVIS_SCALING_PARAMETERS_CHANGES_X; 
													this->app_settings.freeglut_settings.scaling_parameters_changes.y = VVIS_SCALING_PARAMETERS_CHANGES_Y; 
													this->app_settings.freeglut_settings.scaling_parameters_changes.z = VVIS_SCALING_PARAMETERS_CHANGES_Z; 
													break;

		case INTER_COMMAND_SET_TRANSLATION_CHANGES:		std::wcout << L"\tSuccessful\n";
														this->app_settings.freeglut_settings.translation_changes.x = VVIS_TRANSLATION_CHANGES_X;
														this->app_settings.freeglut_settings.translation_changes.y = VVIS_TRANSLATION_CHANGES_Y;
														this->app_settings.freeglut_settings.translation_changes.z = VVIS_TRANSLATION_CHANGES_Z;
														break;

		case INTER_COMMAND_SET_CAMERA_CHANGES:	std::wcout << L"\tSuccessful\n";
												this->app_settings.freeglut_settings.camera_changes.x = VVIS_CAMERA_CHANGES_X;
												this->app_settings.freeglut_settings.camera_changes.y = VVIS_CAMERA_CHANGES_Y;
												this->app_settings.freeglut_settings.camera_changes.z = VVIS_CAMERA_CHANGES_Z;
												break;

		case INTER_COMMAND_SET_SPINRATE: std::wcout << L"\tSuccessful\n"; this->app_settings.freeglut_settings.spinrate = 1; break;

		case INTER_COMMAND_SET_SUBWINDOWING:  std::wcout << L"\tSuccessful\n"; this->app_settings.freeglut_settings.use_additional_subwindows = true; break;

		case INTER_COMMAND_SET_GAP: std::wcout << L"\tSuccessful\n"; this->app_settings.freeglut_settings.gap = 7; break;

		case INTER_COMMAND_SET_POLIGONRATE: std::wcout << L"\tSuccessful\n"; this->app_settings.freeglut_settings.polygonrate = 7; break;

		case INTER_COMMAND_SET_MULTIMATERIAL:  std::wcout << L"\tSuccessful\n"; this->app_settings.other_settings.multimaterialing = false; break;
		
		case INTER_COMMAND_SET_MULTILAYER:  std::wcout << L"\tSuccessful\n"; this->app_settings.other_settings.multilayering = false; break;

		case INTER_COMMAND_SET_MATERIAL: if (_commands.size() < 3 || !is_number(_commands[2])) 
											{ std::wcout << L"\tIncorrect format\n"; return false; } 
									   if(remove_material(this->app_settings.other_settings.materials, std::stoi(_commands[2]))) std::wcout << L"\tSuccessful\n";
									   else std::wcout << L"\tUnsuccessful\n";
									   break;

		case INTER_COMMAND_SET_LAYER: if (_commands.size() < 3 || !is_number(_commands[2])) 
											{ std::wcout << L"\tIncorrect format\n"; return false; } 
									   if (remove_layer(this->app_settings.other_settings.layers, std::stoi(_commands[2]))) std::wcout << L"\tSuccessful\n";
									   else std::wcout << L"\tUnsuccessful\n";
									   
									   break;

		case VVIS_UNKNOWW_MAP_SECOND: std::wcout << L"\tUnknow subcommand: " << _commands[1] << L'\n'; return false; break;
		default: break;

	}
	

	return true;
}

bool Interpretator::convert_handler(std::vector<std::wstring> _commands) {
	
	if (_commands.size() < 2) { std::wcout << L"\tEmpty subcommand\n"; return false; }
	
	switch (get_second_from_map(this->convert_sub_command, to_lower_wstr(_commands[1]))) {

		case INTER_COMMAND_CONVERT_VAMPIRE5: {
			bool boolean = false;
			
			boolean = file_exist(this->app_settings.global_settings.path_to_folder + "/" + VVIS_VAMPIRE5_ATOMS_NAME_WSTR + VVIS_VAMPIRE5_ATOMS_FORMAT_WSTR);
			std::wcout << L"\tatoms file exists? : " << std::boolalpha << boolean << L'\n';

			if (!boolean) return false;

			boolean = file_exist(this->app_settings.global_settings.path_to_folder + "/" + VVIS_VAMPIRE5_SPINS_START_NAME_WSTR + v5_get_file_number(std::to_string(this->app_settings.global_settings.number_of_file)) + VVIS_VAMPIRE5_SPINS_FORMAT_WSTR);
			std::wcout << L"\tspins file exists? : " << std::boolalpha << boolean << L'\n';

			if (!boolean) return false;

			std::wcout << L"\tParsing and converting... : ";

			if (v5_parser_converter(this->app_settings.global_settings.path_to_folder, 
								this->app_settings.global_settings.number_of_file))
				std::wcout << "Successful!\n";
			else std::wcout << "Unsuccessful\n";

		} break;

		case VVIS_UNKNOWW_MAP_SECOND: std::wcout << L"\tUnknow subcommand: " << _commands[1] << L'\n'; return false; break;
		default: break;

	}


	return true;
}

bool Interpretator::visualize_handler(std::vector<std::wstring> _commands) {

	if (_commands.size() < 2) { return visualize_handler({ L"visualize", L"folder" }); };

	switch (get_second_from_map(this->visualize_sub_command, to_lower_wstr(_commands[1]))) {
		
		case INTER_COMMAND_VISUALIZE_FOLDER: { 
			bool boolean = false;
			
			boolean = file_exist(this->app_settings.global_settings.path_to_folder + "/" + VVIS_VVIS_FILE_START_NAME_WSTR + v5_get_file_number(std::to_string(this->app_settings.global_settings.number_of_file)) + VVIS_VVIS_FILE_FORMAT_WSTR);
			std::wcout << L"\tsconfiguration file exists? : " << std::boolalpha << boolean << L'\n';

			if (!boolean) return false;

			std::wcout << L"\tloading... : ";

			std::vector<Vertex> vct = sconfiguration_parsing(this->app_settings.global_settings.path_to_folder + "/" + VVIS_VVIS_FILE_START_NAME_WSTR + v5_get_file_number(std::to_string(this->app_settings.global_settings.number_of_file)) + VVIS_VVIS_FILE_FORMAT_WSTR);
			std::wcout << vct.size() << L" vertexes has been loaded\n";
			
			if (this->app_settings.other_settings.multilayering) {
				int l_count = 0;
				std::wcout << L"\tcounting layers... : ";
				l_count = count_of_layers(vct);
				std::wcout << l_count<< L'\n';

				if (this->app_settings.other_settings.layers.size() != l_count) {
					std::wcout << L"\tlayers : ";
					for (int j = 0; j < l_count; ++j) {
						if (!layer_in_vector(this->app_settings.other_settings.layers, j)) {
							Rgb rgb(int_rand_result(0, 255) / 255.0, int_rand_result(0, 255) / 255.0, int_rand_result(0, 255) / 255.0);
							Layer layer(rgb, j);
							this->app_settings.other_settings.layers.push_back(layer);
							std::wcout << j << L" ";
						} 
					} std::wcout << L"- was added\n";
				}

			}

			if (this->app_settings.other_settings.multimaterialing) {
				int m_count = 0;
				std::wcout << L"\tcounting layers... : ";
				m_count = count_of_materials(vct);
				std::wcout << m_count << L'\n';

				if (this->app_settings.other_settings.materials.size() != m_count) {
					std::wcout << L"\tmaterials : ";
					for (int j = 0; j < m_count; ++j) {
						if (!material_in_vector(this->app_settings.other_settings.materials, j)) {
							Rgb rgb(int_rand_result(0, 255) / 255.0, int_rand_result(0, 255) / 255.0, int_rand_result(0, 255) / 255.0);
							Material material(rgb, j);
							this->app_settings.other_settings.materials.push_back(material);
							std::wcout << j << L" ";
						} 
					} std::wcout << L" - was added\n";
				}

			}

			std::wcout << L"\tvisualizing..." << L'\n';
			
			this->app_settings.global_settings.path_to_sconfiguration_file = this->app_settings.global_settings.path_to_folder + "/" + VVIS_VVIS_FILE_START_NAME_WSTR + v5_get_file_number(std::to_string(this->app_settings.global_settings.number_of_file)) + VVIS_VVIS_FILE_FORMAT_WSTR;

			draw_sample(this->app_settings, vct, this->argc, this->argv);

		} break;

		case INTER_COMMAND_VISUALIZE_FILE: {
			bool boolean = false;
			
			boolean = file_exist(this->app_settings.global_settings.path_to_sconfiguration_file);
			std::wcout << L"\tsconfiguration file exists? : " << std::boolalpha << boolean << L'\n';

			if (!boolean) return false;

			if (this->app_settings.global_settings.path_to_settings_file == VVIS_PATH_PLUG_WSTR && 
				this->app_settings.global_settings.path_to_folder == VVIS_PATH_PLUG_WSTR &&
				this->app_settings.global_settings.path_to_settings_file_folder == VVIS_PATH_PLUG_WSTR) {

				std::string filename = VVIS_VVIS_FILE_START_NAME_WSTR + v5_get_file_number(std::to_string(this->app_settings.global_settings.number_of_file)) + VVIS_VVIS_FILE_FORMAT_WSTR;
				std::string path = this->app_settings.global_settings.path_to_sconfiguration_file;
				path.erase(path.end() - filename.size(), path.end()); this->app_settings.global_settings.path_to_settings_file_folder = path;
				std::wcout << L"\tfolder path to settings file : " << str2wstr(this->app_settings.global_settings.path_to_settings_file_folder) << L" has been set up\n";

			}

			std::wcout << L"\tloading...";
			std::vector<Vertex> vct = sconfiguration_parsing(this->app_settings.global_settings.path_to_sconfiguration_file);
			std::wcout << L" : " << vct.size() << L" vertexes has been loaded\n";

			if (this->app_settings.other_settings.multilayering) {
				int l_count = 0;
				std::wcout << L"\tcounting layers... : ";
				l_count = count_of_layers(vct);
				std::wcout << l_count<< L'\n';

				if (this->app_settings.other_settings.layers.size() != l_count) {
					std::wcout << L"\tlayers : ";
					for (int j = 0; j < l_count; ++j) {
						if (!layer_in_vector(this->app_settings.other_settings.layers, j)) {
							Rgb rgb(int_rand_result(0, 255) / 255.0, int_rand_result(0, 255) / 255.0, int_rand_result(0, 255) / 255.0);
							Layer layer(rgb, j);
							this->app_settings.other_settings.layers.push_back(layer);
							std::wcout << j << L" ";
						} 
					} std::wcout << L"- was added\n";
				}

			}

			if (this->app_settings.other_settings.multimaterialing) {
				int m_count = 0;
				std::wcout << L"\tcounting layers... : ";
				m_count = count_of_materials(vct);
				std::wcout << m_count << L'\n';

				if (this->app_settings.other_settings.materials.size() != m_count) {
					std::wcout << L"\tmaterials : ";
					for (int j = 0; j < m_count; ++j) {
						if (!material_in_vector(this->app_settings.other_settings.materials, j)) {
							Rgb rgb(int_rand_result(0, 255) / 255.0, int_rand_result(0, 255) / 255.0, int_rand_result(0, 255) / 255.0);
							Material material(rgb, j);
							this->app_settings.other_settings.materials.push_back(material);
							std::wcout << j << L" ";
						} 
					} std::wcout << L" - was added\n";
				}

			}

			std::wcout << L"\tvisualizing... : " << L'\n';

			draw_sample(this->app_settings, vct, this->argc, this->argv);
		} break;

		case VVIS_UNKNOWW_MAP_SECOND: std::wcout << L"\tUnknow subcommand: " << _commands[1] << L'\n'; return false; break;
		default: break;
	}



	return true;
}

bool set_command_maps(Interpretator& _inter) {

	// subwindow_0 - drawer square
	_inter.app_settings.subwindows.push_back(Window());
	_inter.app_settings.subwindows[0].backgroundcolor = Rgb(230.0 / 255.0, 230.0 / 255.0, 230.0 / 255.0);

	// s_1 - axis
	_inter.app_settings.subwindows.push_back(Window());
	_inter.app_settings.subwindows[1].backgroundcolor = Rgb(230.0 / 255.0, 230.0 / 255.0, 230.0 / 255.0);

	// s_2 - stats
	_inter.app_settings.subwindows.push_back(Window());
	_inter.app_settings.subwindows[2].backgroundcolor = Rgb(230.0 / 255.0, 230.0 / 255.0, 230.0 / 255.0);

	// s_3 - log
	_inter.app_settings.subwindows.push_back(Window());
	_inter.app_settings.subwindows[3].backgroundcolor = Rgb(230.0 / 255.0, 230.0 / 255.0, 230.0 / 255.0);

	_inter.main_command = {
		{L"help", INTER_COMMAND_HELP},
		{L"settings", INTER_COMMAND_SETTINGS}, {L"setting", INTER_COMMAND_SETTINGS}, {L"setgs", INTER_COMMAND_SETTINGS}, {L"setg", INTER_COMMAND_SETTINGS}, {L"sgs", INTER_COMMAND_SETTINGS},
		{L"set", INTER_COMMAND_SET},
		{L"unset", INTER_COMMAND_UNSET}, {L"uset", INTER_COMMAND_HELP_UNSET},
		{L"convert", INTER_COMMAND_CONVERT}, {L"con", INTER_COMMAND_CONVERT},
		{L"visualize", INTER_COMMAND_VISUALIZE}, {L"vis", INTER_COMMAND_VISUALIZE},
		{L"reset", INTER_COMMAND_RESET},
		{L"restart", INTER_COMMAND_RESTART}
	};

	_inter.help_sub_command = {
		{L"settings", INTER_COMMAND_HELP_SETTINGS},
		{L"set", INTER_COMMAND_HELP_SET},
		{L"unset", INTER_COMMAND_HELP_UNSET},
		{L"convert", INTER_COMMAND_HELP_CONVERT},
		{L"visualize", INTER_COMMAND_HELP_VISUALIZE},
		{L"reset", INTER_COMMAND_HELP_RESET},
		{L"restart", INTER_COMMAND_HELP_RESTART}
	};

	_inter.settings_sub_command = {
		{L"show", INTER_COMMAND_SETTINGS_SHOW},
		{L"save", INTER_COMMAND_SETTINGS_SAVE},
		{L"get", INTER_COMMAND_SETTINGS_GET},
		{L"reset", INTER_COMMAND_SETTINGS_RESET}
	};

	_inter.settings_show_sub_command = {
		{L"all", INTER_COMMAND_SETTINGS_SHOW_ALL},
		{L"console", INTER_COMMAND_SETTINGS_SHOW_CONSOLE},
		{L"window", INTER_COMMAND_SETTINGS_SHOW_FREEGLUT},
		{L"default", INTER_COMMAND_SETTINGS_SHOW_DEFAULT}
	};

	_inter.set_sub_command = {
		{L"folderpath", INTER_COMMAND_SET_FOLDERPATH}, {L"folpath", INTER_COMMAND_SET_FOLDERPATH}, {L"folp", INTER_COMMAND_SET_FOLDERPATH}, {L"folderp", INTER_COMMAND_SET_FOLDERPATH},
		{L"filepath", INTER_COMMAND_SET_FILEPATH}, {L"fpath", INTER_COMMAND_SET_FILEPATH}, {L"fp", INTER_COMMAND_SET_FILEPATH}, {L"filep", INTER_COMMAND_SET_FILEPATH},
		{L"filenumber", INTER_COMMAND_SET_FILENUMBER}, {L"fnumber", INTER_COMMAND_SET_FILENUMBER}, {L"fn", INTER_COMMAND_SET_FILENUMBER}, {L"filen", INTER_COMMAND_SET_FILENUMBER},
		{L"spinindex", INTER_COMMAND_SET_SPININDEX}, {L"sindex", INTER_COMMAND_SET_SPININDEX}, {L"si", INTER_COMMAND_SET_SPININDEX}, {L"spini", INTER_COMMAND_SET_SPININDEX},
		{L"settingsfolder", INTER_COMMAND_SET_SETTINGSFOLDER}, {L"sgsfolder", INTER_COMMAND_SET_SETTINGSFOLDER}, {L"sgsfol", INTER_COMMAND_SET_SETTINGSFOLDER},
		{L"settingsfile", INTER_COMMAND_SET_SETTINGSFILE}, {L"sgsfile", INTER_COMMAND_SET_SETTINGSFILE}, {L"sgsf", INTER_COMMAND_SET_SETTINGSFILE},
		{L"coloring", INTER_COMMAND_SET_COLORING}, {L"cg", INTER_COMMAND_SET_COLORING},
		{L"backgroundcolor", INTER_COMMAND_SET_BACKGROUNDCOLOR}, {L"bgc", INTER_COMMAND_SET_BACKGROUNDCOLOR},
		{L"fullscreen", INTER_COMMAND_SET_FULLSCREEN},
		{L"shape",	INTER_COMMAND_SET_SHAPE},
		{L"translationbyelement", INTER_COMMAND_SET_TRANSLATION_BY_ELEMENT}, {L"tbe", INTER_COMMAND_SET_TRANSLATION_BY_ELEMENT},
		{L"estrangementchanges", INTER_COMMAND_SET_ESTRANGEMENT_CHANGES}, {L"echanges", INTER_COMMAND_SET_ESTRANGEMENT_CHANGES}, {L"ech", INTER_COMMAND_SET_ESTRANGEMENT_CHANGES},
		{L"scalingchanges", INTER_COMMAND_SET_SCALING_CHANGES}, {L"schanges", INTER_COMMAND_SET_SCALING_CHANGES}, {L"sch", INTER_COMMAND_SET_SCALING_CHANGES},
		{L"translationchanges", INTER_COMMAND_SET_TRANSLATION_CHANGES}, {L"tchanges", INTER_COMMAND_SET_TRANSLATION_CHANGES}, {L"tch", INTER_COMMAND_SET_TRANSLATION_CHANGES},
		{L"camerachanges", INTER_COMMAND_SET_CAMERA_CHANGES}, {L"cchanges", INTER_COMMAND_SET_CAMERA_CHANGES}, {L"cch", INTER_COMMAND_SET_CAMERA_CHANGES},
		{L"spinrate", INTER_COMMAND_SET_SPINRATE}, {L"spinr", INTER_COMMAND_SET_SPINRATE}, {L"sr", INTER_COMMAND_SET_SPINRATE}, {L"srate", INTER_COMMAND_SET_SPINRATE},
		{L"subwindowing", INTER_COMMAND_SET_SUBWINDOWING}, {L"subwg", INTER_COMMAND_SET_SUBWINDOWING},
		{L"gap", INTER_COMMAND_SET_GAP},
		{L"polygonrate", INTER_COMMAND_SET_POLIGONRATE}, {L"pr", INTER_COMMAND_SET_POLIGONRATE},
		{L"layer", INTER_COMMAND_SET_LAYER},
		{L"material", INTER_COMMAND_SET_MATERIAL},
		{L"multimaterial", INTER_COMMAND_SET_MULTIMATERIAL},
		{L"multilayer", INTER_COMMAND_SET_MULTILAYER}
	};

	_inter.convert_sub_command = {
		{L"vampire5", INTER_COMMAND_CONVERT_VAMPIRE5}, {L"v5", INTER_COMMAND_CONVERT_VAMPIRE5}, {L"v6", INTER_COMMAND_CONVERT_VAMPIRE5}, {L"vampire6", INTER_COMMAND_CONVERT_VAMPIRE5}
	};

	_inter.visualize_sub_command = {
		{L"folder", INTER_COMMAND_VISUALIZE_FOLDER},
		{L"file", INTER_COMMAND_VISUALIZE_FILE},
	};

	return true;
}
