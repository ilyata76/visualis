#pragma once


#ifndef PARSER_V5_HPP
#define PARSER_V5_HPP

	#include <string>
	#include <fstream>



	namespace vampire5 {

		namespace parser {

			using FUNCTION_STRING_CONSTINTL = std::string(*)(const int&);
			
			int get_count(const std::string& path_to_file);
			int get_count(const char* path_to_file);

			// format 

			// ���������, ����� ����� ���� �������� get_string(path)(file_number)

			// �������� string �������� NUMBER?COUNT?x;y;z;sx;sy;sz!x;y;z;sx;sy;sz ��� �������� const int& number �����
			std::string get_out(const int& number);
			FUNCTION_STRING_CONSTINTL get_string(const std::string& path_to_folder);

			std::string get_spin_file_name(const int& number);

			
		}

	}

#endif // PARSER-V5.HPP
