#pragma once



#ifndef SETTINGS_HPP
#define SETTINGS_HPP


	#include "./console_application.hpp"
	#include "./freeglut_window.hpp"

	namespace vvis {

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

				bool save_settings();
				bool get_settings(const nlohmann::json& _json);

		};

	}





#endif // !SETTINGS_HPP
