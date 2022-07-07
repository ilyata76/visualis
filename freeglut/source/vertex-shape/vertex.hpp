#pragma once


#ifndef VERTEX_HPP
#define VERTEX_HPP

	#include "./point.hpp"
	#include "./spin.hpp"
	#include "../helpful/useful_functions.hpp"
	#include <fstream>

	class Vertex {
		public:
			Spin spin;
			Point point;
			unsigned int number;
			short int layer;
			short int material;

			Vertex(Point& p, Spin& s, unsigned int number) : point(p), spin(s), number(number), layer(0), material(0) {};
			Vertex(Point& p, Spin& s, unsigned int number, short int layer, short int material) : point(p), spin(s), number(number), layer(layer), material(material) {};
			Vertex(Point& p, Spin& s) : point(p), spin(s), number(0), layer(0), material(0) {};

	};

	// _path_to_file must be valid
	std::vector<Vertex> sconfiguration_parsing(const std::string& _path_to_file);

#endif // !VERTEX_HPP
