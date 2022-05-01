#pragma once

#ifndef POINT_SPIN_HPP
#define POINT_SPIN_HPP

	#include <string>

	#include "../../libraries/tia-Exceptio/include/assert.hpp"
	#include "../defines.hpp"

	namespace vvis {

		namespace creator {

			class Point {
				protected:
					double x;
					double y;
					double z;

				public:
					Point();

					Point(const double& x, const double& y, const double& z);

					//Point(double x, double y, double z);

					Point(const double& x, const double& y);

					//Point(double x, double y);

					// Use L'x' etc.
					double get(wchar_t what);

					//double set(wchar_t what, double value);

					// Use L'x' etc.
					double set(wchar_t what, const double& value);
			};

			class Spin {
				protected:
					double sx;
					double sy;
					double sz;

				public:
					Spin();

					Spin(const double& sx, const double& sy, const double& sz);

					//Spin(double sx, double sy, double sz);

					Spin(const double& sx, const double& sy);

					//Spin(double sx, double sy);

					// Use L"x" etc.
					double get(const std::wstring& what);

					// Use L'x' etc.
					double get(wchar_t what);

					// Use L"sx" etc.
					double set(const std::wstring& what, double& value);

					//double set(const std::wstring& what, double value);
					
					// Use L'x' etc.
					double set(wchar_t what, double& value);

					//double set(wchar_t what, double value);
			};


		};

	};

#endif // !POINT_SPIN_HPP