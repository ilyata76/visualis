#include "./console_interpretator.hpp"

Interpretator::Interpretator() {
	this->prompt = L"vvis > ";
	set_command_maps(*this);
}

unsigned char Interpretator::loop(int argc, char** argv) {
	print_logo(std::wcout);
	std::wstring str;

	do {
		std::wcout << this->prompt; std::getline(std::wcin, str);
		std::vector<std::wstring> command_vector = line_to_vector(str);

		switch (get_second_from_map(this->main_command, to_lower_wstr(command_vector[0]))) {
			
			case INTER_COMMAND_HELP:		this->help_handler();		break;
			case INTER_COMMAND_SETTINGS:	this->settings_handler();	break;

		};


	} while (str != L"exit");
	
	return 0;
}

bool Interpretator::settings_handler() {
	return false;
}

bool Interpretator::help_handler() {
	return false;
}

bool set_command_maps(Interpretator& _inter) {
	
	_inter.main_command = {
		{L"help", INTER_COMMAND_HELP},
		{L"settings", INTER_COMMAND_SETTINGS},
		{L"set", INTER_COMMAND_SET},
		{L"convert", INTER_COMMAND_CONVERT},
		{L"visualize", INTER_COMMAND_VISUALIZE},
		{L"reset", INTER_COMMAND_RESET},
		{L"restart", INTER_COMMAND_RESTART}
	};

	return true;
}
