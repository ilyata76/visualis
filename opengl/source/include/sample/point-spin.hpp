#pragma once

#ifndef POINT_SPIN_HPP
#define POINT_SPIN_HPP

	#include <string>

	namespace vvis {

		namespace creator {

			class Point {
				protected:
					double x;
					double y;
					double z;

				public:
					Point();
					Point(double x, double y, double z);
					Point(double x, double y);

					double get(std::wstring& what);
			};

			class Spin {
				protected:
					double sx;
					double sy;
					double sz;

				public:
					Spin();
					Spin(double sx, double sy, double sz);
					Spin(double sx, double sy);

					double get(std::wstring& what);
			};


		};

	};

#endif // !POINT_SPIN_HPP