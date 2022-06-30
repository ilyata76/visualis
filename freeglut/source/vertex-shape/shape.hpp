#pragma once


#ifndef SHAPE_HPP
#define SHAPE_HPP

	#include "../libraries/freeglut/include/GL/freeglut.h"
	#include "./vertex.hpp"
	#include "../color/RGB.hpp"

	class Shape {
		public:
			Vertex vrt;

			Shape(Vertex& _vrt) : vrt(_vrt) {};

			virtual bool set_draw_configuration() = 0;
			virtual bool draw(Rgb color, double* argc) = 0;
			virtual wchar_t info() = 0;
	};

	class Cone : public Shape {
		public:
			double euler_phi;
			double euler_theta;

			Cone(Vertex& _vrt) : Shape(_vrt), euler_phi(0.0), euler_theta(0.0) {};
			
			bool set_draw_configuration();
			
			// 4 args
			bool draw(Rgb color, double* args);
			wchar_t info();
	};


	class Sphere : public Shape {
		public:
			Sphere(Vertex& _vrt) : Shape(_vrt) {};
			
			bool set_draw_configuration();

			// 3 args
			bool draw(Rgb color, double* args);
			wchar_t info();

	};


#endif // !SHAPE_HPP
