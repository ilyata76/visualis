#pragma once


#ifndef CONSOLE_INTERPRETATOR_HPP
#define CONSOLE_INTERPRETATOR_HPP

	#include "../settings/settings.hpp"
	#include "./defines_commands_codes.hpp"
	#include <map>

	class Interpretator {
		private:
			Settings app_settings;
			std::wstring prompt;

			std::map<std::wstring, int> main_command;

		public:
			Interpretator();
			Interpretator(std::wstring& _prompt) : prompt(_prompt) {};
			Interpretator(std::wstring& _prompt, Settings& _app_settings) : prompt(_prompt), app_settings(_app_settings) {};

			// 0 - error; 1 - okay; 2 - restart
			unsigned char loop(int argc, char** argv);

		protected:

			bool settings_handler();
			bool help_handler();

	};








#endif // !CONSOLE_INTERPRETATOR_HPP
