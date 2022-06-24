#pragma once


#ifndef CONSOLE_INTERPRETATOR_HPP
#define CONSOLE_INTERPRETATOR_HPP

	#include "../settings/settings.hpp"
	#include "./defines_commands_codes.hpp"
	#include <map>
	#include <iostream>

	

	class Interpretator {
		private:
			Settings app_settings;
			std::wstring prompt;

			std::map<std::wstring, int> main_command;
				std::map<std::wstring, int> settings_sub_command;
					std::map<std::wstring, int> settings_show_sub_command;
				// help_sub_command
				std::map<std::wstring, int> set_sub_command;


		public:
			Interpretator();
			Interpretator(std::wstring& _prompt) : prompt(_prompt) { set_command_maps(*this); };
			Interpretator(Settings& _app_settings) : app_settings(_app_settings) { this->prompt = L"vvis > "; set_command_maps(*this); };
			Interpretator(std::wstring& _prompt, Settings& _app_settings) : prompt(_prompt), app_settings(_app_settings) { set_command_maps(*this); };

			// 0 - okay; 1 - error; 2 - restart
			unsigned char loop(int argc, char** argv, std::vector<std::wstring> _commands = {});

		protected:

			friend bool set_command_maps(Interpretator& _inter);

			bool settings_handler(std::vector<std::wstring> _commands);
			bool help_handler(std::vector<std::wstring> _commands);
			bool reset_handler(std::vector<std::wstring> _commands);
			bool restart_handler(std::vector<std::wstring> _commands);
			bool set_handler(std::vector<std::wstring> _commands);
			bool unset_handler(std::vector<std::wstring> _commands);

			

	};








#endif // !CONSOLE_INTERPRETATOR_HPP
