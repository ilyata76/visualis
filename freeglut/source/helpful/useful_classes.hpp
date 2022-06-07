#pragma once

#ifndef USEFUL_CLASSES_HPP
#define USEFUL_CLASSES_HPP

	struct Vec3f {
		double x;
		double y;
		double z;

		Vec3f() : x(0), y(0), z(0) {};
		Vec3f(double _x, double _y, double _z) : x(_x), y(_y), z(_z) {};
	};

	typedef Vec3f Point3f;
	typedef Vec3f Direction3f;
	typedef Vec3f Parameters3f;

	struct Angle2f {
		double phi;
		double theta;

		Angle2f() : phi(0), theta(0) {};
		Angle2f(double _phi, double _theta) : phi(_phi), theta(_theta) {};
	};

	struct WindowParameters {
		int width;
		int height;

		WindowParameters() : width(0), height(0) {};
		WindowParameters(double _width, double _height) : width(_width), height(_height) {};
	};


#endif // !USEFUL_CLASSES_HPP