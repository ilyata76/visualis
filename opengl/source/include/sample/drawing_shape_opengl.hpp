#ifndef DRAWING_SHAPE_OPENGL_HPP
#define DRAWING_SHAPE_OPENGL_HPP


	#include <vector>
	#include "creator_of_vertex_arr.hpp"
	#include "../../libraries/freeglut/include/GL/freeglut.h"
	#include "./shape.hpp"

	namespace vvis {
		namespace visualization {

			void display_nothing();
			void display_l();

			void draw_cone_spin(int& index, bool color);
			void display_cone();
			
			void normal_keys(unsigned char key, int x, int y);
			void special_keys(int key, int x, int y);
			
			// if index = DRAW_ALL (-1) draw all of vector
			void main_glut(int argc, char** argv, std::vector <vvis::creator::Vertex>& vect, wchar_t shape, bool color, int index);

			void myReshape(int w, int h);

		}
	}


#endif // !DRAWING_SHAPE_OPENGL_HPP