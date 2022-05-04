#ifndef DRAWING_SHAPE_OPENGL_HPP
#define DRAWING_SHAPE_OPENGL_HPP


	#include <vector>
	#include "creator_of_vertex_arr.hpp"
	#include "../../libraries/freeglut/include/GL/glut.h"
	#include "./shape.hpp"

	namespace vvis {
		namespace visualization {

			void display_nothing();

			void draw_cone_spin(int& index, bool color);
			void display_cone();
			
			// if index = DRAW_ALL (-1) draw all of vector
			void main_glut(int argc, char** argv, std::vector <vvis::creator::Vertex>& vect, wchar_t shape, bool color, int index);

		}
	}


#endif // !DRAWING_SHAPE_OPENGL_HPP