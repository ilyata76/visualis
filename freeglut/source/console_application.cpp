#include "include\user\console_application.hpp"

bool vvis::console::file_exist(const std::wstring& s) {
	struct _stat buf;
	return (_wstat(s.c_str(), &buf) != -1);
}

std::wostream& vvis::console::operator<<(std::wostream& _out, const Console_app_settings& _settings) {
	_out << L"\t Path to folder with files\t\t (c): " << _settings.path_to_folder << L"\n";
	_out << L"\t Path to sconfiguration file\t\t (c): " << _settings.path_to_sconfiguration_file << L"\n";
	_out << L"\t Path settings file\t (c): " << _settings.path_to_settings_file << L"\n";
	_out << L"\t Path settings file folder\t (c): " << _settings.path_to_settings_file_folder << L"\n";
	_out << L"\t Using color?\t\t\t\t (c): " << std::boolalpha << _settings.using_color << L"\n";
	_out << L"\t Number of file\t\t\t\t (c): " << (_settings.number_of_file == INTERPETATOR_NUMBER_PLUG_INT ? L"<nothing>" : std::to_wstring(_settings.number_of_file)) << L"\n";
	_out << L"\t Shape for drawing\t\t\t (u): " << _settings.shape << L" - " << _settings.shape_str << L"\n";
	_out << L"\t Index of spin\t\t\t\t (u): " << (_settings.index_of_spin == DRAW_ALL ? L"DRAW ALL" : std::to_wstring(_settings.index_of_spin)) << L"\n";
	_out << L"\t Background color (RGB)\t\t\t (c): " << _settings.background.red * 255 << L"/255 " << _settings.background.green * 255 << L"/255 " << _settings.background.blue * 255 << L"/255 ";
	return _out;
}

bool vvis::console::Console_app_settings::save_settings() {
	std::fstream file; nlohmann::json _json;
	
	if (this->path_to_settings_file == INTERPETATOR_PATH_PLUG_WSTR) {
		if (this->path_to_settings_file_folder == INTERPETATOR_PATH_PLUG_WSTR) {
			if (this->path_to_folder == INTERPETATOR_PATH_PLUG_WSTR) {
				return false;
			}
			this->path_to_settings_file_folder = this->path_to_folder;
		}
		this->path_to_settings_file = this->path_to_settings_file_folder + L"/" + VISUALIS_SETTINGS_JSON;
	}
	
	if (file_exist(this->path_to_settings_file)) {
		file.open(this->path_to_settings_file, std::ios_base::in);
		_json << file;
		file.close();
	}

	file.open(this->path_to_settings_file, std::ios_base::out | std::ios_base::trunc);
	
	_json["global"]["path_to_folder"] = this->path_to_folder;
	_json["global"]["path_to_sconfiguration_file"] = this->path_to_sconfiguration_file;

	_json["global"]["using_color"] = this->using_color;
	_json["global"]["number_of_file"] = this->number_of_file;

	_json["global"]["shape"] = this->shape;
	_json["global"]["shape_str"] = this->shape_str;

	_json["global"]["index_of_spin"] = this->index_of_spin;

	_json["global"]["background"]["red"] = this->background.red;
	_json["global"]["background"]["green"] = this->background.green;
	_json["global"]["background"]["blue"] = this->background.blue;

	file << _json.dump(4);
	file.close();
	
	return true;
}

bool vvis::console::Console_app_settings::get_settings_by_json(const nlohmann::json& _json){
	if (_json["global"] == nullptr) return false;

	if (_json["global"]["path_to_folder"] == nullptr); else this->path_to_folder = _json["global"]["path_to_folder"].get<std::wstring>();
	if (_json["global"]["path_to_sconfiguration_file"] == nullptr); else this->path_to_sconfiguration_file = _json["global"]["path_to_sconfiguration_file"].get<std::wstring>();

	if (_json["global"]["using_color"] == nullptr); else this->using_color = _json["global"]["using_color"].get<bool>();
	if (_json["global"]["number_of_file"] == nullptr); else this->number_of_file = _json["global"]["number_of_file"].get<int>();

	if (_json["global"]["shape"] == nullptr); else this->shape = _json["global"]["shape"].get<wchar_t>();
	if (_json["global"]["shape_str"] == nullptr); else this->shape_str = _json["global"]["shape_str"].get<std::wstring>();

	if (_json["global"]["index_of_spin"] == nullptr); else this->index_of_spin = _json["global"]["index_of_spin"].get<int>();

	if (_json["global"]["background"]["red"] == nullptr); else this->background.red = _json["global"]["background"]["red"].get<double>();
	if (_json["global"]["background"]["green"] == nullptr); else this->background.green = _json["global"]["background"]["green"].get<double>();
	if (_json["global"]["background"]["blue"] == nullptr); else this->background.blue = _json["global"]["background"]["blue"].get<double>();

	return true;
}

bool vvis::console::Console_app_settings::get_settings() {
	std::fstream file; nlohmann::json _json;

	if (this->path_to_settings_file == INTERPETATOR_PATH_PLUG_WSTR) {
		if (this->path_to_settings_file_folder == INTERPETATOR_PATH_PLUG_WSTR) {
			if (this->path_to_folder == INTERPETATOR_PATH_PLUG_WSTR) {
				return false;
			}
			this->path_to_settings_file_folder = this->path_to_folder;
		}
		this->path_to_settings_file = this->path_to_settings_file_folder + L"/" + VISUALIS_SETTINGS_JSON;
	}
	
	if (file_exist(this->path_to_settings_file)) {
		file.open(this->path_to_settings_file, std::ios_base::in);
		_json << file;
		file.close();
	}

	return this->get_settings_by_json(_json);

}
