#pragma once


#ifndef CONSOLE_APPLICATION_HPP
#define CONSOLE_APPLICATION_HPP

	#include <ostream>
	#include "../sample/color_class.hpp"

	namespace vvis {

		namespace console {

			struct console_app_settings {

				std::wstring path_to_folder						= INTERPETATOR_PATH_PLUG_WSTR;
				std::wstring path_to_sconfiguration_file		= INTERPETATOR_PATH_PLUG_WSTR;
				std::wstring path_to_settings_file_folder		= INTERPETATOR_PATH_PLUG_WSTR;
				bool using_color								= false;
				int number_of_file								= INTERPETATOR_NUMBER_PLUG_INT;
				wchar_t shape									= SHAPE_CONE;
				std::wstring shape_str							= SHAPE_CONE_STR;
				int index_of_spin								= DRAW_ALL;
				vvis::visualization::VvisColor_3f background	= {1, 1, 1};

			};

		}


	}

#endif // !CONSOLE_APPLICATION_HPP
