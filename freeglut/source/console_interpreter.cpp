#include "include\user\console_interpreter.hpp"

vvis::Console_Interpretator::Console_Interpretator() {

	this->main_command = {
		{L"set", COMMAND_SET},
		{L"unset", COMMAND_UNSET},
		{L"show", COMMAND_SHOW_SETTINGS},
		{L"help", COMMAND_HELP},
		{L"convert", COMMAND_CONVERT}, {L"con", COMMAND_CONVERT},
		{L"restart", COMMAND_RESTART},
		{L"reset", COMMAND_RESET},
		{L"visualize", COMMAND_VISUALIZE}, {L"vis", COMMAND_VISUALIZE},
		{L"settings", COMMAND_SETTINGS}
	};

	this->subSettings_command = {
		{L"save", SUBCOMMAND_SAVE_SETTINGS},
		{L"get", SUBCOMMAND_GET_SETTINGS}
	};

	this->subSet_command = {
		{L"folderpath", SUBCOMMAND_SET_FOLDERPATH }, {L"folp", SUBCOMMAND_SET_FOLDERPATH },
		{L"filenumber", SUBCOMMAND_SET_FILENUMBER}, {L"fn", SUBCOMMAND_SET_FILENUMBER},
		{L"filepath", SUBCOMMAND_SET_FILEPATH}, {L"fp", SUBCOMMAND_SET_FILEPATH},
		{L"coloring", SUBCOMMAND_SET_COLORING}, {L"cg", SUBCOMMAND_SET_COLORING},
		{L"backgroundcolor", SUBCOMMAND_SET_BACKGROUNDCOLOR}, {L"bgc", SUBCOMMAND_SET_BACKGROUNDCOLOR},
		{L"settingspath", SUBCOMMAND_SET_SETTINGS_PATH}, {L"sp", SUBCOMMAND_SET_SETTINGS_PATH}
	};

	this->subConvert_command = {
		{L"vampire5", SUBCOMMAND_CONVERT_VAMPIRE6}, {L"vampire6", SUBCOMMAND_CONVERT_VAMPIRE6}, {L"v5", SUBCOMMAND_CONVERT_VAMPIRE6}, {L"v6", SUBCOMMAND_CONVERT_VAMPIRE6},

	};

	this->subVisualize_command = {
		{L"folder", SUBCOMMAND_VISUALIZE_BY_FOLDER}, 
		{ L"file", SUBCOMMAND_VISUALIZE_BY_FILE }
	};

}

void vvis::Console_Interpretator::loop(int argc, char** argv) {
	std::wstring line;
	std::wcout << this->prompt; std::getline(std::wcin, line);
	


	return loop(argc, argv);
}
