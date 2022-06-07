#include "./include/user/settings.hpp"

vvis::app::Settings::Settings() {
}

bool vvis::app::Settings::save_settings() {
    	std::fstream file; nlohmann::json _json;
	
	if (this->global_settings.path_to_settings_file == INTERPETATOR_PATH_PLUG_WSTR) {
		if (this->global_settings.path_to_settings_file_folder == INTERPETATOR_PATH_PLUG_WSTR) {
			if (this->global_settings.path_to_folder == INTERPETATOR_PATH_PLUG_WSTR) {
				return false;
			}
			this->global_settings.path_to_settings_file_folder = this->global_settings.path_to_folder;
		}
		this->global_settings.path_to_settings_file = this->global_settings.path_to_settings_file_folder + L"/" + VISUALIS_SETTINGS_JSON;
	}
	
	if (file_exist(this->global_settings.path_to_settings_file)) {
		file.open(this->global_settings.path_to_settings_file, std::ios_base::in);
		_json << file;
		file.close();
	}

	file.open(this->global_settings.path_to_settings_file, std::ios_base::out | std::ios_base::trunc);
	
	_json["global"]["path_to_folder"] = this->global_settings.path_to_folder;
	_json["global"]["path_to_sconfiguration_file"] = this->global_settings.path_to_sconfiguration_file;

	_json["global"]["using_color"] = this->global_settings.using_color;
	_json["global"]["number_of_file"] = this->global_settings.number_of_file;

	_json["global"]["shape"] = this->global_settings.shape;
	_json["global"]["shape_str"] = this->global_settings.shape_str;

	_json["global"]["index_of_spin"] = this->global_settings.index_of_spin;

	_json["global"]["background"]["red"] = this->global_settings.background.red;
	_json["global"]["background"]["green"] = this->global_settings.background.green;
	_json["global"]["background"]["blue"] = this->global_settings.background.blue;

	file << _json.dump(4);
	file.close();
	
	return true;
}

bool vvis::app::Settings::get_settings_by_json(const nlohmann::json& _json) {
	if (_json["global"] == nullptr) return false;

	if (_json["global"]["path_to_folder"] == nullptr); else this->global_settings.path_to_folder = _json["global"]["path_to_folder"].get<std::wstring>();
	if (_json["global"]["path_to_sconfiguration_file"] == nullptr); else this->global_settings.path_to_sconfiguration_file = _json["global"]["path_to_sconfiguration_file"].get<std::wstring>();

	if (_json["global"]["using_color"] == nullptr); else this->global_settings.using_color = _json["global"]["using_color"].get<bool>();
	if (_json["global"]["number_of_file"] == nullptr); else this->global_settings.number_of_file = _json["global"]["number_of_file"].get<int>();

	if (_json["global"]["shape"] == nullptr); else this->global_settings.shape = _json["global"]["shape"].get<wchar_t>();
	if (_json["global"]["shape_str"] == nullptr); else this->global_settings.shape_str = _json["global"]["shape_str"].get<std::wstring>();

	if (_json["global"]["index_of_spin"] == nullptr); else this->global_settings.index_of_spin = _json["global"]["index_of_spin"].get<int>();

	if (_json["global"]["background"]["red"] == nullptr); else this->global_settings.background.red = _json["global"]["background"]["red"].get<double>();
	if (_json["global"]["background"]["green"] == nullptr); else this->global_settings.background.green = _json["global"]["background"]["green"].get<double>();
	if (_json["global"]["background"]["blue"] == nullptr); else this->global_settings.background.blue = _json["global"]["background"]["blue"].get<double>();

	return true;
}

bool vvis::app::Settings::get_settings() {
	std::fstream file; nlohmann::json _json;

	if (this->global_settings.path_to_settings_file == INTERPETATOR_PATH_PLUG_WSTR) {
		if (this->global_settings.path_to_settings_file_folder == INTERPETATOR_PATH_PLUG_WSTR) {
			if (this->global_settings.path_to_folder == INTERPETATOR_PATH_PLUG_WSTR) {
				return false;
			}
			this->global_settings.path_to_settings_file_folder = this->global_settings.path_to_folder;
		}
		this->global_settings.path_to_settings_file = this->global_settings.path_to_settings_file_folder + L"/" + VISUALIS_SETTINGS_JSON;
	}

	if (file_exist(this->global_settings.path_to_settings_file)) {
		file.open(this->global_settings.path_to_settings_file, std::ios_base::in);
		_json << file;
		file.close();
	}

	return this->get_settings_by_json(_json);

}

std::wostream& vvis::app::operator<<(std::wostream& _out, const Settings& _settings) {
	_out << _settings.global_settings; return _out;
}
