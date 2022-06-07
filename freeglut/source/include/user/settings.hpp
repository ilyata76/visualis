#pragma once



#ifndef SETTINGS_HPP
#define SETTINGS_HPP


	#include "./console_application_settings.hpp"
	#include "./freeglut_window_settings.hpp"

	namespace vvis {

		namespace app {

			struct Settings {
				public:
				
					console::Console_app_settings		global_settings;
					visualization::Freeglut_settings	freeglut_settings;

					Settings();
					Settings(const console::Console_app_settings& _console_settings);
					Settings(const visualization::Freeglut_settings& _window_settings);
					Settings(const console::Console_app_settings& _console_settings, 
							const visualization::Freeglut_settings& _window_settings);
				

					console::Console_app_settings		get_console_settings();
					visualization::Freeglut_settings	get_window_settings();

					friend std::wostream& operator<<(std::wostream& _out, const Settings& _settings);

					// ПЕРЕТАЩИТЬ СЮДА ИЗ CONSOLE_APPL

					// должен существовать путь path_to_settings_file или path_to_folder, или path_to_settings_file_folder
					bool save_settings();

					// должен существовать json файл
					bool get_settings_by_json(const nlohmann::json& _json);

					// должен существовать путь path_to_settings_file или path_to_folder, или path_to_settings_file_folder
					bool get_settings();

			};

		}

	}





#endif // !SETTINGS_HPP
