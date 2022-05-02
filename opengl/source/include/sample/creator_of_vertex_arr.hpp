#pragma once

#ifndef CREATOR_OF_VERTEX_ARR_HPP
#define CREATOR_OF_VERTEX_ARR_HPP

	#include "./point-spin.hpp"
	#include <string>
	#include <fstream>
	#include <vector>
	#include <sstream>

	// идея заключается в том, что здесь парсится файл .vvis и создаётся класс vertex, состоящий из Point(x,y,z), Spin(sx,sy,sz)

	namespace vvis {

		// vvis должен создавать Vertex(point, spin) и массив из Vertex в creator для дальнейшей визуализации в visualization
		namespace creator {

			class Vertex {
				protected:
					Point point;
					Spin spin;
					unsigned int number;
					short int layer;
					short int material;
				public:
					//Vertex();
					//Vertex(Point& p, Spin& s, unsigned int number); 
					//Vertex(Point& p, Spin& s, unsigned int number, short int layer, short int material); 
					//Vertex(Point& p, Spin& s);

					Vertex(Point& p, Spin& s, unsigned int number) : point(p), spin(s), number(number), layer(INT_PLUG_VVIS), material(INT_PLUG_VVIS) {};
					Vertex(Point& p, Spin& s, unsigned int number, short int layer, short int material) : point(p), spin(s), number(number), layer(layer), material(material) {};
					Vertex(Point& p, Spin& s) : point(p), spin(s), number(INT_PLUG_VVIS), layer(INT_PLUG_VVIS), material(INT_PLUG_VVIS) {};

					Point get_point();
					Spin get_spin();
					unsigned int get_number();
					short int get_layer();
					short int get_material();
					
					// setters не нужны?

					~Vertex() {};
 			};

			using FUNCTION_VERTEX_CONSTINT = std::vector<Vertex>(*)(const int& index);
			std::vector <Vertex> get_out(const int& index);
			FUNCTION_VERTEX_CONSTINT create_arry(const std::wstring& p_t_folder); // парсит файл и создаёт вертекс

			std::wstring get_file_name(const int& index);

		}
	};

#endif // !CREATOR_OF_VERTEX_ARR_HPP
