#pragma once

#ifndef CONVERTER_V5_HPP
#define CONVERTER_V5_HPP

// идея конвертера - он конвертирует файл и создаёт другой и только
// formatted string: NUMBER?COUNT?m;l;x;y;z;sx;sy;sz!x;y;z;sx;sy;sz!

	#include <string>
	#include <algorithm>
	#include <fstream>

	#include "../../libraries/tia-Exceptio/include/assert.hpp"
	#include "../defines.hpp"

	namespace vampire5 {

		namespace converter {

			std::string get_number_of_file_from_f_str(const std::string& f_str, int& index); // NUMBER?
			std::string get_count_from_f_str(const std::string& f_str, int& index); // COUNT?

			std::string get_output_str(const std::string& f_str, int& index); // m;l;x;y;z;sx;sy;sz!

			std::string get_file_name(const std::string& number);

			bool convert(const std::string& formatted_str, const std::string& path_to_folder, int& index);

		}

	}


#endif // !CONVERTER_HPP