#pragma once

#ifndef SHAPE_HPP
#define SHAPE_HPP

	#include "./creator_of_vertex_arr.hpp"
	#include "./color_class.hpp"
	#include "../../libraries/freeglut/include/GL/glut.h"

	namespace vvis {
		namespace visualization {

			using creator::Vertex;
			// Vertex ����� �������� �� Spin, ���� �� ��������� ���� �� ������, ����������� � ��.
			class Shape {
				protected:
					Vertex vrt;
				public:
					Shape(Vertex& x) : vrt(x) {};

					virtual bool set_draw_configuration() = 0;

					virtual wchar_t info_wchar() = 0;
					virtual std::wstring info_wstr() = 0;
			};

			class Cone : public Shape {
				protected:
					float euler_phi;    // around Y axis 
					float euler_theta;	// X axis
				public:
					Cone(Vertex& x) : Shape(x), euler_phi(0.0), euler_theta(0.0) {};

					bool set_draw_configuration();	// �� ��������� this->vertex �������� ������������
					
					bool draw(double base, double height, GLint slices, GLint stacks, vvis::visualization::VvisColor_3f color);  // ������

					wchar_t info_wchar();
					std::wstring info_wstr();
			};
		}
	}

#endif // !SHAPE_HPP
