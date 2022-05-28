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
	
	#define SUBCOMMAND_SET_FOLDERPATH 201
	#define SUBCOMMAND_SET_FILENUMBER 202
	#define SUBCOMMAND_SET_FILEPATH 203
	#define SUBCOMMAND_SET_COLORING 204

	#define SUBCOMMAND_CONVERT_VAMPIRE6 501 

	#define SUBCOMMAND_VISUALIZE_BY_FOLDER 701
	#define SUBCOMMAND_VISUALIZE_BY_FILE 702

	#include <iostream>
	#include <algorithm>
	#include <map>


	void print_visualis_logo();

	struct Settings {
		std::wstring path_to_folder					= INTERPETATOR_PATH_PLUG_WSTR;
		std::wstring path_to_sconfiguration_file	= INTERPETATOR_PATH_PLUG_WSTR;
		bool using_color							= false;
		int number_of_file							= INTERPETATOR_NUMBER_PLUG_INT;
		wchar_t shape								= SHAPE_CONE;
		std::wstring shape_str						= SHAPE_CONE_STR;
		int index_of_spin							= DRAW_ALL;
		// TODO: int spin_rate

		friend std::wostream& operator<<(std::wostream& out, const Settings& SET) {
			out << L"\t Path to folder with files\t\t (c): " << SET.path_to_folder << L"\n";
			out << L"\t Path to sconfiguration file\t\t (c): " << SET.path_to_sconfiguration_file << L"\n";
			out << L"\t Using color?\t\t\t\t (c): " << std::boolalpha << SET.using_color << L"\n";
			out << L"\t Number of file\t\t\t\t (c): " << SET.number_of_file << L"\n";
			out << L"\t Shape for drawing\t\t\t (u): " << SET.shape << L" " << SET.shape_str << L"\n";
			out << L"\t Index of spin\t\t\t\t (u): " << (SET.index_of_spin == DRAW_ALL ? L"DRAW ALL" : std::to_wstring(SET.index_of_spin));
			return out;
		};
	};
	
	std::wstring _prompt();

	std::wstring tolower_wstr(std::wstring& _value);

	bool is_number(const std::wstring& s);

	void remove_quotation(std::wstring& str);
	
	// yes no exit
	std::wstring by_synonyms(const std::wstring& _value);
	
	inline bool file_exist(const std::wstring& s);

	class Interpretator {
		private:
			Settings settings;
			std::wstring prompt;
			

			std::map<std::wstring, int> main_command = {
				{L"set", COMMAND_SET},
				{L"unset", COMMAND_UNSET},
				{L"show", COMMAND_SHOW_SETTINGS},
				{L"help", COMMAND_HELP},
				{L"convert", COMMAND_CONVERT}, {L"con", COMMAND_CONVERT},
				{L"restart", COMMAND_RESTART}, {L"reset", COMMAND_RESTART},
				{L"visualize", COMMAND_VISUALIZE}, {L"vis", COMMAND_VISUALIZE}
			};

			// set unset
			std::map<std::wstring, int> subSet_command = {
				{L"folderpath", SUBCOMMAND_SET_FOLDERPATH }, {L"folp", SUBCOMMAND_SET_FOLDERPATH },
				{L"filenumber", SUBCOMMAND_SET_FILENUMBER}, {L"fn", SUBCOMMAND_SET_FILENUMBER},
				{L"filepath", SUBCOMMAND_SET_FILEPATH}, {L"fp", SUBCOMMAND_SET_FILEPATH},
				{L"color", SUBCOMMAND_SET_COLORING}, {L"c", SUBCOMMAND_SET_COLORING}
				
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
			Interpretator(std::wstring _PROMPT, Settings settings);

			void loop(int argc, char** argv);
	};


#endif