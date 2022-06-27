#pragma once


#ifndef GLOBAL_SETTINGS_HPP
#define GLOBAL_SETTINGS_HPP

	#include <string>
	#include <ostream>
	
	#include "../helpful/global_defines.hpp"

	class Global_settings {
		
		public:
			
			std::wstring path_to_folder;
			std::wstring path_to_sconfiguration_file;
			std::wstring path_to_settings_file;
			std::wstring path_to_settings_file_folder;
			int number_of_file;
			int index_of_spin;

			Global_settings();

			friend std::wostream& operator<<(std::wostream& _out, const Global_settings& _settings);

			~Global_settings() {};
	};



#endif // !GLOBAL_SETTINGS_HPP
