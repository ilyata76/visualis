#pragma once

#ifndef CREATOR_OF_VERTEX_ARR_HPP
#define CREATOR_OF_VERTEX_ARR_HPP

	#include "./point-spin.hpp"
	#include <string>

	// идея заключается в том, что здесь парсится файл .vvis и создаётся класс vertex, состоящий из Point(x,y,z), Spin(sx,sy,sz)

	namespace vvis {

		// vvis должен создавать Vertex(point, spin) и массив из Vertex в creator для дальнейшей визуализации в visualization
		namespace creator {

			class Vertex {

			};

		}
	};

#endif // !CREATOR_OF_VERTEX_ARR_HPP
