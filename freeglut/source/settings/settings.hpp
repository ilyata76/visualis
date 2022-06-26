#pragma once


#ifndef SETTINGS_HPP
#define SETTINGS_HPP

	#include "./freeglut_settings.hpp"
	#include "./global_settings.hpp"

	#include "../libraries/json/single_include/nlohmann/json.hpp"

	#include "../helpful/useful_functions.hpp"

	#include <fstream>

	class Settings {

		public:
			Global_settings global_settings;
			Freeglut_settings freeglut_settings;
			Window main_window;
			std::vector<Window> subwindows;

			Settings() {};
			Settings(const Global_settings& _g_s, const Freeglut_settings& _f_s) : global_settings(_g_s), freeglut_settings(_f_s) {};

			friend std::wostream& operator<<(std::wostream& _out, const Settings& _settings);

			std::wostream& print_only_global(std::wostream& _out);

			std::wostream& print_only_freeglut(std::wostream& _out);

			// flag: g - only global, f - only freeglut, a - all
			bool save(wchar_t _flag);

			// flag: g - only global, f - only freeglut, a - all
			bool get_by_json(const nlohmann::json& _json, wchar_t _flag);

			// flag: g - only global, f - only freeglut, a - all
			bool get(wchar_t _flag);

			~Settings() {};
	};


#endif // !SETTINGS_HPP
