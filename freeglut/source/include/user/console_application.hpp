#pragma once


#ifndef CONSOLE_APPLICATION_HPP
#define CONSOLE_APPLICATION_HPP

	#include <ostream>
	#include "../sample/color_class.hpp"
	#include "../../libraries/json/single_include/nlohmann/json.hpp"

	namespace vvis {

		namespace console {

			struct Console_app_settings {
				public:

					std::wstring path_to_folder						= INTERPETATOR_PATH_PLUG_WSTR;
					std::wstring path_to_sconfiguration_file		= INTERPETATOR_PATH_PLUG_WSTR;
					std::wstring path_to_settings_file				= INTERPETATOR_PATH_PLUG_WSTR;
					bool using_color								= false;
					int number_of_file								= INTERPETATOR_NUMBER_PLUG_INT;
					wchar_t shape									= SHAPE_CONE;
					std::wstring shape_str							= SHAPE_CONE_STR;
					int index_of_spin								= DRAW_ALL;
					vvis::visualization::VvisColor_3f background	= {1, 1, 1};



					friend std::wostream& operator<<(std::wostream& _out, const Console_app_settings& _settings); /*{
						out << L"\t Path to folder with files\t\t (c): " << SET.path_to_folder << L"\n";
						out << L"\t Path to sconfiguration file\t\t (c): " << SET.path_to_sconfiguration_file << L"\n";
						out << L"\t Path settings file\t (c): " << SET.path_to_settings_file << L"\n";
						out << L"\t Using color?\t\t\t\t (c): " << std::boolalpha << SET.using_color << L"\n";
						out << L"\t Number of file\t\t\t\t (c): " << (SET.number_of_file == INTERPETATOR_NUMBER_PLUG_INT ? L"<nothing>" : std::to_wstring(SET.number_of_file)) << L"\n";
						out << L"\t Shape for drawing\t\t\t (u): " << SET.shape << L" - " << SET.shape_str << L"\n";
						out << L"\t Index of spin\t\t\t\t (u): " << (SET.index_of_spin == DRAW_ALL ? L"DRAW ALL" : std::to_wstring(SET.index_of_spin)) << L"\n";
						out << L"\t Background color (RGB)\t\t\t (c): " << SET.background.red * 255 << L"/255 " << SET.background.green * 255 << L"/255 " << SET.background.blue * 255 << L"/255 ";
						return out;
					};*/



					bool save_settings(const nlohmann::json& _json);
					bool get_settings(const nlohmann::json& _json);
				
			};
 
			bool get_settings_json(const std::wstring& _path_to_file);

		}


	}

#endif // !CONSOLE_APPLICATION_HPP
