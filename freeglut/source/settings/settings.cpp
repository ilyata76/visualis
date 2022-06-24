#include "./settings.hpp"

std::wostream& operator<<(std::wostream& _out, const Settings& _settings) {
	_out << _settings.global_settings << _settings.freeglut_settings;
	return _out;
};

std::wostream& Settings::print_only_global(std::wostream& _out) {
	return operator<<(_out, this->global_settings);
}

std::wostream& Settings::print_only_freeglut(std::wostream& _out) {
	return operator<<(_out, this->freeglut_settings);
}

bool Settings::save(wchar_t _flag) {
	std::fstream file; nlohmann::json _json;

	if (this->global_settings.path_to_settings_file == VVIS_PATH_PLUG_WSTR) {
		if (this->global_settings.path_to_settings_file_folder == VVIS_PATH_PLUG_WSTR) {
			if (this->global_settings.path_to_folder == VVIS_PATH_PLUG_WSTR) {
				return false;
			}
			this->global_settings.path_to_settings_file_folder = this->global_settings.path_to_folder;
		}
		this->global_settings.path_to_settings_file = this->global_settings.path_to_settings_file_folder + L"/" + VVIS_SETTINGS_FILE_NAME_WSTR;
	}

	if (file_exist(this->global_settings.path_to_settings_file)) {
		file.open(this->global_settings.path_to_settings_file, std::ios_base::in);
		_json << file;
		file.close();
	}

	file.open(this->global_settings.path_to_settings_file, std::ios_base::out | std::ios_base::trunc);

	if (_flag == L'g' || _flag == L'a') {
		_json[VVIS_GLOBAL_SETTINGS]["path_to_folder"] = this->global_settings.path_to_folder;
		_json[VVIS_GLOBAL_SETTINGS]["path_to_sconfiguration_file"] = this->global_settings.path_to_sconfiguration_file;
		_json[VVIS_GLOBAL_SETTINGS]["number_of_file"] = this->global_settings.number_of_file;
		_json[VVIS_GLOBAL_SETTINGS]["index_of_spin"] = this->global_settings.index_of_spin;
	}
	///

	if (_flag == L'f' || _flag == L'a') {
		_json[VVIS_FREEGLUT_SETTINGS]["background"]["red"] = this->freeglut_settings.backgroundcolor.red;
		_json[VVIS_FREEGLUT_SETTINGS]["background"]["green"] = this->freeglut_settings.backgroundcolor.green;
		_json[VVIS_FREEGLUT_SETTINGS]["background"]["blue"] = this->freeglut_settings.backgroundcolor.blue;
		_json[VVIS_FREEGLUT_SETTINGS]["coloring_sample"] = this->freeglut_settings.coloring_sample;
		_json[VVIS_FREEGLUT_SETTINGS]["shape"] = this->freeglut_settings.shape;
		_json[VVIS_FREEGLUT_SETTINGS]["shape_str"] = this->freeglut_settings.shape_wstr;
		_json[VVIS_FREEGLUT_SETTINGS]["additional_rotation"]["phi"] = this->freeglut_settings.additional_rotation.phi;
		_json[VVIS_FREEGLUT_SETTINGS]["additional_rotation"]["theta"] = this->freeglut_settings.additional_rotation.theta;
		_json[VVIS_FREEGLUT_SETTINGS]["estrangement"] = this->freeglut_settings.estrangement;
		_json[VVIS_FREEGLUT_SETTINGS]["global_translation"]["x"] = this->freeglut_settings.global_translation.x;
		_json[VVIS_FREEGLUT_SETTINGS]["global_translation"]["y"] = this->freeglut_settings.global_translation.y;
		_json[VVIS_FREEGLUT_SETTINGS]["global_translation"]["z"] = this->freeglut_settings.global_translation.z;
		_json[VVIS_FREEGLUT_SETTINGS]["scaling_parameters"]["x"] = this->freeglut_settings.scaling_parameters.x;
		_json[VVIS_FREEGLUT_SETTINGS]["scaling_parameters"]["y"] = this->freeglut_settings.scaling_parameters.y;
		_json[VVIS_FREEGLUT_SETTINGS]["scaling_parameters"]["z"] = this->freeglut_settings.scaling_parameters.z;
		_json[VVIS_FREEGLUT_SETTINGS]["scaling_translation"]["x"] = this->freeglut_settings.scaling_translation.x;
		_json[VVIS_FREEGLUT_SETTINGS]["scaling_translation"]["y"] = this->freeglut_settings.scaling_translation.y;
		_json[VVIS_FREEGLUT_SETTINGS]["scaling_translation"]["z"] = this->freeglut_settings.scaling_translation.z;
		_json[VVIS_FREEGLUT_SETTINGS]["position_of_camera"]["x"] = this->freeglut_settings.position_of_camera.x;
		_json[VVIS_FREEGLUT_SETTINGS]["position_of_camera"]["y"] = this->freeglut_settings.position_of_camera.y;
		_json[VVIS_FREEGLUT_SETTINGS]["position_of_camera"]["z"] = this->freeglut_settings.position_of_camera.z;
		_json[VVIS_FREEGLUT_SETTINGS]["position_of_element"]["x"] = this->freeglut_settings.position_of_element.x;
		_json[VVIS_FREEGLUT_SETTINGS]["position_of_element"]["y"] = this->freeglut_settings.position_of_element.y;
		_json[VVIS_FREEGLUT_SETTINGS]["position_of_element"]["z"] = this->freeglut_settings.position_of_element.z;
		_json[VVIS_FREEGLUT_SETTINGS]["scaling_parameters_changes"]["x"] = this->freeglut_settings.scaling_parameters_changes.x;
		_json[VVIS_FREEGLUT_SETTINGS]["scaling_parameters_changes"]["y"] = this->freeglut_settings.scaling_parameters_changes.y;
		_json[VVIS_FREEGLUT_SETTINGS]["scaling_parameters_changes"]["z"] = this->freeglut_settings.scaling_parameters_changes.z;
		_json[VVIS_FREEGLUT_SETTINGS]["translation_changes"]["x"] = this->freeglut_settings.translation_changes.x;
		_json[VVIS_FREEGLUT_SETTINGS]["translation_changes"]["y"] = this->freeglut_settings.translation_changes.y;
		_json[VVIS_FREEGLUT_SETTINGS]["translation_changes"]["z"] = this->freeglut_settings.translation_changes.z;
		_json[VVIS_FREEGLUT_SETTINGS]["camera_changes"]["x"] = this->freeglut_settings.camera_changes.x;
		_json[VVIS_FREEGLUT_SETTINGS]["camera_changes"]["y"] = this->freeglut_settings.camera_changes.y;
		_json[VVIS_FREEGLUT_SETTINGS]["camera_changes"]["z"] = this->freeglut_settings.camera_changes.z;
		_json[VVIS_FREEGLUT_SETTINGS]["translation_by_element"] = this->freeglut_settings.translation_by_element;
		_json[VVIS_FREEGLUT_SETTINGS]["fullscreen"] = this->freeglut_settings.fullscreen;
		_json[VVIS_FREEGLUT_SETTINGS]["main_window"]["height"] = this->freeglut_settings.main_window.height;
		_json[VVIS_FREEGLUT_SETTINGS]["main_window"]["width"] = this->freeglut_settings.main_window.width;
		_json[VVIS_FREEGLUT_SETTINGS]["estrangement_changes"] = this->freeglut_settings.estrangement_changes;
	}

	file << _json.dump(4);
	file.close();

	return true;
}

bool Settings::get_by_json(const nlohmann::json& _json, wchar_t _flag) {
	if (_json == nullptr) return false;
	if (_flag == L'g' || _flag == L'a') {
		if (_json[VVIS_GLOBAL_SETTINGS] == nullptr) return false;

		if (_json[VVIS_GLOBAL_SETTINGS]["path_to_folder"] == nullptr); else this->global_settings.path_to_folder = _json[VVIS_GLOBAL_SETTINGS]["path_to_folder"].get<std::wstring>();
		if (_json[VVIS_GLOBAL_SETTINGS]["path_to_sconfiguration_file"] == nullptr); else this->global_settings.path_to_sconfiguration_file = _json[VVIS_GLOBAL_SETTINGS]["path_to_sconfiguration_file"].get<std::wstring>();
		if (_json[VVIS_GLOBAL_SETTINGS]["number_of_file"] == nullptr); else this->global_settings.number_of_file = _json[VVIS_GLOBAL_SETTINGS]["number_of_file"].get<int>();
		if (_json[VVIS_GLOBAL_SETTINGS]["index_of_spin"] == nullptr); else this->global_settings.index_of_spin = _json[VVIS_GLOBAL_SETTINGS]["index_of_spin"].get<int>();

	}

	if (_flag == L'f' || _flag == L'a') {
		if (_json[VVIS_FREEGLUT_SETTINGS] == nullptr) return false;


		if (_json[VVIS_FREEGLUT_SETTINGS]["background"]["red"] == nullptr); else this->freeglut_settings.backgroundcolor.red = _json[VVIS_FREEGLUT_SETTINGS]["background"]["red"].get<double>();
		if (_json[VVIS_FREEGLUT_SETTINGS]["background"]["green"] == nullptr); else this->freeglut_settings.backgroundcolor.green = _json[VVIS_FREEGLUT_SETTINGS]["background"]["green"].get<double>();
		if (_json[VVIS_FREEGLUT_SETTINGS]["background"]["blue"] == nullptr); else this->freeglut_settings.backgroundcolor.blue = _json[VVIS_FREEGLUT_SETTINGS]["background"]["blue"].get<double>();
		if (_json[VVIS_FREEGLUT_SETTINGS]["coloring_sample"] == nullptr); else this->freeglut_settings.coloring_sample = _json[VVIS_FREEGLUT_SETTINGS]["coloring_sample"].get<bool>();
		if (_json[VVIS_FREEGLUT_SETTINGS]["shape"] == nullptr); else this->freeglut_settings.shape = _json[VVIS_FREEGLUT_SETTINGS]["shape"].get<wchar_t>();
		if (_json[VVIS_FREEGLUT_SETTINGS]["shape_str"] == nullptr); else this->freeglut_settings.shape_wstr = _json[VVIS_FREEGLUT_SETTINGS]["shape_str"].get<std::wstring>();
		if (_json[VVIS_FREEGLUT_SETTINGS]["additional_rotation"]["phi"] == nullptr); else this->freeglut_settings.additional_rotation.phi = _json[VVIS_FREEGLUT_SETTINGS]["additional_rotation"]["phi"].get<double>();
		if (_json[VVIS_FREEGLUT_SETTINGS]["additional_rotation"]["theta"] == nullptr); else this->freeglut_settings.additional_rotation.theta = _json[VVIS_FREEGLUT_SETTINGS]["additional_rotation"]["theta"].get<double>();
		if (_json[VVIS_FREEGLUT_SETTINGS]["estrangement"] == nullptr); else this->freeglut_settings.estrangement = _json[VVIS_FREEGLUT_SETTINGS]["estrangement"].get<double>();
		if (_json[VVIS_FREEGLUT_SETTINGS]["global_translation"]["x"] == nullptr); else this->freeglut_settings.global_translation.x = _json[VVIS_FREEGLUT_SETTINGS]["global_translation"]["x"].get<double>();
		if (_json[VVIS_FREEGLUT_SETTINGS]["global_translation"]["y"] == nullptr); else this->freeglut_settings.global_translation.y = _json[VVIS_FREEGLUT_SETTINGS]["global_translation"]["y"].get<double>();
		if (_json[VVIS_FREEGLUT_SETTINGS]["global_translation"]["z"] == nullptr); else this->freeglut_settings.global_translation.z = _json[VVIS_FREEGLUT_SETTINGS]["global_translation"]["z"].get<double>();
		if (_json[VVIS_FREEGLUT_SETTINGS]["scaling_parameters"]["x"] == nullptr); else this->freeglut_settings.scaling_parameters.x = _json[VVIS_FREEGLUT_SETTINGS]["scaling_parameters"]["x"].get<double>();
		if (_json[VVIS_FREEGLUT_SETTINGS]["scaling_parameters"]["y"] == nullptr); else this->freeglut_settings.scaling_parameters.y = _json[VVIS_FREEGLUT_SETTINGS]["scaling_parameters"]["y"].get<double>();
		if (_json[VVIS_FREEGLUT_SETTINGS]["scaling_parameters"]["z"] == nullptr); else this->freeglut_settings.scaling_parameters.z = _json[VVIS_FREEGLUT_SETTINGS]["scaling_parameters"]["z"].get<double>();
		if (_json[VVIS_FREEGLUT_SETTINGS]["scaling_translation"]["x"] == nullptr); else this->freeglut_settings.scaling_translation.x = _json[VVIS_FREEGLUT_SETTINGS]["scaling_translation"]["x"].get<double>();
		if (_json[VVIS_FREEGLUT_SETTINGS]["scaling_translation"]["y"] == nullptr); else this->freeglut_settings.scaling_translation.y = _json[VVIS_FREEGLUT_SETTINGS]["scaling_translation"]["y"].get<double>();
		if (_json[VVIS_FREEGLUT_SETTINGS]["scaling_translation"]["z"] == nullptr); else this->freeglut_settings.scaling_translation.z = _json[VVIS_FREEGLUT_SETTINGS]["scaling_translation"]["z"].get<double>();
		if (_json[VVIS_FREEGLUT_SETTINGS]["position_of_camera"]["x"] == nullptr); else this->freeglut_settings.position_of_camera.x = _json[VVIS_FREEGLUT_SETTINGS]["position_of_camera"]["x"].get<double>();
		if (_json[VVIS_FREEGLUT_SETTINGS]["position_of_camera"]["y"] == nullptr); else this->freeglut_settings.position_of_camera.y = _json[VVIS_FREEGLUT_SETTINGS]["position_of_camera"]["y"].get<double>();
		if (_json[VVIS_FREEGLUT_SETTINGS]["position_of_camera"]["z"] == nullptr); else this->freeglut_settings.position_of_camera.z = _json[VVIS_FREEGLUT_SETTINGS]["position_of_camera"]["z"].get<double>();
		if (_json[VVIS_FREEGLUT_SETTINGS]["position_of_element"]["x"] == nullptr); else this->freeglut_settings.position_of_element.x = _json[VVIS_FREEGLUT_SETTINGS]["position_of_element"]["x"].get<double>();
		if (_json[VVIS_FREEGLUT_SETTINGS]["position_of_element"]["y"] == nullptr); else this->freeglut_settings.position_of_element.y = _json[VVIS_FREEGLUT_SETTINGS]["position_of_element"]["y"].get<double>();
		if (_json[VVIS_FREEGLUT_SETTINGS]["position_of_element"]["z"] == nullptr); else this->freeglut_settings.position_of_element.z = _json[VVIS_FREEGLUT_SETTINGS]["position_of_element"]["z"].get<double>();
		if (_json[VVIS_FREEGLUT_SETTINGS]["scaling_parameters_changes"]["x"] == nullptr); else this->freeglut_settings.scaling_parameters_changes.x = _json[VVIS_FREEGLUT_SETTINGS]["scaling_parameters_changes"]["x"].get<double>();
		if (_json[VVIS_FREEGLUT_SETTINGS]["scaling_parameters_changes"]["y"] == nullptr); else this->freeglut_settings.scaling_parameters_changes.y = _json[VVIS_FREEGLUT_SETTINGS]["scaling_parameters_changes"]["y"].get<double>();
		if (_json[VVIS_FREEGLUT_SETTINGS]["scaling_parameters_changes"]["z"] == nullptr); else this->freeglut_settings.scaling_parameters_changes.z = _json[VVIS_FREEGLUT_SETTINGS]["scaling_parameters_changes"]["z"].get<double>();
		if (_json[VVIS_FREEGLUT_SETTINGS]["translation_changes"]["x"] == nullptr); else this->freeglut_settings.translation_changes.x = _json[VVIS_FREEGLUT_SETTINGS]["translation_changes"]["x"].get<double>();
		if (_json[VVIS_FREEGLUT_SETTINGS]["translation_changes"]["y"] == nullptr); else this->freeglut_settings.translation_changes.y = _json[VVIS_FREEGLUT_SETTINGS]["translation_changes"]["y"].get<double>();
		if (_json[VVIS_FREEGLUT_SETTINGS]["translation_changes"]["z"] == nullptr); else this->freeglut_settings.translation_changes.z = _json[VVIS_FREEGLUT_SETTINGS]["translation_changes"]["z"].get<double>();
		if (_json[VVIS_FREEGLUT_SETTINGS]["camera_changes"]["x"] == nullptr); else this->freeglut_settings.camera_changes.x = _json[VVIS_FREEGLUT_SETTINGS]["camera_changes"]["x"].get<double>();
		if (_json[VVIS_FREEGLUT_SETTINGS]["camera_changes"]["y"] == nullptr); else this->freeglut_settings.camera_changes.y = _json[VVIS_FREEGLUT_SETTINGS]["camera_changes"]["y"].get<double>();
		if (_json[VVIS_FREEGLUT_SETTINGS]["camera_changes"]["z"] == nullptr); else this->freeglut_settings.camera_changes.z = _json[VVIS_FREEGLUT_SETTINGS]["camera_changes"]["z"].get<double>();
		if (_json[VVIS_FREEGLUT_SETTINGS]["translation_by_element"] == nullptr); else this->freeglut_settings.translation_by_element = _json[VVIS_FREEGLUT_SETTINGS]["translation_by_element"].get<double>();
		if (_json[VVIS_FREEGLUT_SETTINGS]["fullscreen"] == nullptr); else this->freeglut_settings.fullscreen = _json[VVIS_FREEGLUT_SETTINGS]["fullscreen"].get<bool>();
		if (_json[VVIS_FREEGLUT_SETTINGS]["main_window"]["height"] == nullptr); else this->freeglut_settings.main_window.height = _json[VVIS_FREEGLUT_SETTINGS]["main_window"]["height"].get<int>();
		if (_json[VVIS_FREEGLUT_SETTINGS]["main_window"]["width"] == nullptr); else this->freeglut_settings.main_window.width = _json[VVIS_FREEGLUT_SETTINGS]["main_window"]["width"].get<int>();
		if (_json[VVIS_FREEGLUT_SETTINGS]["estrangement_changes"] == nullptr); else this->freeglut_settings.estrangement_changes = _json[VVIS_FREEGLUT_SETTINGS]["estrangement_changes"].get<double>();



	}


	return true;
}
#include <iostream>
bool Settings::get(wchar_t _flag) {
	std::fstream file; nlohmann::json _json;

	if (this->global_settings.path_to_settings_file == VVIS_PATH_PLUG_WSTR) {
		if (this->global_settings.path_to_settings_file_folder == VVIS_PATH_PLUG_WSTR) {
			if (this->global_settings.path_to_folder == VVIS_PATH_PLUG_WSTR) {
				return false;
			}
			this->global_settings.path_to_settings_file_folder = this->global_settings.path_to_folder;
		}
		this->global_settings.path_to_settings_file = this->global_settings.path_to_settings_file_folder + L"/" + VVIS_SETTINGS_FILE_NAME_WSTR;
	}

	if (file_exist(this->global_settings.path_to_settings_file)) {
		file.open(this->global_settings.path_to_settings_file, std::ios_base::in);
		_json << file;
		file.close();
	}
	

	return this->get_by_json(_json, _flag);

}
