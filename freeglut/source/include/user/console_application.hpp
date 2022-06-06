#pragma once


#ifndef CONSOLE_APPLICATION_HPP
#define CONSOLE_APPLICATION_HPP

	#include <ostream>
	#include <fstream>
	#include "../sample/color_class.hpp"
	#include "../../libraries/json/single_include/nlohmann/json.hpp"

	namespace vvis {

		namespace console {

			inline bool file_exist(const std::wstring& s);

			nlohmann::json get_settings_json(const std::wstring& _path_to_file);

			struct Console_app_settings {
				public:

					std::wstring path_to_folder						= INTERPETATOR_PATH_PLUG_WSTR;
					std::wstring path_to_sconfiguration_file		= INTERPETATOR_PATH_PLUG_WSTR;
					std::wstring path_to_settings_file				= INTERPETATOR_PATH_PLUG_WSTR;
					std::wstring path_to_settings_file_folder		= INTERPETATOR_PATH_PLUG_WSTR;
					bool using_color								= false;
					int number_of_file								= INTERPETATOR_NUMBER_PLUG_INT;
					wchar_t shape									= SHAPE_CONE;
					std::wstring shape_str							= SHAPE_CONE_STR;
					int index_of_spin								= DRAW_ALL;
					vvis::visualization::VvisColor_3f background	= {1, 1, 1};

					
					friend std::wostream& operator<<(std::wostream& _out, const Console_app_settings& _settings); 

					// должен существовать путь path_to_settings_file или path_to_folder, или path_to_settings_file_folder
					bool save_settings();

					// должен существовать json файл
					bool get_settings_by_json(const nlohmann::json& _json);
				
					// должен существовать путь path_to_settings_file или path_to_folder, или path_to_settings_file_folder
					bool get_settings();

			};

		}


	}

#endif // !CONSOLE_APPLICATION_HPP
