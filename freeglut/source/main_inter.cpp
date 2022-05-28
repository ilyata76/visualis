#include "./include/main_inter.hpp"

Interpretator::Interpretator() {
	this->prompt = ex_prompt;
}

Interpretator::Interpretator(std::wstring _PROMPT, Settings settings) {
	this->prompt = _PROMPT;
	this->settings = settings;
}


void print_visualis_logo() {
	std::wcout << L"____   ____.___  _____________ ___  _____  .____    .___  _________" << L"\n";
	std::wcout << L"\\   \\ /   /|   |/   _____/    |   \\/  _  \\ |    |   |   |/  _____/" << L"\n";
	std::wcout << L" \\   Y   / |   |\\_____  \\|    |   /  /_\\  \\|    |   |   |\\_____ \\" << L"\n";
	std::wcout << L"  \\     /  |   |/        \\    |  /    |    \\    |___|   |/       \\" << L"\n";
	std::wcout << L"   \\___/   |___/_______  /______/\\____|__  /_______ \\___/_______ /" << L"\n";
	std::wcout << L"                       \\/                \\/        \\/          \\/" << std::endl;
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
		s.end(), [](wchar_t c) { return !std::isdigit(c); }) == s.end();
}

std::wstring Interpretator::get_command_for_error(const std::wstring& _value) {
	return _value == L"" ? L"<nothing>" : L"\"" + _value + L"\"";
}

int Interpretator::switch_code_of_operation(std::map<std::wstring, int> mapp, std::wstring& _value) {
	std::map<std::wstring, int>::iterator it = mapp.find(tolower_wstr(_value));
	return it == mapp.end() ? UNKNOW_COMMAND : it->second;
}

std::wstring Interpretator::by_synonyms(const std::wstring& _value) {
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
	do {
		
		// приглашение ввода и ввод
		std::wcout << this->prompt; std::getline(std::wcin, line);

		// отсекаем выход
		if (this->by_synonyms(line) == L"exit") break;
		if (line == L"" | line == L"\n") continue;

		std::wstringstream ss; ss.str(line); line = L"";
		ss >> line;

		switch (switch_code_of_operation(this->main_command, line)) {




			case COMMAND_SET: {
				
				line = L""; if (ss.eof()) ss.str(L""); else ss >> line;

				switch (switch_code_of_operation(this->sub1_command, line)) {

					
					case SUBCOMMAND_FOLDERPATH : {
						line = L""; if (ss.eof()) ss.str(L""); else ss >> line;

						this->settings.path_to_folder = (line == L"")? INTERPETATOR_PATH_PLUG_WSTR : line;
						
						std::wcout << "\n\tPath to folder : " << this->settings.path_to_folder << " : has been set up\n";
						if (this->settings.path_to_folder == INTERPETATOR_PATH_PLUG_WSTR) std::wcout << "\tERROR: path was not entered\n";
						std::wcout<< std::endl;


					} break;

					case SUBCOMMAND_FILENUMBER: {
						line = L""; if (ss.eof()) ss.str(L""); else ss >> line;

						this->settings.number_of_file = (!is_number(line))? INTERPETATOR_NUMBER_PLUG_INT : std::stoi(line);

						std::wcout << "\n\tNumber of file : " << this->settings.number_of_file << " : has been set up\n";
						if (this->settings.number_of_file == INTERPETATOR_NUMBER_PLUG_INT) std::wcout << "\tERROR: not number\n";
						std::wcout<< std::endl;


					} break;

					case SUBCOMMAND_FILEPATH: {
						line = L""; if (ss.eof()) ss.str(L""); else ss >> line;

						this->settings.path_to_sconfiguration_file = (line == L"" || 
							(line.find(FORMAT_OF_OUR_FILE) == std::wstring::npos || line.find(START_OF_OUR_FILE) == std::wstring::npos)) ?
								 INTERPETATOR_PATH_PLUG_WSTR : line;
						
						std::wcout << "\n\tPath to sconfiguration file : " << this->settings.path_to_sconfiguration_file << " : has been set up\n";
						if (this->settings.path_to_sconfiguration_file == INTERPETATOR_PATH_PLUG_WSTR) std::wcout << "\tERROR: path was not entered or incorrectly\n";
						std::wcout << std::endl;


					} break;

					case SUBCOMMAND_COLORING: {
						line = L""; if (ss.eof()) ss.str(L""); else ss >> line;

						if (L"yes" == by_synonyms(line)) this->settings.using_color = true;
						else if (L"no" == by_synonyms(line)) this->settings.using_color = false;

						std::wcout << "\n\tColoring mode : " << std::boolalpha << this->settings.using_color << " : has been set up\n";
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

				switch (switch_code_of_operation(this->sub1_command, line)) {

					case SUBCOMMAND_FOLDERPATH: {
						this->settings.path_to_folder = INTERPETATOR_PATH_PLUG_WSTR;

						std::wcout << "\n\tPath to folder : " << this->settings.path_to_folder << " : has been set up\n";
						std::wcout << std::endl;
					} break;

					case SUBCOMMAND_FILEPATH: {
						this->settings.path_to_sconfiguration_file = INTERPETATOR_PATH_PLUG_WSTR;

						std::wcout << "\n\tPath to sconfiguration file : " << this->settings.path_to_sconfiguration_file << " : has been set up\n";
						std::wcout << std::endl;
					} break;

					case SUBCOMMAND_FILENUMBER: {
						this->settings.number_of_file = INTERPETATOR_NUMBER_PLUG_INT;

						std::wcout << "\n\tNumber of file : " << this->settings.number_of_file << " : has been set up\n";
						std::wcout << std::endl;
					} break;

					case SUBCOMMAND_COLORING: {
						this->settings.using_color = false;

						std::wcout << "\n\tColoring mode : " << std::boolalpha << this->settings.using_color << " : has been set up\n";
						std::wcout << std::endl;
					}

					case UNKNOW_COMMAND: {
						std::wcout << L"\n\tERROR: Unknow subcommand for \"unset\": " << this->get_command_for_error(line) << L"\n" << std::endl;
					} break;

					default: {} break;
				}
			} break;









			
			case COMMAND_SHOW_SETTINGS: {
				std::wcout << L"\n" << this->settings << L"\n" << std::endl;
			} break;


			case COMMAND_HELP: {
				std::wcout
				 << "\n\t \'set\' : sets up the settings\n"
					<< "\t\t-- \'fp\'/\'folderpath\' <path-to-folder> : sets up the path to folder with sconfiguration or other files\n"
					<< "\t\t-- \'fn\'/\'filenumber\' <integer-number> : sets up the number of sconfiguration file or other\n"
					<< "\t\t\tNOTE: You can specify only one of the paths (to folder or to file)\n"
					<< "\t\t-- \'filepath\' <path-to-file> : sets up the path to sconfiguration file\n"
					<< "\t\t-- \'color\' <y/n> : shape coloring\n"
				 << "\n\t \'show\' : shows current settings\n"
				 << "\n\t \'unset\' <as in set> : sets up the base values\n"
				 //<< "\t \n"
				 //<< "\t \n"
				 //<< "\t \n"
				<< std::endl;
			} break;

			case UNKNOW_COMMAND: {
				std::wcout << L"\n\tERROR: Unknow command: " << get_command_for_error(line) << L"\n" << std::endl;
			} break;

			default: {} break;
		}

	} while (true);
}
