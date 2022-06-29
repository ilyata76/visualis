#pragma once


#ifndef FREEGLUT_SETTINGS_HPP
#define FREEGLUT_SETTINGS_HPP

	#include "../helpful/useful_classes.hpp"
	#include "../helpful/global_defines.hpp"
	#include "../color/RGB.hpp"

	#include <string>
	#include <ostream>

	class Freeglut_settings {
		
		public:
			
			//Rgb backgroundcolor;
			bool coloring_sample;
			wchar_t shape;
			std::wstring shape_wstr;
			Angle2f additional_rotation;
			double estrangement;
			Point3f global_translation;
			Parameters3f scaling_parameters;
			Parameters3f scaling_translation;
			Point3f position_of_camera;
			Point3f position_of_element;
			Parameters3f scaling_parameters_changes;
			Parameters3f translation_changes;
			Parameters3f camera_changes;
			double translation_by_element;
			bool fullscreen;
			//WindowParameters main_window;
			double estrangement_changes;
			bool use_additional_subwindows;
			
			Freeglut_settings();

			friend std::wostream& operator<<(std::wostream& _out, const Freeglut_settings& _settings);

			~Freeglut_settings() {};
	};

#endif // !FREEGLUT_SETTINGS_HPP
