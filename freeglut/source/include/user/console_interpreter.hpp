#pragma once

#ifndef CONSOLE_INTERPRETER
#define CONSOLE_INTERPRETER

	#include <iostream>

	#include "./settings.hpp"

	#include "../parser-converter/parser-v5.hpp"
	#include "../parser-converter/converter-v5.hpp"

	#include "../sample/creator_of_vertex_arr.hpp"
	#include "../sample/drawing_shape_opengl.hpp"


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

	namespace vvis {

		class Console_Interpretator {

		private:

			vvis::app::Settings settings;
			std::wstring prompt;

			std::map<std::wstring, int> main_command;
			std::map<std::wstring, int> subSettings_command;
			std::map<std::wstring, int> subSet_command;
			std::map<std::wstring, int> subConvert_command;
			std::map<std::wstring, int> subVisualize_command;

		public: 
			Console_Interpretator();
			Console_Interpretator(const std::wstring& _prompt);
			Console_Interpretator(const std::wstring& _prompt, const vvis::app::Settings& _settings);

			void loop(int argc, char** argv);

		};




	}

#endif // !CONSOLE_INTERPRETER
