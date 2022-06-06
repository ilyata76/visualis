#pragma once



#ifndef SETTINGS_HPP
#define SETTINGS_HPP


	#include "./console_application.hpp"
	#include "./freeglut_window.hpp"

	namespace vvis {

		class settings {

			private:
				console::console_app_settings	console_settings;
				visualization::window_settings	window_settings;
			public:
				settings();
				settings(console::console_app_settings console_settings);
				settings(visualization::window_settings window_settings);
				settings(console::console_app_settings console_settings, 
						visualization::window_settings window_settings);
				

				console::console_app_settings	get_console_settings();
				visualization::window_settings	get_window_settings();



		};

	}





#endif // !SETTINGS_HPP
