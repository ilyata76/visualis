#ifndef DRAWING_SHAPE_OPENGL_HPP
#define DRAWING_SHAPE_OPENGL_HPP


	#include <vector>

	#include "creator_of_vertex_arr.hpp"
	#include "../../libraries/freeglut/include/GL/freeglut.h"
	#include "../../libraries/json/single_include/nlohmann/json.hpp"
	#include "./shape.hpp"

	#define MENU_RENDER_MOVEMENTS_BY_ARROWS 1010

	#define MENU_RENDER_MOVEMENTS_BY_ARROWS_SHOW_SENSIVITY 1011
	#define MENU_RENDER_MOVEMENTS_BY_ARROWS_INCREASE_SENSIVITY 1012
	#define MENU_RENDER_MOVEMENTS_BY_ARROWS_DECREASE_SENSIVITY 1013

	#define MENU_RENDER_MOVEMENTS_BY_WASD 1020

	#define MENU_RENDER_MOVEMENTS_BY_WASD_SHOW_SENSIVITY 1021
	#define MENU_RENDER_MOVEMENTS_BY_WASD_INCREASE_SENSIVITY 1022
	#define MENU_RENDER_MOVEMENTS_BY_WASD_DECREASE_SENSIVITY 1023

	#define MENU_RENDER_MOVEMENTS_BY_IJKL 1030

	#define MENU_RENDER_MOVEMENTS_BY_SHIFTSPACE 1040

	#define MENU_RENDER_MOVEMENTS_BY_SHIFTSPACE_SHOW_SENSIVITY 1041
	#define MENU_RENDER_MOVEMENTS_BY_SHIFTSPACE_INCREASE_SENSIVITY 1042
	#define MENU_RENDER_MOVEMENTS_BY_SHIFTSPACE_DECREASE_SENSIVITY 1043

	#define MENU_RENDER_SCALING 1050

	#define MENU_RENDER_SCALING_SHOW_SENSIVITY 1051
	#define MENU_RENDER_SCALING_INCREASE_SENSIVITY 1052
	#define MENU_RENDER_SCALING_DECREASE_SENSIVITY 1053

	#define MENU_COLOR_OO 1060

	#define MENU_COLOR_OO_ON 1061
	#define MENU_COLOR_OO_OFF 1062

	#define MENU_SETTINGS_GS 1070

	#define MENU_SETTINGS_GS_SAVE 1071
	#define MENU_SETTINGS_GS_GET 1072
	#define MENU_SETTINGS_GS_RESET 1073
	#define MENU_SETTINGS_GS_RESET_FILE 1074
	#define MENU_SETTINGS_GS_SHOW 1075

	using nlohmann::json;

	inline bool file_exist(const std::wstring& s) {
		struct _stat buf;
		return (_wstat(s.c_str(), &buf) != -1);
	}

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

					std::wstring path_to_folder;
					std::wstring path_to_settings_file;

					app_freeglut();
					app_freeglut(std::vector <vvis::creator::Vertex>& vect_of_vertexes, wchar_t shape, bool use_color, vvis::visualization::VvisColor_3f background, int index_of_line, std::wstring& path_to_folder, std::wstring& _path_to_settings_file);

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
			void menu_settings(int code);

			void n_keys(unsigned char key, int x, int y);
			void s_keys(int key, int x, int y);

		}
	}


#endif // !DRAWING_SHAPE_OPENGL_HPP