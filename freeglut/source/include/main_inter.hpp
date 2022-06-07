#pragma once


#ifndef MAIN_INTER_HPP
#define MAIN_INTER_HPP
	
	#include "./include/parser-converter/parser-v5.hpp"
	#include "./include/parser-converter/converter-v5.hpp"

	#include "./include/sample/creator_of_vertex_arr.hpp"
	#include "./include/sample/drawing_shape_opengl.hpp"

	#define ex_prompt _prompt()

	#define UNKNOW_COMMAND 100

	#define COMMAND_HELP 101
	#define COMMAND_SET 102
	#define COMMAND_UNSET 103
	#define COMMAND_SHOW_SETTINGS 104
	#define COMMAND_CONVERT 105
	#define COMMAND_RESTART 106
	#define COMMAND_VISUALIZE 107
	#define COMMAND_RESET 108
	#define COMMAND_SETTINGS 109
	
	#define SUBCOMMAND_SET_FOLDERPATH 201
	#define SUBCOMMAND_SET_FILENUMBER 202
	#define SUBCOMMAND_SET_FILEPATH 203
	#define SUBCOMMAND_SET_COLORING 204
	#define SUBCOMMAND_SET_BACKGROUNDCOLOR 205
	#define SUBCOMMAND_SET_SETTINGS_PATH 206

	#define SUBCOMMAND_CONVERT_VAMPIRE6 501 

	#define SUBCOMMAND_VISUALIZE_BY_FOLDER 701
	#define SUBCOMMAND_VISUALIZE_BY_FILE 702

	#define SUBCOMMAND_SAVE_SETTINGS 901
	#define SUBCOMMAND_GET_SETTINGS 902

	#include <iostream>
	#include <algorithm>
	#include <map>
	#include "./user/settings.hpp"

	using nlohmann::json;

	void print_visualis_logo();

	std::wstring _prompt();

	std::wstring tolower_wstr(std::wstring& _value);

	bool is_number(const std::wstring& s);

	void remove_quotation(std::wstring& str);

	// yes no exit
	std::wstring by_synonyms(const std::wstring& _value);

	class Interpretator {
		private:
			vvis::app::Settings settings;
			std::wstring prompt;
			

			std::map<std::wstring, int> main_command = {
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

			std::map<std::wstring, int> subSettings_command = {
				{L"save", SUBCOMMAND_SAVE_SETTINGS},
				{L"get", SUBCOMMAND_GET_SETTINGS}
			};

			// set unset
			std::map<std::wstring, int> subSet_command = {
				{L"folderpath", SUBCOMMAND_SET_FOLDERPATH }, {L"folp", SUBCOMMAND_SET_FOLDERPATH },
				{L"filenumber", SUBCOMMAND_SET_FILENUMBER}, {L"fn", SUBCOMMAND_SET_FILENUMBER},
				{L"filepath", SUBCOMMAND_SET_FILEPATH}, {L"fp", SUBCOMMAND_SET_FILEPATH},
				{L"coloring", SUBCOMMAND_SET_COLORING}, {L"cg", SUBCOMMAND_SET_COLORING},
				{L"backgroundcolor", SUBCOMMAND_SET_BACKGROUNDCOLOR}, {L"bgc", SUBCOMMAND_SET_BACKGROUNDCOLOR},
				{L"settingspath", SUBCOMMAND_SET_SETTINGS_PATH}, {L"sp", SUBCOMMAND_SET_SETTINGS_PATH}
			};
			
			// convert visualize
			std::map<std::wstring, int> subConvert_command = {
				{L"vampire5", SUBCOMMAND_CONVERT_VAMPIRE6}, {L"vampire6", SUBCOMMAND_CONVERT_VAMPIRE6}, {L"v5", SUBCOMMAND_CONVERT_VAMPIRE6}, {L"v6", SUBCOMMAND_CONVERT_VAMPIRE6},
				
			};
			
			std::map<std::wstring, int> subVisualize_command = {
				{L"folder", SUBCOMMAND_VISUALIZE_BY_FOLDER}, { L"file", SUBCOMMAND_VISUALIZE_BY_FILE }
			};

			std::wstring get_command_for_error(const std::wstring& _value);
			int switch_code_of_operation(std::map<std::wstring, int> _mapp, std::wstring& _value);

			void set_number_from_file_name(const std::wstring& _str);

			

		public:
			Interpretator();
			Interpretator(const std::wstring& _PROMPT, const vvis::app::Settings& settings);

			void loop(int argc, char** argv);
	};


#endif