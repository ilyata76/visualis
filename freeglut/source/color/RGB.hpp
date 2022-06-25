#pragma once


#ifndef RGB_HPP
#define RGB_HPP

	#include "../helpful/useful_functions.hpp"

	// red green blue from values 0.0 to 1.0
	class RGB {
		public:
			double red, green, blue;

			RGB() : red(1.0), green(1.0), blue(1.0) {};
			RGB(const double& _red, const double& _green, const double& _blue) : red(_red), green(_green), blue(_blue) {};
			~RGB() {};
	};

	RGB get_color_by_direction(const double& _x, const double& _y, const double& _z);


#endif // !RGB_HPP
