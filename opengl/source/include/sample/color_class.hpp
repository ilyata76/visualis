#pragma once


#ifndef COLOR_CLASS_HPP
#define COLOR_CLASS_HPP

	#include <math.h>

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


			typedef struct {
				double r;       // a fraction between 0 and 1
				double g;       // a fraction between 0 and 1
				double b;       // a fraction between 0 and 1
			} rgb;

			typedef struct {
				double h;       // angle in degrees
				double s;       // a fraction between 0 and 1
				double v;       // a fraction between 0 and 1
			} hsv;

			rgb hsv2rgb(hsv in);

		}
	}

#endif // !COLOR_CLASS_HPP
