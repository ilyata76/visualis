#pragma once


#ifndef USEFUL_FUNCTIONS
#define USEFUL_FUNCTIONS

	#include <math.h>
	#include <sys/stat.h>
	#include <string>
	#include "./global_defines.hpp"

	float get_euler_phi(const double& sx, const double& sy, const double& sz);

	float get_euler_theta(const double& sx, const double& sy, const double& sz);

	bool file_exist(std::wstring& _path);

#endif // !USEFUL_FUNCTIONS
