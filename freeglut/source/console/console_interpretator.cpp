#include "./console_interpretator.hpp"


Interpretator::Interpretator() {
	this->prompt = L"vvis > ";
	set_command_maps(*this);
}

unsigned char Interpretator::loop(int argc, char** argv, std::vector<std::wstring> _commands) {
	print_logo(std::wcout);
	std::wstring str;
	std::vector<std::wstring> command_vector;

	do {
		if (_commands.empty()) {
			std::wcout << this->prompt; std::getline(std::wcin, str);
			command_vector = line_to_vector(str); 
		} else {
			command_vector = _commands; _commands = {};
		}

		if (by_synonyms(str) == L"exit") break;

		if (command_vector.size() < 1) continue;

		switch (get_second_from_map(this->main_command, to_lower_wstr(command_vector[0]))) {
			case INTER_COMMAND_HELP:		std::wcout << L'\n'; if (!this->help_handler(command_vector)) std::wcout << "\tUnsuccessfully\n"; std::wcout << std::endl;		break;
			case INTER_COMMAND_SETTINGS:	std::wcout << L'\n'; if (!this->settings_handler(command_vector)) std::wcout << "\tUnsuccessfully\n"; std::wcout << std::endl;	break;
			case INTER_COMMAND_RESTART:		std::wcout << L'\n'; if (!this->restart_handler(command_vector)) std::wcout << "\tUnsuccessfully\n"; else goto end_2; std::wcout << std::endl;	break;
			case INTER_COMMAND_RESET:		std::wcout << L'\n'; if (!this->reset_handler(command_vector)) std::wcout << "\tUnsuccessfully\n"; std::wcout << std::endl;	break;
			case INTER_COMMAND_SET:			std::wcout << L'\n'; if (!this->set_handler(command_vector)) std::wcout << "\tUnsuccessfully\n"; std::wcout << std::endl;		break;
			case INTER_COMMAND_UNSET:		std::wcout << L'\n'; if (!this->unset_handler(command_vector)) std::wcout << "\tUnsuccessfully\n"; std::wcout << std::endl;		break;
			
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

		case VVIS_UNKNOWW_MAP_SECOND: std::wcout << L"\tUnknow subcommand: " << _commands[1] << L'\n'; return false; break;
		default: break;

	}

	return true;
}

bool Interpretator::help_handler(std::vector<std::wstring> _commands) {
	// TODO: help
	std::wcout << "\tWIP settings show {all, console, window, <nothing>} / save / get" << L'\n';
	std::wcout << "\tWIP reset" << L'\n';
	std::wcout << "\tWIP restart" << L'\n';
	std::wcout << "\tWIP set" << L'\n';
	std::wcout << "\tWIP unset" << L'\n';
	return true;
}

bool Interpretator::reset_handler(std::vector<std::wstring> _commands) {
	this->app_settings = Settings();
	std::wcout << L"\t Successful\n";
	return true;
}

bool Interpretator::restart_handler(std::vector<std::wstring> _commands) {
	this->app_settings = Settings();
	std::wcout << L"\t Successful\n";
	return true;
}

bool Interpretator::set_handler(std::vector<std::wstring> _commands) {
	
	if (_commands.size() < 2) { std::wcout << L"\tEmpty subcommand\n"; return false; }
	
	switch (get_second_from_map(this->set_sub_command, to_lower_wstr(_commands[1]))) {
	
		case INTER_COMMAND_SET_FOLDERPATH: { 
			if (_commands.size() < 3) { std::wcout << L"\tEmpty path\n"; return false; }
			if (_commands[2].size() > 0) {
				remove_quotations(_commands[2]);
				this->app_settings.global_settings.path_to_folder = _commands[2];
				std::wcout << L"\tPath to folder \"" << this->app_settings.global_settings.path_to_folder << L"\" has been set up\n";
			} else std::wcout << L"\n\tEmpty path\n";
		} break;
		
		case INTER_COMMAND_SET_FILEPATH: {
			if (_commands.size() < 3) { std::wcout << L"\tEmpty path\n"; return false; }
			if (!contains_subwstr(_commands[2], VVIS_VVIS_FILE_FORMAT) || !contains_subwstr(_commands[2], VVIS_VVIS_FILE_NAME_STR)) { std::wcout << L"\tWrong file name\n"; return false; }
			if (_commands[2].size() > 0) {
				remove_quotations(_commands[2]);
				this->app_settings.global_settings.path_to_sconfiguration_file = _commands[2];
				std::wcout << L"\tPath to sconfiguration file \"" << this->app_settings.global_settings.path_to_sconfiguration_file << L"\" has been set up\n";
			} else std::wcout << L"\n\tEmpty path\n";
		} break;

		case INTER_COMMAND_SET_FILENUMBER: if (!is_number(_commands[2])) { std::wcout << L"\tNot number\n"; return false; }
							else { this->app_settings.global_settings.number_of_file = std::stoi(_commands[2]);
						std::wcout << L"\tFile number \"" << this->app_settings.global_settings.number_of_file << L"\" has been set up\n"; } break;

		case INTER_COMMAND_SET_SPININDEX: if (!is_number(_commands[2])) { std::wcout << L"\tNot number\n"; return false; }
							else { this->app_settings.global_settings.index_of_spin = std::stoi(_commands[2]);
						std::wcout << L"\tSpin index \"" << this->app_settings.global_settings.index_of_spin << L"\" has been set up\n"; } break;

		case INTER_COMMAND_SET_SETTINGSFOLDER : {
			if (_commands.size() < 3) { std::wcout << L"\tEmpty path\n"; return false; }
			if (_commands[2].size() > 0) {
				remove_quotations(_commands[2]);
				this->app_settings.global_settings.path_to_settings_file_folder = _commands[2];
				std::wcout << L"\tPath to settings folder \"" << this->app_settings.global_settings.path_to_settings_file_folder << L"\" has been set up\n";
			} else std::wcout << L"\n\tEmpty path\n";
		} break;

		case INTER_COMMAND_SET_SETTINGSFILE: {
			if (_commands.size() < 3) { std::wcout << L"\tEmpty path\n"; return false; }
			if (!contains_subwstr(_commands[2], VVIS_SETTINGS_FILE_NAME_WSTR)) { std::wcout << L"\tWrong file name\n"; return false; }
			if (_commands[2].size() > 0) {
				remove_quotations(_commands[2]);
				this->app_settings.global_settings.path_to_settings_file = _commands[2];
				std::wcout << L"\tPath to settings file \"" << this->app_settings.global_settings.path_to_settings_file << L"\" has been set up\n";
			} else std::wcout << L"\n\tEmpty path\n";
		} break;


		case INTER_COMMAND_SET_COLORING: if (_commands.size() < 3) { std::wcout << L"\tEmpty instruction\n"; return false; } 
									   this->app_settings.freeglut_settings.coloring_sample = by_synonyms(_commands[2]) == L"yes" ? true : false;
									   std::wcout << L"\tColoring setting \"" << this->app_settings.freeglut_settings.coloring_sample << L"\" has been set up\n";
									   break;


		case INTER_COMMAND_SET_BACKGROUNDCOLOR: if (_commands.size() < 5 || !is_number(_commands[2]) || !is_number(_commands[3])
											|| !is_number(_commands[4]) || std::stod(_commands[2]) > 255 || std::stod(_commands[3]) > 255
											|| std::stod(_commands[4]) > 255) { std::wcout << L"\tIncorrect format\n"; return false; } 
											  
											  this->app_settings.freeglut_settings.backgroundcolor.red = std::stod(_commands[2]) / 255.0;
											  this->app_settings.freeglut_settings.backgroundcolor.green = std::stod(_commands[3]) / 255.0;
											  this->app_settings.freeglut_settings.backgroundcolor.blue = std::stod(_commands[4]) / 255.0;
											  
											  std::wcout << L"\tColoring background (" 
												  << this->app_settings.freeglut_settings.backgroundcolor.red * 255.0 << ", "
												  << this->app_settings.freeglut_settings.backgroundcolor.green * 255.0 << ", "
												  << this->app_settings.freeglut_settings.backgroundcolor.blue * 255.0
												  << L") has been set up\n";
											  
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

		case INTER_COMMAND_SET_FILENUMBER: std::wcout << L"\tSuccessful\n"; this->app_settings.global_settings.number_of_file = VVIS_INT_PLUG_WSTR; break;

		case INTER_COMMAND_SET_SPININDEX: std::wcout << L"\tSuccessful\n"; this->app_settings.global_settings.index_of_spin = VVIS_DRAW_ALL; break;

		case INTER_COMMAND_SET_SETTINGSFILE: std::wcout << L"\tSuccessful\n"; this->app_settings.global_settings.path_to_settings_file = VVIS_PATH_PLUG_WSTR; break;

		case INTER_COMMAND_SET_SETTINGSFOLDER: std::wcout << L"\tSuccessful\n"; this->app_settings.global_settings.path_to_settings_file_folder = VVIS_PATH_PLUG_WSTR; break;

		case INTER_COMMAND_SET_COLORING: std::wcout << L"\tSuccessful\n"; this->app_settings.freeglut_settings.coloring_sample = false; break;

		case INTER_COMMAND_SET_BACKGROUNDCOLOR: std::wcout << L"\tSuccessful\n"; this->app_settings.freeglut_settings.backgroundcolor = RGB(1.0, 1.0, 1.0); break;

		case VVIS_UNKNOWW_MAP_SECOND: std::wcout << L"\tUnknow subcommand: " << _commands[1] << L'\n'; return false; break;
		default: break;

	}
	

	return true;
}

bool set_command_maps(Interpretator& _inter) {
	
	_inter.main_command = {
		{L"help", INTER_COMMAND_HELP},
		{L"settings", INTER_COMMAND_SETTINGS},
		{L"set", INTER_COMMAND_SET},
		{L"unset", INTER_COMMAND_UNSET},
		{L"convert", INTER_COMMAND_CONVERT},
		{L"visualize", INTER_COMMAND_VISUALIZE},
		{L"reset", INTER_COMMAND_RESET},
		{L"restart", INTER_COMMAND_RESTART}
	};

	_inter.settings_sub_command = {
		{L"show", INTER_COMMAND_SETTINGS_SHOW},
		{L"save", INTER_COMMAND_SETTINGS_SAVE},
		{L"get", INTER_COMMAND_SETTINGS_GET}
	};

	_inter.settings_show_sub_command = {
		{L"all", INTER_COMMAND_SETTINGS_SHOW_ALL},
		{L"console", INTER_COMMAND_SETTINGS_SHOW_CONSOLE},
		{L"window", INTER_COMMAND_SETTINGS_SHOW_FREEGLUT},
		{L"default", INTER_COMMAND_SETTINGS_SHOW_DEFAULT}
	};

	_inter.set_sub_command = {
		{L"folderpath", INTER_COMMAND_SET_FOLDERPATH},
		{L"filepath", INTER_COMMAND_SET_FILEPATH},
		{L"filenumber", INTER_COMMAND_SET_FILENUMBER},
		{L"spinindex", INTER_COMMAND_SET_SPININDEX},
		{L"settingsfolder", INTER_COMMAND_SET_SETTINGSFOLDER},
		{L"settingsfile", INTER_COMMAND_SET_SETTINGSFILE},
		{L"coloring", INTER_COMMAND_SET_COLORING},
		{L"backgroundcolor", INTER_COMMAND_SET_BACKGROUNDCOLOR}
	};

	return true;
}
