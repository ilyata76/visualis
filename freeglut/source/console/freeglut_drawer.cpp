#include "./freeglut_drawer.hpp"

Settings glob_settings;
std::vector<Vertex> glob_vct;

bool axis_by_cones = false;

void draw_sample(Settings& _settings, std::vector<Vertex>& _vct, int argc, char** argv) {

	glob_settings = _settings;
	glob_vct = _vct;
	// ��������� ����� ���������� �� ���� � ���� ������ � ������ ���������� �� ����� � �������������� �� ����� � �������

	glutInit(&argc, argv);

	glutInitWindowSize(glob_settings.main_window.wh.width,
						glob_settings.main_window.wh.height);

	glutInitWindowPosition(0, 0);

	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);

	glob_settings.main_window.descriptor = glutCreateWindow("main_window"); glutSetWindowTitle("VISUALIS");
		glutDisplayFunc(display_mainwindow);
		glutReshapeFunc(reshape_mainwindow);
		glutKeyboardFunc(normal_keys);
		glutSpecialFunc(special_keys);
		main_menu_init();


	// subwindow

	glob_settings.subwindows.push_back(
		Window(0, WindowParameters(glob_settings.main_window.wh.height / 7.0, glob_settings.main_window.wh.height),
			Rgb(glob_settings.main_window.backgroundcolor.red, glob_settings.main_window.backgroundcolor.green, glob_settings.main_window.backgroundcolor.blue))
	);

	glob_settings.subwindows[0].descriptor = glutCreateSubWindow(
		glob_settings.main_window.descriptor, 0, 0, glob_settings.subwindows[0].wh.width, glob_settings.subwindows[0].wh.height
	);

		glutDisplayFunc(display_subwindow_0);
		glutReshapeFunc(reshape_subwindow_0);
		subwindow_0_menu_init();


	// continue

	glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE, GLUT_ACTION_CONTINUE_EXECUTION);
	glutMainLoop();

}

void display_mainwindow() {

	glClearColor(glob_settings.main_window.backgroundcolor.red, glob_settings.main_window.backgroundcolor.green, glob_settings.main_window.backgroundcolor.blue, 0.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	if (glob_settings.freeglut_settings.shape == VVIS_SHAPE_NOTHING || glob_vct.size() == 0) {
		
		glMatrixMode(GL_PROJECTION);
			glLoadIdentity();
			gluOrtho2D(0.0, glob_settings.main_window.wh.width, 0.0, glob_settings.main_window.wh.height);
			glColor3f(0.0, 0.0, 0.0);

		glMatrixMode(GL_MODELVIEW);
			glPushMatrix();
			glColor3f(0.0, 0.0, 0.0);
			glLoadIdentity();
			glRasterPos2i(0.0, glob_settings.main_window.wh.height / 2);
				[](std::string text) {int len = text.length(); for (int i = 0; i < len; ++i) glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, text[i]); }("NOTHING TO DISPLAY");
		glPopMatrix();

		glFlush();
		glutSwapBuffers();
	
	} else {
		
		glMatrixMode(GL_MODELVIEW);
			glLoadIdentity();

			gluLookAt(
				glob_settings.freeglut_settings.position_of_camera.x, glob_settings.freeglut_settings.position_of_camera.y, glob_settings.freeglut_settings.position_of_camera.z,		//
				glob_settings.freeglut_settings.position_of_element.x, glob_settings.freeglut_settings.position_of_element.y, glob_settings.freeglut_settings.position_of_element.z,		//
				0., 1., 0.
			);

		glMatrixMode(GL_PROJECTION);
			glLoadIdentity();
			
			glOrtho(
				-(double(glob_settings.main_window.wh.width) / 2.) * double(glob_settings.freeglut_settings.estrangement), (double(glob_settings.main_window.wh.width) / 2.) * double(glob_settings.freeglut_settings.estrangement),
				-(double(glob_settings.main_window.wh.height) / 2.) * double(glob_settings.freeglut_settings.estrangement), (double(glob_settings.main_window.wh.height) / 2.) * double(glob_settings.freeglut_settings.estrangement),
				1., 1000.
			);
			
		glMatrixMode(GL_MODELVIEW);

		if (glob_settings.global_settings.index_of_spin == VVIS_DRAW_ALL) {
					
			size_t size_of_vector = glob_vct.size();
					
			for (unsigned int i = 0; i < size_of_vector; ++i) {
				draw_shape(i);
			}

		} else {
			draw_shape(glob_settings.global_settings.index_of_spin);
		}


		glFlush();
		glutSwapBuffers();

	}
}

void draw_shape(int index) {
	Shape* shape = NULL; double args_for_draw[4];

	Vertex current_vertex = glob_vct[index];

	switch (glob_settings.freeglut_settings.shape) {

		case VVIS_SHAPE_CONE:
			shape = new Cone(current_vertex);

			args_for_draw[0] = 0.005 * glob_settings.freeglut_settings.scaling_parameters.x;		//
			args_for_draw[1] = 0.05 * glob_settings.freeglut_settings.scaling_parameters.y;		//
			args_for_draw[2] = 10;
			args_for_draw[3] = 10;

			break;
		
		default: 

			shape = new Cone(current_vertex);

			args_for_draw[0] = 0.005 * glob_settings.freeglut_settings.scaling_parameters.x;		//
			args_for_draw[1] = 0.05 * glob_settings.freeglut_settings.scaling_parameters.y;		//
			args_for_draw[2] = 10;
			args_for_draw[3] = 10;

			break;

	}

	glPushMatrix();

	glTranslated(0, 0, glob_settings.freeglut_settings.position_of_element.z);

	glTranslated(glob_settings.freeglut_settings.global_translation.x, glob_settings.freeglut_settings.global_translation.y, glob_settings.freeglut_settings.global_translation.z); 
	glTranslated(-glob_settings.freeglut_settings.position_of_camera.x, -glob_settings.freeglut_settings.position_of_camera.y, -glob_settings.freeglut_settings.position_of_camera.z);


	shape->set_draw_configuration(); 

	glRotated(glob_settings.freeglut_settings.additional_rotation.phi, 0, 1, 0); 
	glRotatef(glob_settings.freeglut_settings.additional_rotation.theta, 1, 0, 0);

	glTranslated(
		current_vertex.point.x * glob_settings.freeglut_settings.scaling_translation.x,
		current_vertex.point.y * glob_settings.freeglut_settings.scaling_translation.y,
		current_vertex.point.z * glob_settings.freeglut_settings.scaling_translation.z);

	Rgb color_config(0, 0, 0);

	if (glob_settings.freeglut_settings.coloring_sample) {
		color_config = get_color_by_direction(current_vertex.spin.x, current_vertex.spin.y, current_vertex.spin.z);
	}

	shape->draw(color_config, args_for_draw);

	glPopMatrix();

	delete shape;

}

void reshape_mainwindow(int w, int h) {
	if (h == 0) h = 1;
	if (w == 0) w = 1;

	glViewport(0, 0, w, h);
	
	glob_settings.main_window.wh.width = w;
	glob_settings.main_window.wh.height= h;

	// reshape subwindows
	glutSetWindow(glob_settings.subwindows[0].descriptor);
		glutReshapeWindow(glob_settings.main_window.wh.height / 7.0, glob_settings.main_window.wh.height);
	
	glutSetWindow(glob_settings.main_window.descriptor);
}

void normal_keys(unsigned char key, int x, int y) {

	double t_b_e = glob_settings.freeglut_settings.translation_by_element;

	switch (key) {
	
		case '�':
		case 'w':	glob_settings.freeglut_settings.position_of_camera.y -= t_b_e * glob_settings.freeglut_settings.camera_changes.y; 
					glob_settings.freeglut_settings.position_of_element.y += t_b_e * glob_settings.freeglut_settings.camera_changes.y;
					postRedisplay();
					break;

		case '�':
		case 's':	glob_settings.freeglut_settings.position_of_camera.y += t_b_e * glob_settings.freeglut_settings.camera_changes.y;
					glob_settings.freeglut_settings.position_of_element.y -= t_b_e * glob_settings.freeglut_settings.camera_changes.y;
					postRedisplay();
					break;

		case '�':
		case 'a':	glob_settings.freeglut_settings.position_of_camera.x += t_b_e * glob_settings.freeglut_settings.camera_changes.x;
					glob_settings.freeglut_settings.position_of_element.x -= t_b_e * glob_settings.freeglut_settings.camera_changes.x;
					postRedisplay();
					break;

		case '�':
		case 'd':	glob_settings.freeglut_settings.position_of_camera.x -= t_b_e * glob_settings.freeglut_settings.camera_changes.x;
					glob_settings.freeglut_settings.position_of_element.x += t_b_e * glob_settings.freeglut_settings.camera_changes.x;
					postRedisplay();
					break;

		case '�':
		case 'i':	glob_settings.freeglut_settings.additional_rotation.theta -= t_b_e * glob_settings.freeglut_settings.camera_changes.y;
					postRedisplay();
					break;

		case '�':
		case 'k':	glob_settings.freeglut_settings.additional_rotation.theta += t_b_e * glob_settings.freeglut_settings.camera_changes.y;
					postRedisplay();
					break;
		
		case '�':
		case 'j':	glob_settings.freeglut_settings.additional_rotation.phi -= t_b_e * glob_settings.freeglut_settings.camera_changes.x;
					postRedisplay();
					break;
		
		case '�':
		case 'l':	glob_settings.freeglut_settings.additional_rotation.phi += t_b_e * glob_settings.freeglut_settings.camera_changes.x;
					postRedisplay();
					break;
		
		case ' ':	glob_settings.freeglut_settings.estrangement += glob_settings.freeglut_settings.estrangement_changes;
					postRedisplay();
					break;
		
		case 27:	glutLeaveMainLoop(); 
					break;

		default: 
					break;
	
	}


}

void special_keys(int key, int x, int y) {
	
	double t_b_e = glob_settings.freeglut_settings.translation_by_element;

	switch (key) {

		case GLUT_KEY_PAGE_UP:		glob_settings.freeglut_settings.scaling_parameters.x += glob_settings.freeglut_settings.scaling_parameters_changes.x;
									glob_settings.freeglut_settings.scaling_parameters.y += glob_settings.freeglut_settings.scaling_parameters_changes.y;
									glob_settings.freeglut_settings.scaling_parameters.z += glob_settings.freeglut_settings.scaling_parameters_changes.z;
									postRedisplay();
									break;

		case GLUT_KEY_PAGE_DOWN:	glob_settings.freeglut_settings.scaling_parameters.x -= glob_settings.freeglut_settings.scaling_parameters_changes.x;
									glob_settings.freeglut_settings.scaling_parameters.y -= glob_settings.freeglut_settings.scaling_parameters_changes.y;
									glob_settings.freeglut_settings.scaling_parameters.z -= glob_settings.freeglut_settings.scaling_parameters_changes.z;
									postRedisplay();
									break;
									
		case GLUT_KEY_LEFT:			glob_settings.freeglut_settings.global_translation.x -= t_b_e * glob_settings.freeglut_settings.translation_changes.x;
									postRedisplay();
									break;									

		case GLUT_KEY_RIGHT:		glob_settings.freeglut_settings.global_translation.x += t_b_e * glob_settings.freeglut_settings.translation_changes.x;
									postRedisplay();
									break;							

		case GLUT_KEY_UP:			glob_settings.freeglut_settings.global_translation.y += t_b_e * glob_settings.freeglut_settings.translation_changes.y;
									postRedisplay();
									break;		

		case GLUT_KEY_DOWN:			glob_settings.freeglut_settings.global_translation.y -= t_b_e * glob_settings.freeglut_settings.translation_changes.y;
									postRedisplay();
									break;

		case GLUT_KEY_CTRL_L:
		case GLUT_KEY_SHIFT_L:		glob_settings.freeglut_settings.estrangement -= glob_settings.freeglut_settings.estrangement_changes;
									postRedisplay();
									break;

		case GLUT_KEY_F11:			if (!glob_settings.freeglut_settings.fullscreen) { glutFullScreen(); glob_settings.freeglut_settings.fullscreen = true; }
									else { glutPositionWindow(0, 0); glob_settings.freeglut_settings.fullscreen = false; };
									break;

		default:					
									break;

	}

}

void main_menu_init() {
	int _main_menu_render = glutCreateMenu(main_menu_render);

	int _menu_movements_by_arrows = glutCreateMenu(menu_movements_by_arrows);
	int _menu_movements_by_wasd = glutCreateMenu(menu_movements_by_wasd);
	int _menu_movements_by_ijkl = glutCreateMenu(menu_movements_by_ijkl);
	int _menu_movements_by_shiftspace = glutCreateMenu(menu_movements_by_shiftspace);
	int _menu_scaling = glutCreateMenu(menu_scaling);
	int _menu_color = glutCreateMenu(menu_color);
	int _menu_settings = glutCreateMenu(menu_settings);

	glutSetMenu(_menu_movements_by_arrows);
		glutAddMenuEntry("Inrease sensivity", MENU_RENDER_MOVEMENTS_BY_ARROWS_INCREASE_SENSIVITY);
		glutAddMenuEntry("Decrease sensivity", MENU_RENDER_MOVEMENTS_BY_ARROWS_DECREASE_SENSIVITY);
		glutAddMenuEntry("Press UP", MENU_RENDER_MOVEMENTS_BY_ARROWS_PRESS_UP);
		glutAddMenuEntry("Press DOWN", MENU_RENDER_MOVEMENTS_BY_ARROWS_PRESS_DOWN);
		glutAddMenuEntry("Press LEFT", MENU_RENDER_MOVEMENTS_BY_ARROWS_PRESS_LEFT);
		glutAddMenuEntry("Press RIGHT", MENU_RENDER_MOVEMENTS_BY_ARROWS_PRESS_RIGHT);

	glutSetMenu(_menu_movements_by_wasd);
		glutAddMenuEntry("Inrease sensivity", MENU_RENDER_MOVEMENTS_BY_WASD_INCREASE_SENSIVITY);
		glutAddMenuEntry("Decrease sensivity", MENU_RENDER_MOVEMENTS_BY_WASD_DECREASE_SENSIVITY);
		glutAddMenuEntry("Press W", MENU_RENDER_MOVEMENTS_BY_WASD_PRESS_W);
		glutAddMenuEntry("Press A", MENU_RENDER_MOVEMENTS_BY_WASD_PRESS_A);
		glutAddMenuEntry("Press S", MENU_RENDER_MOVEMENTS_BY_WASD_PRESS_S);
		glutAddMenuEntry("Press D", MENU_RENDER_MOVEMENTS_BY_WASD_PRESS_D);

	glutSetMenu(_menu_movements_by_ijkl);
		glutAddMenuEntry("Inrease sensivity", MENU_RENDER_MOVEMENTS_BY_IJKL_INCREASE_SENSIVITY);
		glutAddMenuEntry("Decrease sensivity", MENU_RENDER_MOVEMENTS_BY_IJKL_DECREASE_SENSIVITY);
		glutAddMenuEntry("Press I", MENU_RENDER_MOVEMENTS_BY_IJKL_PRESS_I);
		glutAddMenuEntry("Press J", MENU_RENDER_MOVEMENTS_BY_IJKL_PRESS_J);
		glutAddMenuEntry("Press K", MENU_RENDER_MOVEMENTS_BY_IJKL_PRESS_K);
		glutAddMenuEntry("Press L", MENU_RENDER_MOVEMENTS_BY_IJKL_PRESS_L);

	glutSetMenu(_menu_movements_by_shiftspace);
		glutAddMenuEntry("Inrease sensivity", MENU_RENDER_MOVEMENTS_BY_SHIFTSPACE_INCREASE_SENSIVITY);
		glutAddMenuEntry("Decrease sensivity", MENU_RENDER_MOVEMENTS_BY_SHIFTSPACE_DECREASE_SENSIVITY);
		glutAddMenuEntry("Press SHIFT", MENU_RENDER_MOVEMENTS_BY_SHIFTSPACE_PRESS_SHIFT);
		glutAddMenuEntry("Press SPACE", MENU_RENDER_MOVEMENTS_BY_SHIFTSPACE_PRESS_SPACE);

	glutSetMenu(_menu_scaling);
		glutAddMenuEntry("Inrease sensivity", MENU_RENDER_SCALING_INCREASE_SENSIVITY);
		glutAddMenuEntry("Decrease sensivity", MENU_RENDER_SCALING_DECREASE_SENSIVITY);
		glutAddMenuEntry("Press PAGE UP", MENU_RENDER_SCALING_PRESS_PAGE_UP);
		glutAddMenuEntry("Press PAGE DOWN", MENU_RENDER_SCALING_PRESS_PAGE_DOWN);

	glutSetMenu(_menu_color);
		glutAddMenuEntry("ON", MENU_COLOR_OO_ON);
		glutAddMenuEntry("OFF", MENU_COLOR_OO_OFF);

	glutSetMenu(_menu_settings);
		glutAddMenuEntry("SAVE", MENU_SETTINGS_GS_SAVE);
		glutAddMenuEntry("GET", MENU_SETTINGS_GS_GET);
		glutAddMenuEntry("RESET", MENU_SETTINGS_GS_RESET);
		glutAddMenuEntry("RESET FILE", MENU_SETTINGS_GS_RESET_FILE);

	glutSetMenu(_main_menu_render);
		glutAddSubMenu("Movements by arrows", _menu_movements_by_arrows);
		glutAddSubMenu("Movements by wasd", _menu_movements_by_wasd);
		glutAddSubMenu("Movements by ijkl", _menu_movements_by_ijkl);
		glutAddSubMenu("Movements by shift(lctrl)/space", _menu_movements_by_shiftspace);
		glutAddSubMenu("Scaling parameters by pageup/pagedown", _menu_scaling);
		glutAddSubMenu("Coloring", _menu_color);
		glutAddSubMenu("Settings", _menu_settings);
		glutAddMenuEntry("Invert control", MENU_RENDER_INVERT_CONTROL);

	glutAttachMenu(GLUT_RIGHT_BUTTON);
	glutDetachMenu(GLUT_LEFT_BUTTON);

}

void main_menu_render(int code) {
	
	switch (code) {

		case MENU_RENDER_INVERT_CONTROL: glob_settings.freeglut_settings.translation_by_element *= -1; break;

		default:
			break;
	}

}

void menu_movements_by_arrows(int code) {
	
	switch (code) {

		case MENU_RENDER_MOVEMENTS_BY_ARROWS_INCREASE_SENSIVITY: 
			glob_settings.freeglut_settings.translation_changes.x *= MOVEMENTS_BY_ARROWS_MULTIPLY_SENSIVITY;
			glob_settings.freeglut_settings.translation_changes.y *= MOVEMENTS_BY_ARROWS_MULTIPLY_SENSIVITY;
			glob_settings.freeglut_settings.translation_changes.z *= MOVEMENTS_BY_ARROWS_MULTIPLY_SENSIVITY;
			break;

		case MENU_RENDER_MOVEMENTS_BY_ARROWS_DECREASE_SENSIVITY:
			glob_settings.freeglut_settings.translation_changes.x /= MOVEMENTS_BY_ARROWS_MULTIPLY_SENSIVITY;
			glob_settings.freeglut_settings.translation_changes.y /= MOVEMENTS_BY_ARROWS_MULTIPLY_SENSIVITY;
			glob_settings.freeglut_settings.translation_changes.z /= MOVEMENTS_BY_ARROWS_MULTIPLY_SENSIVITY;
			break;

		case MENU_RENDER_MOVEMENTS_BY_ARROWS_PRESS_UP: 
			special_keys(GLUT_KEY_UP, 0, 0);
			break;

		case MENU_RENDER_MOVEMENTS_BY_ARROWS_PRESS_DOWN: 
			special_keys(GLUT_KEY_DOWN, 0, 0);
			break;

		case MENU_RENDER_MOVEMENTS_BY_ARROWS_PRESS_LEFT: 
			special_keys(GLUT_KEY_LEFT, 0, 0);
			break;

		case MENU_RENDER_MOVEMENTS_BY_ARROWS_PRESS_RIGHT: 
			special_keys(GLUT_KEY_RIGHT, 0, 0);
			break;

		default:
			break;
	}

}

void menu_movements_by_wasd(int code) {

	switch (code) {

		case MENU_RENDER_MOVEMENTS_BY_WASD_INCREASE_SENSIVITY: 
			glob_settings.freeglut_settings.camera_changes.x *= MOVEMENTS_BY_WASD_MULTIPLY_SENSIVITY;
			glob_settings.freeglut_settings.camera_changes.y *= MOVEMENTS_BY_WASD_MULTIPLY_SENSIVITY;
			glob_settings.freeglut_settings.camera_changes.z *= MOVEMENTS_BY_WASD_MULTIPLY_SENSIVITY;
			break;

		case MENU_RENDER_MOVEMENTS_BY_WASD_DECREASE_SENSIVITY: 
			glob_settings.freeglut_settings.camera_changes.x /= MOVEMENTS_BY_WASD_MULTIPLY_SENSIVITY;
			glob_settings.freeglut_settings.camera_changes.y /= MOVEMENTS_BY_WASD_MULTIPLY_SENSIVITY;
			glob_settings.freeglut_settings.camera_changes.z /= MOVEMENTS_BY_WASD_MULTIPLY_SENSIVITY;
			break;

		case MENU_RENDER_MOVEMENTS_BY_WASD_PRESS_W:
			normal_keys('w', 0, 0);
			break;

		case MENU_RENDER_MOVEMENTS_BY_WASD_PRESS_A:
			normal_keys('a', 0, 0);
			break;

		case MENU_RENDER_MOVEMENTS_BY_WASD_PRESS_S:
			normal_keys('s', 0, 0);
			break;

		case MENU_RENDER_MOVEMENTS_BY_WASD_PRESS_D:
			normal_keys('d', 0, 0);
			break;

		default:
			break;

	}
}

void menu_movements_by_ijkl(int code) {

	switch (code) {

		case MENU_RENDER_MOVEMENTS_BY_IJKL_INCREASE_SENSIVITY: 
			glob_settings.freeglut_settings.camera_changes.x *= MOVEMENTS_BY_WASD_MULTIPLY_SENSIVITY;
			glob_settings.freeglut_settings.camera_changes.y *= MOVEMENTS_BY_WASD_MULTIPLY_SENSIVITY;
			glob_settings.freeglut_settings.camera_changes.z *= MOVEMENTS_BY_WASD_MULTIPLY_SENSIVITY;
			break;

		case MENU_RENDER_MOVEMENTS_BY_IJKL_DECREASE_SENSIVITY: 
			glob_settings.freeglut_settings.camera_changes.x /= MOVEMENTS_BY_WASD_MULTIPLY_SENSIVITY;
			glob_settings.freeglut_settings.camera_changes.y /= MOVEMENTS_BY_WASD_MULTIPLY_SENSIVITY;
			glob_settings.freeglut_settings.camera_changes.z /= MOVEMENTS_BY_WASD_MULTIPLY_SENSIVITY;
			break;

		case MENU_RENDER_MOVEMENTS_BY_IJKL_PRESS_I: 
			normal_keys('i', 0, 0);
			break;

		case MENU_RENDER_MOVEMENTS_BY_IJKL_PRESS_J: 
			normal_keys('j', 0, 0);
			break;

		case MENU_RENDER_MOVEMENTS_BY_IJKL_PRESS_K: 
			normal_keys('k', 0, 0);
			break;

		case MENU_RENDER_MOVEMENTS_BY_IJKL_PRESS_L: 
			normal_keys('l', 0, 0);
			break;


		default:
			break;

	}

}

void menu_movements_by_shiftspace(int code) {

	switch (code) {

		case MENU_RENDER_MOVEMENTS_BY_SHIFTSPACE_INCREASE_SENSIVITY: 
			glob_settings.freeglut_settings.estrangement_changes *= MOVEMENTS_BY_SHIFTSPACE_MULTIPLY_SENSIVITY;
			break;

		case MENU_RENDER_MOVEMENTS_BY_SHIFTSPACE_DECREASE_SENSIVITY: 
			glob_settings.freeglut_settings.estrangement_changes /= MOVEMENTS_BY_SHIFTSPACE_MULTIPLY_SENSIVITY;
			break;

		case MENU_RENDER_MOVEMENTS_BY_SHIFTSPACE_PRESS_SHIFT: 
			special_keys(GLUT_KEY_SHIFT_L, 0, 0);
			break;

		case MENU_RENDER_MOVEMENTS_BY_SHIFTSPACE_PRESS_SPACE: 
			normal_keys(' ', 0, 0);
			break;

		default:
			break;

	}

}

void menu_scaling(int code) {

	switch (code) {

		case MENU_RENDER_SCALING_INCREASE_SENSIVITY:
			glob_settings.freeglut_settings.scaling_parameters_changes.x *= SCALING_MULTIPLY_SENSIVITY_X;
			glob_settings.freeglut_settings.scaling_parameters_changes.y *= SCALING_MULTIPLY_SENSIVITY_Y;
			glob_settings.freeglut_settings.scaling_parameters_changes.z *= SCALING_MULTIPLY_SENSIVITY_Z;
			break;

		case MENU_RENDER_SCALING_DECREASE_SENSIVITY:
			glob_settings.freeglut_settings.scaling_parameters_changes.x /= SCALING_MULTIPLY_SENSIVITY_X;
			glob_settings.freeglut_settings.scaling_parameters_changes.y /= SCALING_MULTIPLY_SENSIVITY_Y;
			glob_settings.freeglut_settings.scaling_parameters_changes.z /= SCALING_MULTIPLY_SENSIVITY_Z;
			break;

		case MENU_RENDER_SCALING_PRESS_PAGE_UP: 
			special_keys(GLUT_KEY_PAGE_UP, 0, 0);
			break;
			

		case MENU_RENDER_SCALING_PRESS_PAGE_DOWN: 
			special_keys(GLUT_KEY_PAGE_DOWN, 0, 0);
			break;

		default:
			break;

	}

}

void menu_color(int code) {

	switch (code) {

		case MENU_COLOR_OO_OFF:
			glob_settings.freeglut_settings.coloring_sample = false;
			postRedisplay();
			break;

		case MENU_COLOR_OO_ON:
			glob_settings.freeglut_settings.coloring_sample = true;
			postRedisplay();
			break;

		default:
			break;
	}

}

void menu_settings(int code) {

	switch (code) {

		case MENU_SETTINGS_GS_SAVE:
			glob_settings.save(L'a');
			break;

		case MENU_SETTINGS_GS_GET: {
				int width = glob_settings.main_window.wh.width, height = glob_settings.main_window.wh.height;
				glob_settings.get(L'f');
				glob_settings.main_window.wh.width = width; glob_settings.main_window.wh.height = height;
				postRedisplay();
			} break;

		case MENU_SETTINGS_GS_RESET:	
			glob_settings = Settings(glob_settings.global_settings, Freeglut_settings());
			break;

		case MENU_SETTINGS_GS_RESET_FILE: {
			Settings reseted_settings = Settings(glob_settings.global_settings, Freeglut_settings());
			reseted_settings.save(L'a');
			} break;
	}

}

void display_subwindow_0() {
	
	//glClearColor(glob_settings.main_window.backgroundcolor.red, glob_settings.main_window.backgroundcolor.green, glob_settings.main_window.backgroundcolor.blue, 1.0);
	glClearColor(230.0/255.0, 230.0/255.0, 230.0/255.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


	glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();

		gluLookAt(
			glob_settings.freeglut_settings.position_of_camera.x, glob_settings.freeglut_settings.position_of_camera.y, glob_settings.freeglut_settings.position_of_camera.z,		//
			glob_settings.freeglut_settings.position_of_element.x, glob_settings.freeglut_settings.position_of_element.y, glob_settings.freeglut_settings.position_of_element.z,		//
			0., 1., 0.
		);

	glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		double estrangement = 0.7;

		glOrtho(
			-(double(glob_settings.subwindows[0].wh.width) / 2.) * estrangement, (double(glob_settings.subwindows[0].wh.width) / 2.) * estrangement,
			-(double(glob_settings.subwindows[0].wh.height) / 2.) * estrangement, (double(glob_settings.subwindows[0].wh.height) / 2.) * estrangement,
			0.1, 10000.
		);

	glMatrixMode(GL_MODELVIEW);

	glPushMatrix();

	glTranslated(glob_settings.freeglut_settings.position_of_element.x, glob_settings.freeglut_settings.position_of_element.y, glob_settings.freeglut_settings.position_of_element.z);
	glRotated(glob_settings.freeglut_settings.additional_rotation.phi, 0, 1, 0);
	glRotatef(glob_settings.freeglut_settings.additional_rotation.theta, 1, 0, 0);
	
	if (axis_by_cones) {

		glColor3f(1.0, 0.0, 0.0);
		estrangement = glob_settings.subwindows[0].wh.width / 50.0;
		glRotated(90.0, 0, 1, 0);
			glutSolidCylinder(3.0 * estrangement, 6.0 * estrangement, 10.0, 10.0);
			glTranslated(0.0, 0.0, 6.0 * estrangement);
			glutSolidCone(3.0 * estrangement, 17.0 * estrangement, 10.0, 10.0);
			glTranslated(0.0, 0.0, -5.0 * estrangement);
		glRotated(-90.0, 0, 1, 0);

		glColor3f(0.0, 1.0, 0.0);

		glRotated(-90.0, 1, 0, 0);
			glutSolidCylinder(3.0 * estrangement, 6.0 * estrangement, 10.0, 10.0);
			glTranslated(0.0, 0.0, 6.0 * estrangement);
			glutSolidCone(3.0 * estrangement, 17.0 * estrangement, 10.0, 10.0);
			glTranslated(0.0, 0.0, -5.0 * estrangement);
		glRotated(90.0, 1, 0, 0);

		glColor3f(0.0, 0.0, 1.0);
			glutSolidCylinder(3.0 * estrangement, 6.0 * estrangement, 10.0, 10.0);
			glTranslated(0.0, 0.0, 6.0 * estrangement);
			glutSolidCone(3.0 * estrangement, 17.0 * estrangement, 10.0, 10.0);
			glTranslated(0.0, 0.0, -5.0 * estrangement);
		glPopMatrix();

	} else {

		glLineWidth(4);

		glColor3f(1.0, 0.0, 0.0);

		glBegin(GL_LINES);
			glVertex3f(0.0, 0.0, 0.0);
			glVertex3f(50.0, 0.0, 0.0);
		glEnd();	
	
	
		glColor3f(0.0, 1.0, 0.0);

		glBegin(GL_LINES);
			glVertex3f(0.0, 0.0, 0.0);
			glVertex3f(0.0, 50.0, 0.0);
		glEnd();
	
		glColor3f(0.0, 0.0, 1.0);

		glBegin(GL_LINES);
			glVertex3f(0.0, 0.0, 0.0);
			glVertex3f(0.0, 0.0, 50.0);
		glEnd();
	}

	glutSwapBuffers();

}

void display_subwindow_1()
{
}

void reshape_subwindow_0(int w, int h) {

	if (h == 0) h = 1;
	if (w == 0) w = 1;

	glViewport(0, 0, w, h);
	
	glob_settings.subwindows[0].wh.width = w;
	glob_settings.subwindows[0].wh.height = h;

}

void subwindow_0_menu_init() {
	int _subwindow0_menu = glutCreateMenu(subwindow_0_menu);
	
	glutSetMenu(_subwindow0_menu);
		glutAddMenuEntry("Use lines", SUBWINDOW0_MENU_USE_LINES);
		glutAddMenuEntry("Use cones", SUBWINDOW0_MENU_USE_CONES);
	
	glutAttachMenu(GLUT_RIGHT_BUTTON);
	glutDetachMenu(GLUT_LEFT_BUTTON);
}

void subwindow_0_menu(int code) {
	
	switch (code) {
		case SUBWINDOW0_MENU_USE_CONES: axis_by_cones = true; glutPostRedisplay();break;
		case SUBWINDOW0_MENU_USE_LINES: axis_by_cones = false; glutPostRedisplay(); break;
		default: break;
	}

}

void postRedisplay() {
	glutSetWindow(glob_settings.main_window.descriptor);
		glutPostRedisplay();
	
	for (const auto& x : glob_settings.subwindows) {
		glutSetWindow(x.descriptor);
			glutPostRedisplay();
	}

	glutSetWindow(glob_settings.main_window.descriptor);
}