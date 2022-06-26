#include "./global_settings.hpp"

Global_settings::Global_settings() {
	this->path_to_folder				= VVIS_PATH_PLUG_WSTR;
	this->path_to_sconfiguration_file	= VVIS_PATH_PLUG_WSTR;
	this->path_to_settings_file			= VVIS_PATH_PLUG_WSTR;
	this->path_to_settings_file_folder	= VVIS_PATH_PLUG_WSTR;
	this->number_of_file				= VVIS_INT_PLUG;
	this->index_of_spin					= VVIS_DRAW_ALL;
}

std::wostream& operator<<(std::wostream& _out, const Global_settings& _settings) {
	_out << L"\t Path to folder with files\t\t [C]: " << _settings.path_to_folder << L"\n";
	_out << L"\t Path to sconfiguration file\t\t [C]: " << _settings.path_to_sconfiguration_file << L"\n";
	_out << L"\t Path settings file\t\t\t [C]: " << _settings.path_to_settings_file << L"\n";
	_out << L"\t Path settings file folder\t\t [C]: " << _settings.path_to_settings_file_folder << L"\n";
	_out << L"\t Number of file\t\t\t\t [C]: " << (_settings.number_of_file == VVIS_INT_PLUG ? L"<nothing>" : std::to_wstring(_settings.number_of_file)) << L"\n";
	_out << L"\t Index of spin\t\t\t\t [C]: " << (_settings.index_of_spin == VVIS_DRAW_ALL ? L"DRAW ALL" : std::to_wstring(_settings.index_of_spin)) << L"\n";

	return _out;
}
