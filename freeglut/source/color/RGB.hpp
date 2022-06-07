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
	};

	RGB get_color_by_direction(const double& _x, const double& _y, const double& _z) {
		//https://en.wikipedia.org/wiki/HSL_and_HSV

		//HSL
		//https://galactic.ink/sphere/
		//HUE 0-360 - будет нашем углом arctg 0-360
		//Luminance 0-100 - от оси Z 0-180

		double hue = get_euler_phi(_x, _y, _z); //Given a color with hue H ∈ [0°, 360°], saturation SL ∈ [0, 1], and lightness L ∈ [0, 1], we first find chroma:
		double lightness = (get_euler_theta(_x, _y, _z) * 1 / 180);
		double saturation = 1;

		double chroma = ( 1 - fabs(2.0 * lightness - 1.0) * saturation );
		double h = ( hue / 60 );
		double intermediate_X = ( chroma * (1 - fabs(fmod(h, 2.0) - 1)) );
	
		double R1 = 0, G1 = 0, B1 = 0;

		if		(h >= 0 && h < 1)	{ R1 = chroma; G1 = intermediate_X; B1 = 0; }
		else if (h >= 1 && h < 2)	{ R1 = intermediate_X; G1 = chroma; B1 = 0; }
		else if (h >= 2 && h < 3)	{ R1 = 0; G1 = chroma; B1 = intermediate_X; }
		else if (h >= 3 && h < 4)	{ R1 = 0; G1 = intermediate_X; B1 = chroma; }
		else if (h >= 4 && h < 5)	{ R1 = intermediate_X; G1 = 0; B1 = chroma; }
		else						{ R1 = chroma; G1 = 0; B1 = intermediate_X; }
	
		double m = lightness - chroma / 2;

		return RGB(R1 + m, G1 + m, B1 + m);
	}


#endif // !RGB_HPP
