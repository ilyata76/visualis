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

			Global_settings() {
				this->path_to_folder				= VVIS_PATH_PLUG_WSTR;
				this->path_to_sconfiguration_file	= VVIS_PATH_PLUG_WSTR;
				this->path_to_settings_file			= VVIS_PATH_PLUG_WSTR;
				this->path_to_settings_file_folder	= VVIS_PATH_PLUG_WSTR;
				this->number_of_file				= VVIS_INT_PLUG_WSTR;
				this->index_of_spin					= VVIS_DRAW_ALL;
			}

			friend std::wostream& operator<<(std::wostream& _out, const Global_settings& _settings) {
				_out << L"\t Path to folder with files\t\t (X): " << _settings.path_to_folder << L"\n";
				_out << L"\t Path to sconfiguration file\t\t (X): " << _settings.path_to_sconfiguration_file << L"\n";
				_out << L"\t Path settings file\t\t\t (X): " << _settings.path_to_settings_file << L"\n";
				_out << L"\t Path settings file folder\t\t (X): " << _settings.path_to_settings_file_folder << L"\n";
				_out << L"\t Number of file\t\t\t\t (X): " << (_settings.number_of_file == VVIS_INT_PLUG_WSTR ? L"<nothing>" : std::to_wstring(_settings.number_of_file)) << L"\n";
				_out << L"\t Index of spin\t\t\t\t (X): " << (_settings.index_of_spin == VVIS_DRAW_ALL ? L"DRAW ALL" : std::to_wstring(_settings.index_of_spin)) << L"\n";
				
				return _out;
			}


	};



#endif // !GLOBAL_SETTINGS_HPP
