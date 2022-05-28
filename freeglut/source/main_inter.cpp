#include "./include/main_inter.hpp"

struct settings {
	std::wstring path_to_folder				= L"";
	std::wstring path_to_atoms_file			= L"";
	std::wstring path_to_spins_file			= L"";
	bool using_color						= false;
	int number_of_spins_file				= 0;
} global_interpet;

std::map<std::wstring, int> main_command = { {L"set", COMMAND_SET } };

void print_visualis_logo() {
	std::wcout << L"____   ____.___  _____________ ___  _____  .____    .___  _________" << L"\n";
	std::wcout << L"\\   \\ /   /|   |/   _____/    |   \\/  _  \\ |    |   |   |/  _____/" << L"\n";
	std::wcout << L" \\   Y   / |   |\\_____  \\|    |   /  /_\\  \\|    |   |   |\\_____ \\" << L"\n";
	std::wcout << L"  \\     /  |   |/        \\    |  /    |    \\    |___|   |/       \\" << L"\n";
	std::wcout << L"   \\___/   |___/_______  /______/\\____|__  /_______ \\___/_______ /" << L"\n";
	std::wcout << L"                       \\/                \\/        \\/          \\/" << std::endl;
}

std::wstring _prompt() {
	return std::wstring(L"vis>");
}

std::wstring tolower_wstr(std::wstring& _value) {
	std::transform(_value.begin(), _value.end(), _value.begin(), std::tolower);
	return std::wstring(_value);
}

int switch_code_of_operation(std::map<std::wstring, int> mapp, std::wstring& _value) {
	std::map<std::wstring, int>::iterator it = mapp.find(tolower_wstr(_value));
	return it == mapp.end() ? COMMAND_UNKNOW_COMMAND : it->second;
}

std::wstring by_synonyms(const std::wstring& _value) {
	std::wstring copy_value = _value; tolower_wstr(copy_value);

	std::vector<std::wstring> exit = {L"exit", L"(exit)", L"exit.", L"end"};
	
	
	std::vector<std::wstring>::iterator it = std::find(exit.begin(), exit.end(), copy_value);
	if (it != exit.end()) return L"exit"; else return _value;

}

void interpertator_loop(int argc, char** argv) {
	std::wstring line;
	do {
		
		// приглашение ввода и ввод
		std::wcout << prompt; std::getline(std::wcin, line);

		// отсекаем выход
		if (by_synonyms(line) == L"exit") break;
		if (line == L"" | line == L"\n") continue;

		std::wstringstream ss; ss.str(line);
		ss >> line;



		switch (switch_code_of_operation(main_command, line)) {

			case COMMAND_SET: {
				std::wcout << "set!";
			} break;
		
		
			case COMMAND_UNKNOW_COMMAND: {
				std::wcout << L"\n\tERROR: Unknow command: \"" << line << L"\"\n" << std::endl;
			} break;

			default: {} break;
		}

	} while (true);
}
