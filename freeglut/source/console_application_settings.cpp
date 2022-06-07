#include "include\user\console_application_settings.hpp"

bool vvis::file_exist(const std::wstring& s) {
	struct _stat buf;
	return (_wstat(s.c_str(), &buf) != -1);
}

std::wostream& vvis::console::operator<<(std::wostream& _out, const Console_app_settings& _settings) {
	_out << L"\t Path to folder with files\t\t (c): " << _settings.path_to_folder << L"\n";
	_out << L"\t Path to sconfiguration file\t\t (c): " << _settings.path_to_sconfiguration_file << L"\n";
	_out << L"\t Path settings file\t\t\t (u): " << _settings.path_to_settings_file << L"\n";
	_out << L"\t Path settings file folder\t\t (c): " << _settings.path_to_settings_file_folder << L"\n";
	_out << L"\t Using color?\t\t\t\t (c): " << std::boolalpha << _settings.using_color << L"\n";
	_out << L"\t Number of file\t\t\t\t (c): " << (_settings.number_of_file == INTERPETATOR_NUMBER_PLUG_INT ? L"<nothing>" : std::to_wstring(_settings.number_of_file)) << L"\n";
	_out << L"\t Shape for drawing\t\t\t (u): " << _settings.shape << L" - " << _settings.shape_str << L"\n";
	_out << L"\t Index of spin\t\t\t\t (u): " << (_settings.index_of_spin == DRAW_ALL ? L"DRAW ALL" : std::to_wstring(_settings.index_of_spin)) << L"\n";
	_out << L"\t Background color (RGB)\t\t\t (c): " << _settings.background.red * 255 << L"/255 " << _settings.background.green * 255 << L"/255 " << _settings.background.blue * 255 << L"/255 ";
	return _out;
}