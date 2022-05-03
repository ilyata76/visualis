#pragma once


#ifndef COLOR_CLASS_HPP
#define COLOR_CLASS_HPP

namespace vvis {
	namespace visualization {

		class VvisColor {
			//
		};

		class VvisColor_3f : public VvisColor {
			public:
				float red; float green; float blue;

				VvisColor_3f() : red(1), green(1), blue(1) {};
				VvisColor_3f(float red, float green, float blue) : red(red), green(green), blue(blue) {};
		};

		VvisColor_3f get_color_by_direction(float x, float y, float z);

	}
}

#endif // !COLOR_CLASS_HPP
