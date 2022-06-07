#pragma once


#ifndef USEFUL_FUNCTIONS
#define USEFUL_FUNCTIONS

	#include <math.h>
	#include <sys/stat.h>
	#include <string>
	#include "./global_defines.hpp"

	float get_euler_phi(const double& sx, const double& sy, const double& sz) {
		int sign = -1;
		if (VVIS_COUNTERCLOCKWISE) sign = 1;
		if (sx > 0 && sy > 0) {
			return (sign * atan(fabs(sy / sx)) * 180.0 / 3.1415);
		} else if (sx < 0 && sy > 0) {
			return (sign * (180 - (atan(fabs(sy / sx))) * 180.0 / 3.1415));
		} else if (sx < 0 && sy < 0) {
			return (sign * (270 - (atan(fabs(sx / sy))) * 180.0 / 3.1415));
		} else if (sx > 0 && sy < 0) {
			return (sign * (360 - (atan(fabs(sy / sx))) * 180.0 / 3.1415));
		} else {
			if (sy == 0) if (sx < 0) return (sign * 180.0); else return (sign * 0.0);
			if (sx == 0) if (sy > 0) return (sign * 90.0); else return (sign * (-90.0));
		} return (sign * 0.0f);
	}

	float get_euler_theta(const double& sx, const double& sy, const double& sz) {
		int sign = -1;
		if (VVIS_COUNTERCLOCKWISE) sign = 1;
	
		if (sz == 0) return (sign * 90.0f);
	
		if (sz > 0) return (sign * (atan(fabs(sqrt(pow(sx, 2) + pow(sy, 2))) / fabs(sz))) * 180.0 / 3.1415);
		else return (sign * (180 - (atan(fabs(sqrt(pow(sx, 2) + pow(sy, 2)) / sz))) * 180.0 / 3.1415));


		return (sign * 0.0f);
	}

	bool file_exist(std::wstring& _path) {
		struct _stat buf;
		return (_wstat(_path.c_str(), &buf) != -1);
	}

#endif // !USEFUL_FUNCTIONS
