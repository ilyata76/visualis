#ifndef DRAWING_SHAPE_OPENGL_HPP
#define DRAWING_SHAPE_OPENGL_HPP


	#include <vector>
	#include "creator_of_vertex_arr.hpp"
	#include "../../libraries/freeglut/include/GL/freeglut.h"
	#include "./shape.hpp"

	namespace vvis {
		namespace visualization {

			struct vec3 {
				double x;
				double y;
				double z;

				vec3() : x(0), y(0), z(0) {};
				vec3(double x, double y, double z) : x(x), y(y), z(z) {};
			};

			struct app_freeglut {

					int index_of_line;

					double additional_rotation_phi;
					double additional_rotation_theta;
				
					std::vector <vvis::creator::Vertex> vect_of_vertexes;

					double estrangement;

					vec3 global_translation;
					vec3 scaling_parameters;
					vec3 scaling_translation;
					vec3 position_of_camera;
					vec3 position_of_element;


					// то, что сможет изменить пользователь? определяется изначально в defines

					//vec3 scaling_translation_changes_up;
					//vec3 scaling_translation_changes_down;

					vec3 scaling_parameters_changes;

					vec3 translation_changes;

					double translation_by_element;

					vec3 camera_changes; // +-

					double estrangement_changes;

					bool use_color;
					bool fullscreen;
					wchar_t shape;

					int width_of_window;
					int height_of_window;

					vvis::visualization::VvisColor_3f background;

					app_freeglut();
					app_freeglut(std::vector <vvis::creator::Vertex>& vect_of_vertexes, wchar_t shape, bool use_color, vvis::visualization::VvisColor_3f background, int index_of_line);

			};

			void draw_sample(app_freeglut& app, int argc, char** argv);

			void display_render();
			void reshape_render(int w, int h);
			void draw_shape(int index);

			void main_menu_init();
			void main_menu_render(int code);
			void menu_movements_by_arrows(int code);
			void menu_movements_by_wasd(int code);
			void menu_movements_by_ijkl(int code);
			void menu_movements_by_shiftspace(int code);
			void menu_scaling(int code);
			void menu_color(int code);

			void n_keys(unsigned char key, int x, int y);
			void s_keys(int key, int x, int y);

		}
	}


#endif // !DRAWING_SHAPE_OPENGL_HPP