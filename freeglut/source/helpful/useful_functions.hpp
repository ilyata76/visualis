#pragma once


#ifndef USEFUL_FUNCTIONS
#define USEFUL_FUNCTIONS

	#include <math.h>
	#include <sys/stat.h>
	#include <string>
	#include <ostream>
	#include <vector>
	#include <sstream>
	#include <algorithm>
	#include <map>
	#include <random>
	#include <fstream>
	#include "./global_defines.hpp"
	#include "../libraries/exceptio/include/assert.hpp"

	float get_euler_phi(const double& sx, const double& sy, const double& sz);

	float get_euler_theta(const double& sx, const double& sy, const double& sz);

	bool file_exist(const std::string _path);

	std::wostream& print_logo(std::wostream& _out);

	std::vector<std::wstring> line_to_vector(const std::wstring& _sstream);
	
	std::wstring to_lower_wstr(std::wstring& _value);

	std::wostream& print_vector(std::wostream& _out, std::vector<std::wstring>& _vector, std::wstring separator = L" ");

	// GNU: (_commands[2]) <- cannot convert to link
	int get_second_from_map(std::map<std::wstring, int>& _map, std::wstring _value);

	std::wstring remove_quotations(std::wstring& _str);

	bool is_number(const std::wstring& _str);

	bool contains_substr(const std::string& _str, const std::string& _substr);

	std::wstring by_synonyms(const std::wstring& _value);

	std::string v5_get_file_number(const std::string& _number);

	std::string wstr2str(const std::wstring& _wstr);
	std::wstring str2wstr(const std::string& _wstr);

	const char* c_str(const std::string& _str);

	bool is_double(std::wstring& _value);

	int int_rand_result(int a, int b);

#endif // !USEFUL_FUNCTIONS
