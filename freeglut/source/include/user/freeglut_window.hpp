#pragma once


#ifndef FREEGLUT_WINDOW_HPP
#define FREEGLUT_WINDOW_HPP

	#include <ostream>
	#include "../defines.hpp"
	#include "../sample/color_class.hpp"
	#include "../../libraries/json/single_include/nlohmann/json.hpp"
	#include "../sample/vec.hpp"
	#include "../sample/creator_of_vertex_arr.hpp"

	namespace vvis {

		namespace visualization {

			inline bool file_exist(const std::wstring& s);

			nlohmann::json get_settings_json(const std::wstring& _path_to_file);

			struct Freeglut_settings {
				public:

					Angle2f additional_rotation					= Angle2f(0.0, 0.0);
					double estrangement							= 1.0;
					Point3f global_translation					= Point3f(0.0, 0.0, 0.0);
					Parameters3f scaling_parameters				= Parameters3f(20.0, 20.0, 20.0);
					Parameters3f scaling_translation			= Parameters3f(1.0, 1.0, 1.0);
					Point3f position_of_camera					= Point3f(0.0, 0.0, 0.0);
					Point3f position_of_element					= Point3f(0.0, 0.0, -100.0);
					Parameters3f scaling_parameters_changes		= Parameters3f(SCALING_PARAMETERS_CHANGES_X, SCALING_PARAMETERS_CHANGES_Y, SCALING_PARAMETERS_CHANGES_Z);
					Parameters3f translation_changes			= Parameters3f(TRANSLATION_CHANGES_X, TRANSLATION_CHANGES_Y, TRANSLATION_CHANGES_Z);
					Parameters3f camera_changes					= Parameters3f(CAMERA_CHANGES_X, CAMERA_CHANGES_Y, CAMERA_CHANGES_Z);
					double translation_by_element				= ELEMENT_TRANSLATION;
					bool fullscreen								= false;
					WindowParameters main_window				= WindowParameters(0.0, 0.0);
					double estrangement_changes					= ESTRAGNEMENT_CHANGES;


					friend std::wostream& operator<<(std::wostream& _out, const Freeglut_settings& _settings);
					
					bool save_settings();
					bool get_settings_by_json(const nlohmann::json& _json);
					bool get_settings();

			};


		}

	}

#endif // !FREEGLUT_WINDOW_HPP
