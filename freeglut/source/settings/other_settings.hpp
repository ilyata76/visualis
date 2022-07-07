#pragma once


#ifndef OTHER_SETTINGS_HPP
#define OTHER_SETTINGS_HPP

	#include "../helpful/useful_classes.hpp"
	#include "../helpful/global_defines.hpp"
	#include "../color/RGB.hpp"

	#include <string>
	#include <ostream>

	class Other_settings {
		
		public:
			
			bool axis_by_cones;// = false;
			bool show_axis_names;// = true;

			void* font_stats;// = GLUT_BITMAP_HELVETICA_12;
			void* font_log;// = GLUT_BITMAP_HELVETICA_12;

			bool inverted_black_text_stats;// = false;
			bool inverted_black_text_log;// = false;
			bool inverted_black_text_axis;// = false;

			Parameters3f transl_stats;// = { 0.0, 0.0, 0.0 };
			Parameters3f transl_log;// = { 0.0, 0.0, 0.0 };
			
			Other_settings();

			friend std::wostream& operator<<(std::wostream& _out, const Other_settings& _settings);

			~Other_settings() {};
	};

#endif // !OTHER_SETTINGS_HPP
