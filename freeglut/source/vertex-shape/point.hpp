#pragma once


#ifndef POINT_HPP
#define POINT_HPP

	class Point {
		public:
			double x; double y; double z;

			Point() : x(0.0), y(0.0), z(0.0) {};
			Point(double& x, double& y, double& z) : x(x), y(y), z(z) {};
			Point(double x, double y, double z) : x(x), y(y), z(z) {};
			~Point() {};
	};

#endif // !POINT_HPP
