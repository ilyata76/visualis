#pragma once

#ifndef USEFUL_CLASSES_HPP
#define USEFUL_CLASSES_HPP

	#include "../color/RGB.hpp"

	struct Vec3f {
		double x;
		double y;
		double z;

		Vec3f() : x(0), y(0), z(0) {};
		Vec3f(double _x, double _y, double _z) : x(_x), y(_y), z(_z) {};
		~Vec3f() {};
	};

	typedef Vec3f Point3f;
	typedef Vec3f Direction3f;
	typedef Vec3f Parameters3f;

	struct Angle2f {
		double phi;
		double theta;

		Angle2f() : phi(0), theta(0) {};
		Angle2f(double _phi, double _theta) : phi(_phi), theta(_theta) {};
		~Angle2f() {};
	};

	struct WindowParameters {
		int width;
		int height;

		WindowParameters() : width(0), height(0) {};
		WindowParameters(double _width, double _height) : width(_width), height(_height) {};
		~WindowParameters() {};
	};

	struct WindowPosition {
		int x;
		int y;

		WindowPosition() : x(0), y(0) {};
		WindowPosition(int _x, int _y) : x(_x), y(_y) {};
		~WindowPosition() {};
	};

	struct Arrow {
		double x;
		double y;
		double pressed_position_x;
		double pressed_position_y;

		Arrow() : x(0), y(0), pressed_position_x(0), pressed_position_y(0) {};
		~Arrow() {};
	};

	class Window {
		public:

			int descriptor;
			WindowParameters wh;
			WindowPosition window_position;
			Rgb backgroundcolor;
			Arrow arrow;

			Window() : descriptor(0), wh(WindowParameters(500.0, 350.0)), backgroundcolor(Rgb(1.0, 1.0, 1.0)), window_position(WindowPosition(0, 0)) {};
			Window(int _descriptor, WindowParameters _wh, Rgb _background) : descriptor(_descriptor), wh(_wh), backgroundcolor(_background), window_position(WindowPosition(0, 0)) {};
			~Window() {};
	};


#endif // !USEFUL_CLASSES_HPP