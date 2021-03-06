#include "./settings.hpp"

std::wostream& operator<<(std::wostream& _out, const Settings& _settings) {
	_out << _settings.global_settings << _settings.freeglut_settings << _settings.other_settings;
	_out << L"\t Background of mainwindow color\t\t: " << _settings.main_window.backgroundcolor.red * 255.0 << L"/255 " << _settings.main_window.backgroundcolor.green * 255.0 << L"/255 " << _settings.main_window.backgroundcolor.blue * 255.0 << L"/255\n";
	
	int j = 0;
	for (const auto& window : _settings.subwindows) {
		_out << L"\t Background of subwindow" << j << " color\t\t: " << window.backgroundcolor.red * 255.0 << L"/255 " << window.backgroundcolor.green * 255.0 << L"/255 " << window.backgroundcolor.blue * 255.0 << L"/255\n";
		++j;
	}

	_out << L"\t Window\t\t\t\t\t: (" << _settings.main_window.wh.height << L", " << _settings.main_window.wh.width << L")\n";
	return _out;
};

std::wostream& Settings::print_only_global(std::wostream& _out) {
	return operator<<(_out, this->global_settings);
}

std::wostream& Settings::print_only_freeglut(std::wostream& _out) {
	return operator<<(_out, this->freeglut_settings);
}

std::wostream& Settings::print_only_other(std::wostream& _out) {
	return operator<<(_out, this->other_settings);
}

bool Settings::save(wchar_t _flag) {
	Assert((_flag == L'a' || _flag == L'o' || _flag == L'f' || _flag == L'g'), 1, L"unknown flag", L"Assert, settings.save");
	try {
		std::fstream file; nlohmann::json _json; //nlohmann::json _json_backup;

		if (this->global_settings.path_to_settings_file == VVIS_PATH_PLUG_WSTR) {
			if (this->global_settings.path_to_settings_file_folder == VVIS_PATH_PLUG_WSTR) {
				if (this->global_settings.path_to_folder == VVIS_PATH_PLUG_WSTR) {
					return false;
				}
				this->global_settings.path_to_settings_file_folder = this->global_settings.path_to_folder;
			}
			this->global_settings.path_to_settings_file = this->global_settings.path_to_settings_file_folder + "/" + VVIS_SETTINGS_FILE_NAME_WSTR;
		}

		//if (file_exist(this->global_settings.path_to_settings_file)) {
		//	file.open(c_str(this->global_settings.path_to_settings_file), std::ios_base::in);
		//	_json_backup << file;
		//	file.close();
		//}

		file.open(this->global_settings.path_to_settings_file, std::ios_base::out | std::ios_base::trunc);

		if (_flag == L'g' || _flag == L'a') {

			_json[VVIS_GLOBAL_SETTINGS]["path_to_folder"] = this->global_settings.path_to_folder;

			_json[VVIS_GLOBAL_SETTINGS]["path_to_sconfiguration_file"] = this->global_settings.path_to_sconfiguration_file;

			_json[VVIS_GLOBAL_SETTINGS]["number_of_file"] = this->global_settings.number_of_file;

			_json[VVIS_GLOBAL_SETTINGS]["index_of_spin"] = this->global_settings.index_of_spin;

		}
		///

		if (_flag == L'f' || _flag == L'a') {

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

			_json[VVIS_FREEGLUT_SETTINGS]["estrangement_changes"] = this->freeglut_settings.estrangement_changes;

			_json[VVIS_FREEGLUT_SETTINGS]["polygonrate"] = this->freeglut_settings.polygonrate;

			_json[VVIS_FREEGLUT_SETTINGS]["subwindowing"] = this->freeglut_settings.use_additional_subwindows;

			_json[VVIS_FREEGLUT_SETTINGS]["spinrate"] = this->freeglut_settings.spinrate;

			_json[VVIS_FREEGLUT_SETTINGS]["gap"] = this->freeglut_settings.gap;

			_json[VVIS_FREEGLUT_SETTINGS]["beta_light"] = this->freeglut_settings.beta_light;

		}

		if (_flag == L'w' || _flag == L'a') {

			_json[VVIS_WINDOWS_SETTINGS]["main_window"]["height"] = this->main_window.wh.height;
			_json[VVIS_WINDOWS_SETTINGS]["main_window"]["width"] = this->main_window.wh.width;
		

			_json[VVIS_WINDOWS_SETTINGS]["main_window"]["background"]["red"] = int(this->main_window.backgroundcolor.red * 255.0);
			_json[VVIS_WINDOWS_SETTINGS]["main_window"]["background"]["green"] = int(this->main_window.backgroundcolor.green * 255.0);
			_json[VVIS_WINDOWS_SETTINGS]["main_window"]["background"]["blue"] = int(this->main_window.backgroundcolor.blue * 255.0);
		
		
			_json[VVIS_WINDOWS_SETTINGS]["subwindows"]["count"] = this->subwindows.size();
		
			for (int j = 0; j < subwindows.size(); ++j) {
				_json[VVIS_WINDOWS_SETTINGS]["subwindows"][std::to_string(j)]["red"] = int(this->subwindows[j].backgroundcolor.red * 255.0);
				_json[VVIS_WINDOWS_SETTINGS]["subwindows"][std::to_string(j)]["green"] = int(this->subwindows[j].backgroundcolor.green * 255.0);
				_json[VVIS_WINDOWS_SETTINGS]["subwindows"][std::to_string(j)]["blue"] = int(this->subwindows[j].backgroundcolor.blue * 255.0);
			}

		}

		if (_flag == L'o' || _flag == L'a') {

			_json[VVIS_OTHER_SETTINGS]["axis_by_cones"] = this->other_settings.axis_by_cones;

			_json[VVIS_OTHER_SETTINGS]["show_axis_names"] = this->other_settings.show_axis_names;

			_json[VVIS_OTHER_SETTINGS]["inverted_black_text_stats"] = this->other_settings.inverted_black_text_stats;

			_json[VVIS_OTHER_SETTINGS]["inverted_black_text_log"] = this->other_settings.inverted_black_text_log;

			_json[VVIS_OTHER_SETTINGS]["inverted_black_text_axis"] = this->other_settings.inverted_black_text_axis;

			_json[VVIS_OTHER_SETTINGS]["multilayer"] = this->other_settings.multilayering;

			_json[VVIS_OTHER_SETTINGS]["multimaterial"] = this->other_settings.multimaterialing;

			int materials_count = this->other_settings.materials.size();
			int layers_count = this->other_settings.layers.size();
			
			_json[VVIS_OTHER_SETTINGS]["layers"]["count"] = layers_count;
			
			
			for (int j = 0; j < layers_count; ++j) {

				_json[VVIS_OTHER_SETTINGS]["layers"][std::to_string(j)]["index"] = this->other_settings.layers[j].number;
				
				_json[VVIS_OTHER_SETTINGS]["layers"][std::to_string(j)]["color"]["red"] = int(this->other_settings.layers[j].color.red * 255.0);
				_json[VVIS_OTHER_SETTINGS]["layers"][std::to_string(j)]["color"]["green"] = int(this->other_settings.layers[j].color.green * 255.0);
				_json[VVIS_OTHER_SETTINGS]["layers"][std::to_string(j)]["color"]["blue"] = int(this->other_settings.layers[j].color.blue * 255.0);

				_json[VVIS_OTHER_SETTINGS]["layers"][std::to_string(j)]["name"] = this->other_settings.layers[j].name;

			}

			_json[VVIS_OTHER_SETTINGS]["materials"]["count"] = materials_count;
			
			for (int j = 0; j < materials_count; ++j) {

				_json[VVIS_OTHER_SETTINGS]["materials"][std::to_string(j)]["index"] = this->other_settings.materials[j].number;

				_json[VVIS_OTHER_SETTINGS]["materials"][std::to_string(j)]["color"]["red"] = int(this->other_settings.materials[j].color.red * 255.0);
				_json[VVIS_OTHER_SETTINGS]["materials"][std::to_string(j)]["color"]["green"] = int(this->other_settings.materials[j].color.green * 255.0);
				_json[VVIS_OTHER_SETTINGS]["materials"][std::to_string(j)]["color"]["blue"] = int(this->other_settings.materials[j].color.blue * 255.0);

				_json[VVIS_OTHER_SETTINGS]["materials"][std::to_string(j)]["name"] = this->other_settings.materials[j].name;

			}

		}


		file << _json.dump(4);
		file.close();

		return true;

	} catch(std::exception& E) {
		return false;
	}
}


bool Settings::get_by_json(const nlohmann::json& _json, wchar_t _flag) {
	Assert((_flag == L'a' || _flag == L'o' || _flag == L'f' || _flag == L'g'), 1, L"unknown flag", L"Assert, settings.get");
	try {

		if (_json == nullptr) return false;

		if (_flag == L'g' || _flag == L'a') {

			if (_json.contains(VVIS_GLOBAL_SETTINGS)) {

				if (_json[VVIS_GLOBAL_SETTINGS].contains("path_to_folder")) 
					this->global_settings.path_to_folder = _json[VVIS_GLOBAL_SETTINGS]["path_to_folder"].get<std::string>();

				if (_json[VVIS_GLOBAL_SETTINGS].contains("path_to_sconfiguration_file"))
					this->global_settings.path_to_sconfiguration_file = _json[VVIS_GLOBAL_SETTINGS]["path_to_sconfiguration_file"].get<std::string>();

				if (_json[VVIS_GLOBAL_SETTINGS].contains("number_of_file")) 
					this->global_settings.number_of_file = _json[VVIS_GLOBAL_SETTINGS]["number_of_file"].get<int>();

				if (_json[VVIS_GLOBAL_SETTINGS].contains("index_of_spin")) 
					this->global_settings.index_of_spin = _json[VVIS_GLOBAL_SETTINGS]["index_of_spin"].get<int>();

			} else return false;
		}

		if (_flag == L'f' || _flag == L'a') {
		
			if (_json.contains(VVIS_FREEGLUT_SETTINGS)) {

				if (_json[VVIS_FREEGLUT_SETTINGS].contains("coloring_sample"))
					this->freeglut_settings.coloring_sample = _json[VVIS_FREEGLUT_SETTINGS]["coloring_sample"].get<bool>();

				if (_json[VVIS_FREEGLUT_SETTINGS].contains("shape"))
					this->freeglut_settings.shape = _json[VVIS_FREEGLUT_SETTINGS]["shape"].get<wchar_t>();

				if (_json[VVIS_FREEGLUT_SETTINGS].contains("shape_str"))
					this->freeglut_settings.shape_wstr = _json[VVIS_FREEGLUT_SETTINGS]["shape_str"].get<std::wstring>();


				if (_json[VVIS_FREEGLUT_SETTINGS].contains("additional_rotation")) {

					if (_json[VVIS_FREEGLUT_SETTINGS]["additional_rotation"].contains("phi"))
						this->freeglut_settings.additional_rotation.phi = _json[VVIS_FREEGLUT_SETTINGS]["additional_rotation"]["phi"].get<double>();

					if (_json[VVIS_FREEGLUT_SETTINGS]["additional_rotation"].contains("theta"))
						this->freeglut_settings.additional_rotation.theta = _json[VVIS_FREEGLUT_SETTINGS]["additional_rotation"]["theta"].get<double>();

				}

				if (_json[VVIS_FREEGLUT_SETTINGS].contains("estrangement"))
					this->freeglut_settings.estrangement = _json[VVIS_FREEGLUT_SETTINGS]["estrangement"].get<double>();

				if (_json[VVIS_FREEGLUT_SETTINGS].contains("global_translation")) {

					if (_json[VVIS_FREEGLUT_SETTINGS]["global_translation"].contains("x")) 
						this->freeglut_settings.global_translation.x = _json[VVIS_FREEGLUT_SETTINGS]["global_translation"]["x"].get<double>();

					if (_json[VVIS_FREEGLUT_SETTINGS]["global_translation"].contains("y"))
						this->freeglut_settings.global_translation.y = _json[VVIS_FREEGLUT_SETTINGS]["global_translation"]["y"].get<double>();

					if (_json[VVIS_FREEGLUT_SETTINGS]["global_translation"].contains("z"))
						this->freeglut_settings.global_translation.z = _json[VVIS_FREEGLUT_SETTINGS]["global_translation"]["z"].get<double>();
				}
			
				if (_json[VVIS_FREEGLUT_SETTINGS].contains("scaling_parameters")) {

					if (_json[VVIS_FREEGLUT_SETTINGS]["scaling_parameters"].contains("x"))
						this->freeglut_settings.scaling_parameters.x = _json[VVIS_FREEGLUT_SETTINGS]["scaling_parameters"]["x"].get<double>();

					if (_json[VVIS_FREEGLUT_SETTINGS]["scaling_parameters"].contains("y"))
						this->freeglut_settings.scaling_parameters.y = _json[VVIS_FREEGLUT_SETTINGS]["scaling_parameters"]["y"].get<double>();

					if (_json[VVIS_FREEGLUT_SETTINGS]["scaling_parameters"].contains("z"))
						this->freeglut_settings.scaling_parameters.z = _json[VVIS_FREEGLUT_SETTINGS]["scaling_parameters"]["z"].get<double>();

				}

				if (_json[VVIS_FREEGLUT_SETTINGS].contains("scaling_translation")) {
				
					if (_json[VVIS_FREEGLUT_SETTINGS]["scaling_translation"].contains("x"))
						this->freeglut_settings.scaling_translation.x = _json[VVIS_FREEGLUT_SETTINGS]["scaling_translation"]["x"].get<double>();

					if (_json[VVIS_FREEGLUT_SETTINGS]["scaling_translation"].contains("y"))
						this->freeglut_settings.scaling_translation.y = _json[VVIS_FREEGLUT_SETTINGS]["scaling_translation"]["y"].get<double>();

					if (_json[VVIS_FREEGLUT_SETTINGS]["scaling_translation"].contains("z"))
						this->freeglut_settings.scaling_translation.z = _json[VVIS_FREEGLUT_SETTINGS]["scaling_translation"]["z"].get<double>();

				}

				if (_json[VVIS_FREEGLUT_SETTINGS].contains("position_of_camera")) {

					if (_json[VVIS_FREEGLUT_SETTINGS]["position_of_camera"].contains("x"))
						this->freeglut_settings.position_of_camera.x = _json[VVIS_FREEGLUT_SETTINGS]["position_of_camera"]["x"].get<double>();

					if (_json[VVIS_FREEGLUT_SETTINGS]["position_of_camera"].contains("y"))
						this->freeglut_settings.position_of_camera.y = _json[VVIS_FREEGLUT_SETTINGS]["position_of_camera"]["y"].get<double>();

					if (_json[VVIS_FREEGLUT_SETTINGS]["position_of_camera"].contains("z"))
						this->freeglut_settings.position_of_camera.z = _json[VVIS_FREEGLUT_SETTINGS]["position_of_camera"]["z"].get<double>();

				}

				if (_json[VVIS_FREEGLUT_SETTINGS].contains("position_of_element")) {

					if (_json[VVIS_FREEGLUT_SETTINGS]["position_of_element"].contains("x"))
						this->freeglut_settings.position_of_element.x = _json[VVIS_FREEGLUT_SETTINGS]["position_of_element"]["x"].get<double>();

					if (_json[VVIS_FREEGLUT_SETTINGS]["position_of_element"].contains("y"))
						this->freeglut_settings.position_of_element.y = _json[VVIS_FREEGLUT_SETTINGS]["position_of_element"]["y"].get<double>();

					if (_json[VVIS_FREEGLUT_SETTINGS]["position_of_element"].contains("z"))
						this->freeglut_settings.position_of_element.z = _json[VVIS_FREEGLUT_SETTINGS]["position_of_element"]["z"].get<double>();

				}

				if (_json[VVIS_FREEGLUT_SETTINGS].contains("scaling_parameters_changes")) {
				
					if (_json[VVIS_FREEGLUT_SETTINGS]["scaling_parameters_changes"].contains("x"))
						this->freeglut_settings.scaling_parameters_changes.x = _json[VVIS_FREEGLUT_SETTINGS]["scaling_parameters_changes"]["x"].get<double>();
				
					if (_json[VVIS_FREEGLUT_SETTINGS]["scaling_parameters_changes"].contains("y"))
						this->freeglut_settings.scaling_parameters_changes.y = _json[VVIS_FREEGLUT_SETTINGS]["scaling_parameters_changes"]["y"].get<double>();

					if (_json[VVIS_FREEGLUT_SETTINGS]["scaling_parameters_changes"].contains("z"))
						this->freeglut_settings.scaling_parameters_changes.z = _json[VVIS_FREEGLUT_SETTINGS]["scaling_parameters_changes"]["z"].get<double>();

				}

				if (_json[VVIS_FREEGLUT_SETTINGS].contains("translation_changes")) {

					if (_json[VVIS_FREEGLUT_SETTINGS]["translation_changes"].contains("x"))
						this->freeglut_settings.translation_changes.x = _json[VVIS_FREEGLUT_SETTINGS]["translation_changes"]["x"].get<double>();

					if (_json[VVIS_FREEGLUT_SETTINGS]["translation_changes"].contains("y"))
						this->freeglut_settings.translation_changes.y = _json[VVIS_FREEGLUT_SETTINGS]["translation_changes"]["y"].get<double>();

					if (_json[VVIS_FREEGLUT_SETTINGS]["translation_changes"].contains("z"))
						this->freeglut_settings.translation_changes.z = _json[VVIS_FREEGLUT_SETTINGS]["translation_changes"]["z"].get<double>();

				}
			
				if (_json[VVIS_FREEGLUT_SETTINGS].contains("camera_changes")) {

					if (_json[VVIS_FREEGLUT_SETTINGS]["camera_changes"].contains("x"))
						this->freeglut_settings.camera_changes.x = _json[VVIS_FREEGLUT_SETTINGS]["camera_changes"]["x"].get<double>();

					if (_json[VVIS_FREEGLUT_SETTINGS]["camera_changes"].contains("y")) 
						this->freeglut_settings.camera_changes.y = _json[VVIS_FREEGLUT_SETTINGS]["camera_changes"]["y"].get<double>();

					if (_json[VVIS_FREEGLUT_SETTINGS]["camera_changes"].contains("z"))
						this->freeglut_settings.camera_changes.z = _json[VVIS_FREEGLUT_SETTINGS]["camera_changes"]["z"].get<double>();

				}
			
				if (_json[VVIS_FREEGLUT_SETTINGS].contains("translation_by_element"))
					this->freeglut_settings.translation_by_element = _json[VVIS_FREEGLUT_SETTINGS]["translation_by_element"].get<double>();

				if (_json[VVIS_FREEGLUT_SETTINGS].contains("fullscreen"))
					this->freeglut_settings.fullscreen = _json[VVIS_FREEGLUT_SETTINGS]["fullscreen"].get<bool>();

				if (_json[VVIS_FREEGLUT_SETTINGS].contains("estrangement_changes"))
					this->freeglut_settings.estrangement_changes = _json[VVIS_FREEGLUT_SETTINGS]["estrangement_changes"].get<double>();

				if (_json[VVIS_FREEGLUT_SETTINGS].contains("polygonrate"))
					this->freeglut_settings.polygonrate = _json[VVIS_FREEGLUT_SETTINGS]["polygonrate"].get<double>();

				if (_json[VVIS_FREEGLUT_SETTINGS].contains("subwindowing"))
					this->freeglut_settings.use_additional_subwindows = _json[VVIS_FREEGLUT_SETTINGS]["subwindowing"].get<bool>();

				if (_json[VVIS_FREEGLUT_SETTINGS].contains("spinrate"))
					this->freeglut_settings.spinrate = _json[VVIS_FREEGLUT_SETTINGS]["spinrate"].get<int>();

				if (_json[VVIS_FREEGLUT_SETTINGS].contains("gap"))
					this->freeglut_settings.gap = _json[VVIS_FREEGLUT_SETTINGS]["gap"].get<int>();

				if (_json[VVIS_FREEGLUT_SETTINGS].contains("beta_light"))
					this->freeglut_settings.beta_light = _json[VVIS_FREEGLUT_SETTINGS]["beta_light"].get<bool>();


			} else return false;
		}

		if (_flag == L'w' || _flag == L'a') {

			if (_json.contains(VVIS_WINDOWS_SETTINGS)) {

				if (_json[VVIS_WINDOWS_SETTINGS].contains("main_window")) {

					if (_json[VVIS_WINDOWS_SETTINGS]["main_window"].contains("height"))
						this->main_window.wh.height = _json[VVIS_WINDOWS_SETTINGS]["main_window"]["height"].get<int>();

					if (_json[VVIS_WINDOWS_SETTINGS]["main_window"].contains("width"))
						this->main_window.wh.width = _json[VVIS_WINDOWS_SETTINGS]["main_window"]["width"].get<int>();

					if (_json[VVIS_WINDOWS_SETTINGS]["main_window"].contains("background")) {

						if (_json[VVIS_WINDOWS_SETTINGS]["main_window"]["background"].contains("red"))
							this->main_window.backgroundcolor.red = _json[VVIS_WINDOWS_SETTINGS]["main_window"]["background"]["red"].get<int>() / 255.0;

						if (_json[VVIS_WINDOWS_SETTINGS]["main_window"]["background"].contains("green"))
							this->main_window.backgroundcolor.green = _json[VVIS_WINDOWS_SETTINGS]["main_window"]["background"]["green"].get<int>() / 255.0;

						if (_json[VVIS_WINDOWS_SETTINGS]["main_window"]["background"].contains("blue"))
							this->main_window.backgroundcolor.blue = _json[VVIS_WINDOWS_SETTINGS]["main_window"]["background"]["blue"].get<int>() / 255.0;

					}

				}

				if (_json[VVIS_WINDOWS_SETTINGS].contains("subwindows")) {

					int count = 0;

					if (_json[VVIS_WINDOWS_SETTINGS]["subwindows"].contains("count"))
						count = _json[VVIS_WINDOWS_SETTINGS]["subwindows"]["count"].get<int>();

					if (count <= this->subwindows.size()) {

						for (int j = 0; j < count; ++j) {

							if (_json[VVIS_WINDOWS_SETTINGS]["subwindows"].contains(std::to_string(j))) {

								if (_json[VVIS_WINDOWS_SETTINGS]["subwindows"][std::to_string(j)].contains("red"))
									this->subwindows[j].backgroundcolor.red = _json[VVIS_WINDOWS_SETTINGS]["subwindows"][std::to_string(j)]["red"].get<int>() / 255.0;

								if (_json[VVIS_WINDOWS_SETTINGS]["subwindows"][std::to_string(j)].contains("green"))
									this->subwindows[j].backgroundcolor.green = _json[VVIS_WINDOWS_SETTINGS]["subwindows"][std::to_string(j)]["green"].get<int>() / 255.0;

								if (_json[VVIS_WINDOWS_SETTINGS]["subwindows"][std::to_string(j)].contains("blue"))
									this->subwindows[j].backgroundcolor.blue = _json[VVIS_WINDOWS_SETTINGS]["subwindows"][std::to_string(j)]["blue"].get<int>() / 255.0;

							}

						}

					}

				}

			} else return false;

		}

		if (_flag == L'o' || _flag == L'a') {

			if (_json.contains(VVIS_OTHER_SETTINGS)) {


				if (_json[VVIS_OTHER_SETTINGS].contains("axis_by_cones"))
					this->other_settings.axis_by_cones = _json[VVIS_OTHER_SETTINGS]["axis_by_cones"].get<bool>();

				if (_json[VVIS_OTHER_SETTINGS].contains("show_axis_names"))
					this->other_settings.show_axis_names = _json[VVIS_OTHER_SETTINGS]["show_axis_names"].get<bool>();

				if (_json[VVIS_OTHER_SETTINGS].contains("inverted_black_text_stats"))
					this->other_settings.inverted_black_text_stats = _json[VVIS_OTHER_SETTINGS]["inverted_black_text_stats"].get<bool>();

				if (_json[VVIS_OTHER_SETTINGS].contains("inverted_black_text_log"))
					this->other_settings.inverted_black_text_log = _json[VVIS_OTHER_SETTINGS]["inverted_black_text_log"].get<bool>();

				if (_json[VVIS_OTHER_SETTINGS].contains("inverted_black_text_axis"))
					this->other_settings.inverted_black_text_axis = _json[VVIS_OTHER_SETTINGS]["inverted_black_text_axis"].get<bool>();

				if (_json[VVIS_OTHER_SETTINGS].contains("multilayer"))
					this->other_settings.multilayering = _json[VVIS_OTHER_SETTINGS]["multilayer"].get<bool>();

				if (_json[VVIS_OTHER_SETTINGS].contains("multimaterial"))
					this->other_settings.multimaterialing = _json[VVIS_OTHER_SETTINGS]["multimaterial"].get<bool>();

				
				
				
				
				if (_json[VVIS_OTHER_SETTINGS].contains("layers")) {

					int l_count = 0;

					if (_json[VVIS_OTHER_SETTINGS]["layers"].contains("count"))
						l_count = _json[VVIS_OTHER_SETTINGS]["layers"]["count"].get<int>();

					this->other_settings.layers = {};

					for (int j = 0; j < l_count; ++j) {

						if (_json[VVIS_OTHER_SETTINGS]["layers"].contains(std::to_string(j))) {

							Layer layer;

							if (_json[VVIS_OTHER_SETTINGS]["layers"][std::to_string(j)].contains("color")) {

								if (_json[VVIS_OTHER_SETTINGS]["layers"][std::to_string(j)]["color"].contains("red"))
									layer.color.red = _json[VVIS_OTHER_SETTINGS]["layers"][std::to_string(j)]["color"]["red"].get<int>() / 255.0;

								if (_json[VVIS_OTHER_SETTINGS]["layers"][std::to_string(j)]["color"].contains("green"))
									layer.color.green = _json[VVIS_OTHER_SETTINGS]["layers"][std::to_string(j)]["color"]["green"].get<int>() / 255.0;

								if (_json[VVIS_OTHER_SETTINGS]["layers"][std::to_string(j)]["color"].contains("blue"))
									layer.color.blue = _json[VVIS_OTHER_SETTINGS]["layers"][std::to_string(j)]["color"]["blue"].get<int>() / 255.0;


							}

							if (_json[VVIS_OTHER_SETTINGS]["layers"][std::to_string(j)].contains("index"))
								layer.number = _json[VVIS_OTHER_SETTINGS]["layers"][std::to_string(j)]["index"].get<int>();

							if (_json[VVIS_OTHER_SETTINGS]["layers"][std::to_string(j)].contains("name"))
								layer.name = _json[VVIS_OTHER_SETTINGS]["layers"][std::to_string(j)]["name"].get<std::wstring>();

							this->other_settings.layers.push_back(layer);

						}

					}


				}


				if (_json[VVIS_OTHER_SETTINGS].contains("materials")) {

					int m_count = 0;

					if (_json[VVIS_OTHER_SETTINGS]["materials"].contains("count"))
						m_count = _json[VVIS_OTHER_SETTINGS]["materials"]["count"].get<int>();

					this->other_settings.materials = {};

					for (int j = 0; j < m_count; ++j) {

						if (_json[VVIS_OTHER_SETTINGS]["materials"].contains(std::to_string(j))) {

							Material material;

							if (_json[VVIS_OTHER_SETTINGS]["materials"][std::to_string(j)].contains("color")) {

								if (_json[VVIS_OTHER_SETTINGS]["materials"][std::to_string(j)]["color"].contains("red"))
									material.color.red = _json[VVIS_OTHER_SETTINGS]["materials"][std::to_string(j)]["color"]["red"].get<int>() / 255.0;

								if (_json[VVIS_OTHER_SETTINGS]["materials"][std::to_string(j)]["color"].contains("green"))
									material.color.green = _json[VVIS_OTHER_SETTINGS]["materials"][std::to_string(j)]["color"]["green"].get<int>() / 255.0;

								if (_json[VVIS_OTHER_SETTINGS]["materials"][std::to_string(j)]["color"].contains("blue"))
									material.color.blue = _json[VVIS_OTHER_SETTINGS]["materials"][std::to_string(j)]["color"]["blue"].get<int>() / 255.0;


							}

							if (_json[VVIS_OTHER_SETTINGS]["materials"][std::to_string(j)].contains("index"))
								material.number = _json[VVIS_OTHER_SETTINGS]["materials"][std::to_string(j)]["index"].get<int>();

							if (_json[VVIS_OTHER_SETTINGS]["materials"][std::to_string(j)].contains("name"))
								material.name = _json[VVIS_OTHER_SETTINGS]["materials"][std::to_string(j)]["name"].get<std::wstring>();

							this->other_settings.materials.push_back(material);

						}

					}

					

				}



			} else return false;

		}

		return true;

	} catch (std::exception& E) {
		return false;
	}
}

bool Settings::get(wchar_t _flag) {
	Assert((_flag == L'a' || _flag == L'o' || _flag == L'f' || _flag == L'g'), 1, L"unknown flag", L"Assert, settings.get");
	std::fstream file; nlohmann::json _json;

	if (this->global_settings.path_to_settings_file == VVIS_PATH_PLUG_WSTR) {
		if (this->global_settings.path_to_settings_file_folder == VVIS_PATH_PLUG_WSTR) {
			if (this->global_settings.path_to_folder == VVIS_PATH_PLUG_WSTR) {
				return false;
			}
			this->global_settings.path_to_settings_file_folder = this->global_settings.path_to_folder;
		}
		this->global_settings.path_to_settings_file = this->global_settings.path_to_settings_file_folder + "/" + VVIS_SETTINGS_FILE_NAME_WSTR;
	}

	if (file_exist(this->global_settings.path_to_settings_file)) {
		file.open(this->global_settings.path_to_settings_file, std::ios_base::in);
		if (file.is_open() && !file.eof()) _json << file;
		file.close();
	}
	

	return this->get_by_json(_json, _flag);

}
