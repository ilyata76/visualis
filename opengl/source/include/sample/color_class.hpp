#pragma once


#ifndef COLOR_CLASS_HPP
#define COLOR_CLASS_HPP

namespace vvis {
	namespace visualization {

		class VvisColor_3f {
			public:
				int red; int green; int blue;

				VvisColor_3f() : red(1), green(1), blue(1) {};
				VvisColor_3f(int red, int green, int blue) : red(red), green(green), blue(blue) {};
		};

		VvisColor_3f get_color_by_direction(int x, int y, int z);

	}
}

#endif // !COLOR_CLASS_HPP
