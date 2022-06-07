#include "./include/main_inter.hpp" 

Interpretator::Interpretator() {
	this->prompt = ex_prompt;
}

Interpretator::Interpretator(const std::wstring& _PROMPT, const vvis::app::Settings& settings) {
	this->prompt = _PROMPT;
	this->settings = settings;
}

void print_visualis_logo() {

	std::wcout << L"\n    ____   ____.___  _____________ ___  _____  .____    .___  _________ " << L"\n";
	std::wcout << L"    \\   \\ /   /|   |/   _____/    |   \\/  _  \\ |    |   |   |/  _____/  " << L"\n";
	std::wcout << L"     \\   Y   / |   |\\_____  \\|    |   /  /_\\  \\|    |   |   |\\_____ \\   " << L"\n";
	std::wcout << L"      \\     /  |   |/        \\    |  /    |    \\    |___|   |/       \\  " << L"\n";
	std::wcout << L"       \\___/   |___/_______  /______/\\____|__  /_______ \\___/_______ /  " << L"\n";
	std::wcout << L"                           \\/                \\/        \\/          \\/   " << L"\n" << std::endl;

}

std::wstring _prompt() {
	return std::wstring(L"vis > ");
}

std::wstring tolower_wstr(std::wstring& _value) {
	std::transform(_value.begin(), _value.end(), _value.begin(), std::tolower);
	return std::wstring(_value);
}

bool is_number(const std::wstring& s) {
	return !s.empty() && std::find_if(s.begin(),
		s.end(), [](wchar_t c) { return !(std::isdigit(c) || c == L'0'); }) == s.end();
}

void remove_quotation(std::wstring& str) {
	if ((str[0] == L'\"' && str[str.size() - 1] == L'\"') ||
		(str[0] == L'\'' && str[str.size() - 1] == L'\'')) {
		str.pop_back(); str = str.substr(1);
	}
}

std::wstring Interpretator::get_command_for_error(const std::wstring& _value) {
	return _value == L"" ? L"<nothing>" : L"\"" + _value + L"\"";
}

int Interpretator::switch_code_of_operation(std::map<std::wstring, int> mapp, std::wstring& _value) {
	std::map<std::wstring, int>::iterator it = mapp.find(tolower_wstr(_value));
	return it == mapp.end() ? UNKNOW_COMMAND : it->second;
}

void Interpretator::set_number_from_file_name(const std::wstring& _path) {
	size_t a = _path.find(START_OF_OUR_FILE);
	this->settings.global_settings.number_of_file = std::stoi(_path.substr(a + 15, 8));
}

std::wstring by_synonyms(const std::wstring& _value) {
	std::wstring copy_value = _value; tolower_wstr(copy_value);

	std::vector<std::wstring> exit = {L"exit", L"(exit)", L"exit.", L"end"};
	std::vector<std::wstring> yes = {L"y", L"yes", L"yes.", L"yep", L"1", L"true"};
	std::vector<std::wstring> no = {L"n", L"no", L"not.", L"nope", L"0", L"false"};
	
	
	std::vector<std::wstring>::iterator it = std::find(exit.begin(), exit.end(), copy_value);
	if (it != exit.end()) return L"exit";
	
	it = std::find(yes.begin(), yes.end(), copy_value);
	if (it != yes.end()) return L"yes";
	
	it = std::find(no.begin(), no.end(), copy_value);
	if (it != no.end()) return L"no";
	
	return _value;

}

void Interpretator::loop(int argc, char** argv) {
	std::wstring line;

	// приглашение ввода и ввод
	

	while (true) {
		
		std::wcout << this->prompt; std::getline(std::wcin, line);
		// отсекаем выход
		if (by_synonyms(line) == L"exit") { break; }
		if (line == L"" | line == L"\n") continue;

		std::wstringstream ss; ss.str(line); line = L"";
		ss >> line;

		switch (switch_code_of_operation(this->main_command, line)) {


			case COMMAND_SETTINGS: {
				line = L""; if (ss.eof()) ss.str(L""); else ss >> line;

				switch (switch_code_of_operation(this->subSettings_command, line)) {
					

					case SUBCOMMAND_SAVE_SETTINGS: {
						line = L""; if (ss.eof()) ss.str(L""); else ss >> line;
						
						if (this->settings.global_settings.path_to_folder == INTERPETATOR_PATH_PLUG_WSTR && this->settings.global_settings.path_to_settings_file_folder == INTERPETATOR_PATH_PLUG_WSTR) {
							std::wcout << "\n\t ERROR: first initialize one of the paths (to settings or to folder)\n" << std::endl;
							break;
						}

						this->settings.save_settings();
						
						if (this->settings.global_settings.path_to_settings_file_folder != INTERPETATOR_PATH_PLUG_WSTR) std::wcout << "\n\tSuccsesful\n" << std::endl;
						else std::wcout << "\n\tUnsuccsesful\n" << std::endl;
					} break;
					
					case SUBCOMMAND_GET_SETTINGS: {
						line = L""; if (ss.eof()) ss.str(L""); else ss >> line;
						
						bool Bol = file_exist(this->settings.global_settings.path_to_settings_file_folder + L"/" + VISUALIS_SETTINGS_JSON);
						if (!Bol) { std::wcout << "\n\t ERROR: file doesnt exist\n" << std::endl; break; }
						
						this->settings.get_settings();
						
						if(this->settings.global_settings.path_to_settings_file_folder != INTERPETATOR_PATH_PLUG_WSTR) std::wcout << "\n\tSuccsesful\n" << std::endl;
						else std::wcout << "\n\tUnsuccsesful (settingspath has not been set up)\n" << std::endl;
					} break;

					case UNKNOW_COMMAND: {
						std::wcout << L"\n\tERROR: Unknow subcommand for \"settings\": " << this->get_command_for_error(line) << L"\n" << std::endl;
					} break;

					default: {} break;

				}				

			} break;
















			case COMMAND_SET: {
				
				line = L""; if (ss.eof()) ss.str(L""); else ss >> line;

				switch (switch_code_of_operation(this->subSet_command, line)) {

					
					case SUBCOMMAND_SET_FOLDERPATH : {
						line = L""; if (ss.eof()) ss.str(L""); else ss >> line;

						this->settings.global_settings.path_to_folder = (line == L"")? INTERPETATOR_PATH_PLUG_WSTR : line;
						
						remove_quotation(this->settings.global_settings.path_to_folder);

						std::wcout << L"\n\tPath to folder : " << this->settings.global_settings.path_to_folder << L" : has been set up\n";
						if (this->settings.global_settings.path_to_folder == INTERPETATOR_PATH_PLUG_WSTR) std::wcout << L"\tERROR: path was not entered\n";
						std::wcout<< std::endl;


					} break;

					case SUBCOMMAND_SET_FILENUMBER: {
						line = L""; if (ss.eof()) ss.str(L""); else ss >> line;

						this->settings.global_settings.number_of_file = (!is_number(line))? INTERPETATOR_NUMBER_PLUG_INT : std::stoi(line);

						std::wcout << L"\n\tNumber of file : " << this->settings.global_settings.number_of_file << L" : has been set up\n";
						if (this->settings.global_settings.number_of_file == INTERPETATOR_NUMBER_PLUG_INT) std::wcout << L"\tERROR: not number\n";
						std::wcout<< std::endl;


					} break;

					case SUBCOMMAND_SET_FILEPATH: {
						line = L""; if (ss.eof()) ss.str(L""); else ss >> line;
						
						this->settings.global_settings.path_to_sconfiguration_file = (line.size() <= 10 ||
							(line.find(FORMAT_OF_OUR_FILE) == std::wstring::npos || line.find(START_OF_OUR_FILE) == std::wstring::npos)) ?
								 INTERPETATOR_PATH_PLUG_WSTR : line;
						
						remove_quotation(this->settings.global_settings.path_to_sconfiguration_file);

						if (settings.global_settings.path_to_sconfiguration_file != INTERPETATOR_PATH_PLUG_WSTR) {
							std::wstring file = vvis::creator::get_file_name(this->settings.global_settings.number_of_file) + FORMAT_OF_OUR_FILE;
							std::wstring path = this->settings.global_settings.path_to_sconfiguration_file;
							path.erase(path.end() - file.size(), path.end()); this->settings.global_settings.path_to_folder = path;
						}

						std::wcout << L"\n\tPath to sconfiguration file : " << this->settings.global_settings.path_to_sconfiguration_file << L" : has been set up\n";
						if (this->settings.global_settings.path_to_sconfiguration_file == INTERPETATOR_PATH_PLUG_WSTR) std::wcout << L"\tERROR: path was not entered or incorrectly\n";
						std::wcout << std::endl;


					} break;

					case SUBCOMMAND_SET_COLORING: {
						line = L""; if (ss.eof()) ss.str(L""); else ss >> line;

						if (L"yes" == by_synonyms(line)) this->settings.global_settings.using_color = true;
						else if (L"no" == by_synonyms(line)) this->settings.global_settings.using_color = false;

						std::wcout << L"\n\tColoring mode : " << std::boolalpha << this->settings.global_settings.using_color << L" : has been set up\n";
						std::wcout << std::endl;
					} break;


					case SUBCOMMAND_SET_BACKGROUNDCOLOR: {
						for (int j = 0; j < 3; ++j) {
							line = L""; if (ss.eof()) { ss.str(L""); break; } else ss >> line;
							if (j == 0) this->settings.global_settings.background.red = (!is_number(line) || std::stoi(line) >= 255) ? 1 : std::stoi(line)/255.;
							if (j == 1) this->settings.global_settings.background.green = (!is_number(line) || std::stoi(line) >= 255) ? 1 : std::stoi(line)/255.;
							if (j == 2) this->settings.global_settings.background.blue = (!is_number(line) || std::stoi(line) >= 255) ? 1 : std::stoi(line)/255.;
						}

						std::wcout << L"\n\tColoring background : " << this->settings.global_settings.background.red << L"*255 " << this->settings.global_settings.background.green << L"*255 "
							<< this->settings.global_settings.background.blue << L"*255 : has been set up\n";
						std::wcout << std::endl;
					} break;

					case SUBCOMMAND_SET_SETTINGS_PATH: {
						line = L""; if (ss.eof()) ss.str(L""); else ss >> line;

						this->settings.global_settings.path_to_settings_file_folder = (line == L"") ? INTERPETATOR_PATH_PLUG_WSTR : line;

						remove_quotation(this->settings.global_settings.path_to_settings_file_folder);

						std::wcout << L"\n\tPath to settings file folder : " << this->settings.global_settings.path_to_settings_file_folder << L" : has been set up\n";
						if (this->settings.global_settings.path_to_settings_file_folder == INTERPETATOR_PATH_PLUG_WSTR) std::wcout << L"\tERROR: path was not entered or incorrectly\n";
						std::wcout << std::endl;

					} break;

					
					case UNKNOW_COMMAND: {
						std::wcout << L"\n\tERROR: Unknow subcommand for \"set\": " << this->get_command_for_error(line) << L"\n" << std::endl;
					} break;

					default: {} break;
				}

			} break;
		






			case COMMAND_UNSET: {
				line = L""; if (ss.eof()) ss.str(L""); else ss >> line;

				switch (switch_code_of_operation(this->subSet_command, line)) {

					case SUBCOMMAND_SET_FOLDERPATH: {
						this->settings.global_settings.path_to_folder = INTERPETATOR_PATH_PLUG_WSTR;

						std::wcout << L"\n\tPath to folder : " << this->settings.global_settings.path_to_folder << L" : has been set up\n";
						std::wcout << std::endl;
					} break;

					case SUBCOMMAND_SET_FILEPATH: {
						this->settings.global_settings.path_to_sconfiguration_file = INTERPETATOR_PATH_PLUG_WSTR;

						std::wcout << L"\n\tPath to sconfiguration file : " << this->settings.global_settings.path_to_sconfiguration_file << L" : has been set up\n";
						std::wcout << std::endl;
					} break;

					case SUBCOMMAND_SET_FILENUMBER: {
						this->settings.global_settings.number_of_file = INTERPETATOR_NUMBER_PLUG_INT;

						std::wcout << L"\n\tNumber of file : " << this->settings.global_settings.number_of_file << L" : has been set up\n";
						std::wcout << std::endl;
					} break;

					case SUBCOMMAND_SET_COLORING: {
						this->settings.global_settings.using_color = false;

						std::wcout << L"\n\tColoring mode : " << std::boolalpha << this->settings.global_settings.using_color << L" : has been set up\n";
						std::wcout << std::endl;
					} break;

					case SUBCOMMAND_SET_BACKGROUNDCOLOR: {
						this->settings.global_settings.background = vvis::visualization::VvisColor_3f(1, 1, 1);

						std::wcout << L"\n\tColoring background : " << this->settings.global_settings.background.red << L"*255 " << this->settings.global_settings.background.green << L"*255 "
							<< this->settings.global_settings.background.blue << L"*255 : has been set up\n";
						std::wcout << std::endl;
					} break;

					case SUBCOMMAND_SET_SETTINGS_PATH: {
						this->settings.global_settings.path_to_settings_file_folder = INTERPETATOR_PATH_PLUG_WSTR;

						std::wcout << L"\n\tPath to settings file : " << this->settings.global_settings.path_to_settings_file_folder << L" : has been set up\n";
						std::wcout << std::endl;
					} break;

					case UNKNOW_COMMAND: {
						std::wcout << L"\n\tERROR: Unknow subcommand for \"unset\": " << this->get_command_for_error(line) << L"\n" << std::endl;
					} break;

					default: {} break;
				}
			} break;








			case COMMAND_CONVERT: {
				line = L""; if (ss.eof()) ss.str(L""); else ss >> line;

				switch (switch_code_of_operation(this->subConvert_command, line)) {
					
					case SUBCOMMAND_CONVERT_VAMPIRE6: {
						//TODO: кроссплатформенность?
						bool Bol = false;
						std::wcout << L"\n";
						std::wcout << L"\tPath to folder : " << this->settings.global_settings.path_to_folder << L"\n";
						std::wcout << L"\tFile number : " << this->settings.global_settings.number_of_file << L"\n";

						Bol = file_exist(this->settings.global_settings.path_to_folder + L"/" + NAME_OF_ATOMS_FILE_V5 + FORMAT_OF_ATOMS_FILE_V5);
						std::wcout << L"\tFile " << NAME_OF_ATOMS_FILE_V5 << FORMAT_OF_ATOMS_FILE_V5 << " exists : "

							<< std::boolalpha << Bol << "\n";
						
						Bol = file_exist(this->settings.global_settings.path_to_folder + L"/" + vampire5::parser::get_spin_file_name(this->settings.global_settings.number_of_file) + FORMAT_OF_SPINS_FILE_V5);
						std::wcout << L"\tFile " << vampire5::parser::get_spin_file_name(this->settings.global_settings.number_of_file) << FORMAT_OF_SPINS_FILE_V5 << " exists : "

							<< std::boolalpha << Bol << L"\n";

						if (!Bol) { std::wcout << std::endl; break; }

						std::wcout << L"\tParsing... : ";
							std::wstring fstr = vampire5::parser::get_string(this->settings.global_settings.path_to_folder)(this->settings.global_settings.number_of_file);
						std::wcout << (fstr.size() != 0 ? L"Succsesfully\n" : L"Unsuccessfully\n");

						if (fstr.size() == 0) { std::wcout << std::endl; break; }

						std::wcout << L"\tConverting... : ";
						std::wcout << (vampire5::converter::convert(fstr, this->settings.global_settings.path_to_folder) ? L"Succsesfully\n" : L"Unsuccessfully\n");

						std::wcout << std::endl;
					} break;

					case UNKNOW_COMMAND: {
						std::wcout << L"\n\tERROR: Unknow subcommand for \"convert\": " << this->get_command_for_error(line) << L"\n" << std::endl;
					} break;

					default: {} break;
				}
			} break;







			case COMMAND_VISUALIZE: {
				line = L""; if (ss.eof()) ss.str(L""); else ss >> line;

				switch (switch_code_of_operation(this->subVisualize_command, line)) {



					case SUBCOMMAND_VISUALIZE_BY_FILE: {

						bool Bol = false;

						std::wcout << L"\n";
						std::wcout << L"\tPath to file : " << this->settings.global_settings.path_to_sconfiguration_file << L"\n";

						Bol = file_exist(this->settings.global_settings.path_to_sconfiguration_file);

						this->set_number_from_file_name(this->settings.global_settings.path_to_sconfiguration_file);

						std::wstring file = vvis::creator::get_file_name(this->settings.global_settings.number_of_file) + FORMAT_OF_OUR_FILE;

						std::wcout << L"\tFile " << file << L" exists : "
							<< std::boolalpha << Bol << "\n";

						if (!Bol) { std::wcout << std::endl; break; }

						//это инициализируется ещё при инициализации filepath
						//std::wstring path = this->settings.path_to_sconfiguration_file;
						//path.erase(path.end() - file.size(), path.end()); this->settings.path_to_folder = path;

						std::wcout << L"\tParsing... : ";
							std::vector <vvis::creator::Vertex> vect = vvis::creator::create_arry(this->settings.global_settings.path_to_folder)(this->settings.global_settings.number_of_file);
						std::wcout << (vect.size() != 0 ? L"Succsesfully\n" : L"Unsuccessfully\n");
						std::wcout << L"\tLoaded " << vect.size() << L" spins\n";
							vvis::visualization::app_freeglut app(vect, this->settings.global_settings.shape, this->settings.global_settings.using_color, this->settings.global_settings.background, this->settings.global_settings.index_of_spin, this->settings.global_settings.path_to_folder, this->settings.global_settings.path_to_settings_file_folder + L"/" + VISUALIS_SETTINGS_JSON);

						std::wcout << L"\tDrawing... \n";
							vvis::visualization::draw_sample(app, argc, argv);

						std::wcout << std::endl;
					} break;






					case SUBCOMMAND_VISUALIZE_BY_FOLDER: {

						bool Bol = false;

						std::wcout << L"\n";
						std::wcout << L"\tPath to folder : " << this->settings.global_settings.path_to_folder << L"\n";
						std::wstring file = vvis::creator::get_file_name(this->settings.global_settings.number_of_file) + FORMAT_OF_OUR_FILE;

						Bol = file_exist(this->settings.global_settings.path_to_folder + L"/" + file);

						std::wcout << L"\tFile " << file << L" exists : "
							<< std::boolalpha << Bol << "\n";

						if (!Bol) { std::wcout << std::endl; break; }
						
						std::wcout << L"\tParsing... : ";
							std::vector <vvis::creator::Vertex> vect = vvis::creator::create_arry(this->settings.global_settings.path_to_folder)(this->settings.global_settings.number_of_file);
						std::wcout << (vect.size() != 0 ? L"Succsesfully\n" : L"Unsuccessfully\n");
						std::wcout << L"\tLoaded " << vect.size() << L" spins\n";
							vvis::visualization::app_freeglut app(vect, this->settings.global_settings.shape, this->settings.global_settings.using_color, this->settings.global_settings.background, this->settings.global_settings.index_of_spin, this->settings.global_settings.path_to_folder, this->settings.global_settings.path_to_settings_file_folder + L"/" + VISUALIS_SETTINGS_JSON);

						std::wcout << L"\tDrawing... \n";
							vvis::visualization::draw_sample(app, argc, argv);

						std::wcout << std::endl;

					} break;





					case UNKNOW_COMMAND: {
						std::wcout << L"\n\tERROR: Unknow subcommand for \"visualize\": " << this->get_command_for_error(line) << L"\n" << std::endl;
					} break;

					default: {} break;

				};


			} break;













			case COMMAND_RESTART :{
				this->settings.global_settings.number_of_file = INTERPETATOR_NUMBER_PLUG_INT;
				this->settings.global_settings.path_to_folder = INTERPETATOR_PATH_PLUG_WSTR;
				this->settings.global_settings.path_to_sconfiguration_file = INTERPETATOR_PATH_PLUG_WSTR;
				this->settings.global_settings.using_color = false;
				this->settings.global_settings.shape = SHAPE_CONE;
				this->settings.global_settings.shape_str = SHAPE_CONE_STR;
				this->settings.global_settings.index_of_spin = DRAW_ALL;
				this->settings.global_settings.background = vvis::visualization::VvisColor_3f(1, 1, 1);
				this->settings.global_settings.path_to_settings_file_folder = INTERPETATOR_PATH_PLUG_WSTR;
				Assert(false, L"Restarting the program", L"The settings have been reset ");
			} break;

			case COMMAND_RESET: {
				this->settings.global_settings.number_of_file = INTERPETATOR_NUMBER_PLUG_INT;
				this->settings.global_settings.path_to_folder = INTERPETATOR_PATH_PLUG_WSTR;
				this->settings.global_settings.path_to_sconfiguration_file = INTERPETATOR_PATH_PLUG_WSTR;
				this->settings.global_settings.using_color = false;
				this->settings.global_settings.shape = SHAPE_CONE;
				this->settings.global_settings.shape_str = SHAPE_CONE_STR;
				this->settings.global_settings.index_of_spin = DRAW_ALL;
				this->settings.global_settings.background = vvis::visualization::VvisColor_3f(1, 1, 1);
				this->settings.global_settings.path_to_settings_file_folder = INTERPETATOR_PATH_PLUG_WSTR;
				std::wcout << "\n\tSuccessful!\n" << std::endl;
			} break;
			
			case COMMAND_SHOW_SETTINGS: {
				std::wcout << L"\n" << this->settings.global_settings << L"\n" << std::endl;
			} break;







			case COMMAND_HELP: {
				std::wcout
				 << "\n\t \'set\' : sets up the settings\n"
					<< "\t\t-- \'folderpath\'/\'folp\' <path-to-folder> : sets up the path to folder with sconfiguration or other files\n"
					<< "\t\t-- \'filenumber\'/\'fn\' <integer-number> : sets up the number of sconfiguration file or other\n"
					<< "\t\t\tNOTE: You can specify only one of the paths (to folder or to file)\n"
					<< "\t\t\tNOTE: Supports absolute or relative path \n"
					<< "\t\t\tEXAMPLE: set folp ../../temp/b\n"
					<< "\t\t-- \'filepath\'/\'fp\' <path-to-file> : sets up the path to sconfiguration file\n"
					<< "\t\t\tEXAMPLE: set fp ../../temp/b/sconfiguration-00000010.vvis\n"
					<< "\t\t-- \'coloring\'/\'cg\' <y/n> : shape coloring\n"
					<< "\t\t-- \'backgroundcolor\'/\'bgc\' <red> <green> <blue> : integers 0-255\n"
					<< "\t\t-- \'settingspath\'/\'sp\' <path-to-folder> : path to visualis-settings.json\n"
					<< "\t\t\tEXAMPLE: set sp ../b\n"
				 << "\n\t \'show\' : shows current settings\n"
				 << "\n\t \'unset\' <as in set> : sets up the base values\n"
				 << "\n\t \'convert\'/\'con\' : converts to .vvis format using global settings (folderpath, filenumber)\n"
					<< "\t\t-- \'v6\'/\'vampire6\'/\'v5\'/\'vampire5\' : looking for atoms-coords.data & spins-xxx.data\n"
				 << "\n\t \'visualize\'/\'vis\' : drawing a sample using global settings\n"
					<< "\t\t-- \'folder\' : ... using folderpath & filename\n"
					<< "\t\t-- \'file\' : ... using filepath\n"
				<< "\n\t \'settings\'\n"
					<< "\t\t-- \'save\' : save current variables to .json\n"
					<< "\t\t-- \'get\' : restore the variables from .json\n"
					<< "\t\t\tNOTE: looking for visualis-settings.json in current settings directory (settingspath)\n"
					<< "\t\t\tNOTE: this file used to save the drawer settings (f.e. sensivity) also by pop-menu\n"
				 //<< "\t \n"
				 << "\n\t \'restart\'/\'reset\' : reset the all current settings and restart the program\n"
				 << "\n\t \'exit\' : close the program\n"
				<< std::endl;
			} break;






			case UNKNOW_COMMAND: {
				std::wcout << L"\n\tERROR: Unknow command: " << get_command_for_error(line) << L"\n" << std::endl;
			} break;

			default: {} break;
		}

	}
}
