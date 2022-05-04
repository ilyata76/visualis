#pragma once


#ifndef COLOR_CLASS_HPP
#define COLOR_CLASS_HPP

	#include <math.h>
	#include "../defines.hpp"

	namespace vvis {
		namespace visualization {

			class VvisColor {
				//
			};

			class VvisColor_3f : public VvisColor {
				public:
					double red; double green; double blue;

					VvisColor_3f() : red(1), green(1), blue(1) {};
					VvisColor_3f(double red, double green, double blue) : red(red), green(green), blue(blue) {};
			};

			VvisColor_3f get_color_by_direction(double x, double y, double z);

		}
	}

#endif // !COLOR_CLASS_HPP
