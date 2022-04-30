#pragma once

#ifndef CONVERTER_V5_HPP
#define CONVERTER_V5_HPP

// идея конвертера - он конвертирует файл и создаёт другой и только
// formatted string: NUMBER?COUNT?m;l;x;y;z;sx;sy;sz!x;y;z;sx;sy;sz!

	#include <string>
	#include "../../libraries/tia-Exceptio/include/assert.hpp"
	#include "../defines.hpp"

	namespace vampire5 {

		namespace converter {

			std::string get_number_of_file_from_f_str(std::string& f_str, int& index); // NUMBER?
			std::string get_count_from_f_str(std::string& f_str, int& index); // COUNT?
			std::string get_output_str(std::string& f_str, int& index); // m;l;x;y;z;sx;sy;sz!
			std::string get_spin_file_name(std::string& number);
			bool convert(std::string& formatted_str);

		}

	}


#endif // !CONVERTER_HPP