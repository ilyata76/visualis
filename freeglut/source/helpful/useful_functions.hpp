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
	#include "./global_defines.hpp"

	float get_euler_phi(const double& sx, const double& sy, const double& sz);

	float get_euler_theta(const double& sx, const double& sy, const double& sz);

	bool file_exist(const std::wstring& _path);

	std::wostream& print_logo(std::wostream& _out);

	std::vector<std::wstring> line_to_vector(const std::wstring& _sstream);
	
	std::wstring to_lower_wstr(std::wstring& _value);

	std::wostream& print_vector(std::wostream& _out, std::vector<std::wstring>& _vector, std::wstring separator = L" ");

	int get_second_from_map(std::map<std::wstring, int>& _map, std::wstring& _value);

#endif // !USEFUL_FUNCTIONS
