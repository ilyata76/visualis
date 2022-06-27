#pragma once


#ifndef SPIN_HPP
#define SPIN_HPP

	class Spin {
		public:
			double x; double y; double z;

			Spin() : x(0.0), y(0.0), z(0.0) {};
			Spin(double& x, double& y, double& z) : x(x), y(y), z(z) {};
			Spin(double x, double y, double z) : x(x), y(y), z(z) {};
			~Spin() {};
	};

#endif // !SPIN_HPP
