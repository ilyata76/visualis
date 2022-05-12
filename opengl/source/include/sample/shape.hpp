#pragma once

#ifndef SHAPE_HPP
#define SHAPE_HPP

	#include "./creator_of_vertex_arr.hpp"
	#include "./color_class.hpp"
	#include "../../libraries/freeglut/include/GL/glut.h"	
	#include <math.h>

	namespace vvis {
		namespace visualization {

			//using creator::Vertex;
			// Vertex можно заменить на Spin, если не развивать идею со слоями, материалами и пр.
			class Shape {
				protected:
					creator::Vertex vrt;
				public:
					Shape(creator::Vertex& x) : vrt(x) {};

					virtual bool set_draw_configuration() = 0;

					virtual bool new_draw(vvis::visualization::VvisColor_3f color, double* args) = 0;

					virtual wchar_t info_wchar() = 0;
					virtual std::wstring info_wstr() = 0;
			};

			class Cone : public Shape {
				protected:
					float euler_phi;    // around Y axis 
					float euler_theta;	// X axis
				public:
					Cone(creator::Vertex& x) : Shape(x), euler_phi(0.0), euler_theta(0.0) {};

					bool set_draw_configuration();	// на основании this->vertex построит конфигурацию
					
					bool draw(double base, double height, GLint slices, GLint stacks, vvis::visualization::VvisColor_3f color);  // рисует
					
					
					bool new_draw(vvis::visualization::VvisColor_3f color, double* args);  // рисует

					wchar_t info_wchar();
					std::wstring info_wstr();
			};


		}
	}

#endif // !SHAPE_HPP
