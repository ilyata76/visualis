#pragma once


#ifndef RGB_HPP
#define RGB_HPP

	#include "../helpful/useful_functions.hpp"

	// red green blue values from 0.0 to 1.0
	class Rgb {
		public:
			double red, green, blue;

			Rgb() : red(1.0), green(1.0), blue(1.0) {};
			Rgb(const double& _red, const double& _green, const double& _blue) : red(_red), green(_green), blue(_blue) {};
			~Rgb() {};

			friend bool operator== (Rgb& a, Rgb& b);
			friend std::wostream& operator<<(std::wostream& _out, const Rgb& _rgb);

	};

	Rgb get_color_by_direction(const double& _x, const double& _y, const double& _z);


#endif // !RGB_HPP
