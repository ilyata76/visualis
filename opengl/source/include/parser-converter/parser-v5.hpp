#pragma once

#ifndef PARSER_V5_HPP
#define PARSER_V5_HPP

	#include <string>
	#include <fstream>
	#include <algorithm>

	#include "../../libraries/tia-Exceptio/include/assert.hpp"

	#include "../defines.hpp"

	namespace vampire5 {

		namespace parser {

			int get_count(const std::wstring& path_to_file);
			int get_count(const wchar_t* path_to_file);
			
			using FUNCTION_STRING_CONSTINTL = std::wstring(*)(const int&);
			// получает string форматом NUMBER?COUNT?x;y;z;sx;sy;sz!x;y;z;sx;sy;sz! для текущего const int& number файла
			std::wstring get_out(const int& number);
			FUNCTION_STRING_CONSTINTL get_string(const std::wstring& path_to_folder);

			std::wstring get_spin_file_name(const int& number);

		}

	}

#endif // PARSER-V5.HPP
