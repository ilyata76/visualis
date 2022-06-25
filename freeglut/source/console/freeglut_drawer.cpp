#include "./freeglut_drawer.hpp"

Settings glob_settings;
std::vector<Vertex> glob_vct;

void draw_sample(Settings& _settings, std::vector<Vertex>& _vct, int argc, char** argv) {

	glob_settings = _settings;
	glob_vct = _vct;

	glutInit(&argc, argv);

	glutInitWindowSize(glob_settings.freeglut_settings.main_window.height,
						glob_settings.freeglut_settings.main_window.width);

	glutInitWindowPosition(0, 0);

	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);

	int MAINWINDOW = glutCreateWindow("main_window"); glutSetWindowTitle("VISUALIS");

		glutDisplayFunc(display_mainwindow);
		glutReshapeFunc(reshape_mainwindow);
		glutKeyboardFunc(normal_keys);
		glutSpecialFunc(special_keys);
	
	glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE, GLUT_ACTION_CONTINUE_EXECUTION);
	glutMainLoop();

}

void display_mainwindow() {

	glClearColor(glob_settings.freeglut_settings.backgroundcolor.red, glob_settings.freeglut_settings.backgroundcolor.green, glob_settings.freeglut_settings.backgroundcolor.blue, 0.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	if (glob_settings.freeglut_settings.shape == VVIS_SHAPE_NOTHING || glob_vct.size() == 0) {
		
		glMatrixMode(GL_PROJECTION);
			glLoadIdentity();
			gluOrtho2D(0.0, glob_settings.freeglut_settings.main_window.width, 0.0, glob_settings.freeglut_settings.main_window.height);
			glColor3f(0.0, 0.0, 0.0);

		glMatrixMode(GL_MODELVIEW);
			glPushMatrix();
			glColor3f(0.0, 0.0, 0.0);
			glLoadIdentity();
			glRasterPos2i(0.0, glob_settings.freeglut_settings.main_window.height / 2);
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
				-(double(glob_settings.freeglut_settings.main_window.width) / 2.) * double(glob_settings.freeglut_settings.estrangement), (double(glob_settings.freeglut_settings.main_window.width) / 2.) * double(glob_settings.freeglut_settings.estrangement),
				-(double(glob_settings.freeglut_settings.main_window.height) / 2.) * double(glob_settings.freeglut_settings.estrangement), (double(glob_settings.freeglut_settings.main_window.height) / 2.) * double(glob_settings.freeglut_settings.estrangement),
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

	glob_settings.freeglut_settings.main_window.width = w;
	glob_settings.freeglut_settings.main_window.height= h;
}

void normal_keys(unsigned char key, int x, int y) {

	double t_b_e = glob_settings.freeglut_settings.translation_by_element;

	switch (key) {
	
		case 'ö':
		case 'w':	glob_settings.freeglut_settings.position_of_camera.y -= t_b_e * glob_settings.freeglut_settings.camera_changes.y; 
					glob_settings.freeglut_settings.position_of_element.y += t_b_e * glob_settings.freeglut_settings.camera_changes.y;
					glutPostRedisplay();
					break;

		case 'û':
		case 's':	glob_settings.freeglut_settings.position_of_camera.y += t_b_e * glob_settings.freeglut_settings.camera_changes.y;
					glob_settings.freeglut_settings.position_of_element.y -= t_b_e * glob_settings.freeglut_settings.camera_changes.y;
					glutPostRedisplay();
					break;

		case 'ô':
		case 'a':	glob_settings.freeglut_settings.position_of_camera.x += t_b_e * glob_settings.freeglut_settings.camera_changes.x;
					glob_settings.freeglut_settings.position_of_element.x -= t_b_e * glob_settings.freeglut_settings.camera_changes.x;
					glutPostRedisplay();
					break;

		case 'â':
		case 'd':	glob_settings.freeglut_settings.position_of_camera.x -= t_b_e * glob_settings.freeglut_settings.camera_changes.x;
					glob_settings.freeglut_settings.position_of_element.x += t_b_e * glob_settings.freeglut_settings.camera_changes.x;
					glutPostRedisplay();
					break;

		case 'ø':
		case 'i':	glob_settings.freeglut_settings.additional_rotation.theta -= t_b_e * glob_settings.freeglut_settings.camera_changes.y;
					glutPostRedisplay();
					break;

		case 'ë':
		case 'k':	glob_settings.freeglut_settings.additional_rotation.theta += t_b_e * glob_settings.freeglut_settings.camera_changes.y;
					glutPostRedisplay();
					break;
		
		case 'î':
		case 'j':	glob_settings.freeglut_settings.additional_rotation.phi -= t_b_e * glob_settings.freeglut_settings.camera_changes.x;
					glutPostRedisplay();
					break;
		
		case 'ä':
		case 'l':	glob_settings.freeglut_settings.additional_rotation.phi += t_b_e * glob_settings.freeglut_settings.camera_changes.x;
					glutPostRedisplay();
					break;
		
		case ' ':	glob_settings.freeglut_settings.estrangement += glob_settings.freeglut_settings.estrangement_changes;
					glutPostRedisplay();
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
									glutPostRedisplay();
									break;

		case GLUT_KEY_PAGE_DOWN:	glob_settings.freeglut_settings.scaling_parameters.x -= glob_settings.freeglut_settings.scaling_parameters_changes.x;
									glob_settings.freeglut_settings.scaling_parameters.y -= glob_settings.freeglut_settings.scaling_parameters_changes.y;
									glob_settings.freeglut_settings.scaling_parameters.z -= glob_settings.freeglut_settings.scaling_parameters_changes.z;
									glutPostRedisplay();
									break;
									
		case GLUT_KEY_LEFT:			glob_settings.freeglut_settings.global_translation.x -= t_b_e * glob_settings.freeglut_settings.translation_changes.x;
									glutPostRedisplay();
									break;									

		case GLUT_KEY_RIGHT:		glob_settings.freeglut_settings.global_translation.x += t_b_e * glob_settings.freeglut_settings.translation_changes.x;
									glutPostRedisplay();
									break;							

		case GLUT_KEY_UP:			glob_settings.freeglut_settings.global_translation.y += t_b_e * glob_settings.freeglut_settings.translation_changes.y;
									glutPostRedisplay();
									break;		

		case GLUT_KEY_DOWN:			glob_settings.freeglut_settings.global_translation.y -= t_b_e * glob_settings.freeglut_settings.translation_changes.y;
									glutPostRedisplay();
									break;

		case GLUT_KEY_CTRL_L:
		case GLUT_KEY_SHIFT_L:		glob_settings.freeglut_settings.estrangement -= glob_settings.freeglut_settings.estrangement_changes;
									glutPostRedisplay();
									break;

		case GLUT_KEY_F11:			if (!glob_settings.freeglut_settings.fullscreen) { glutFullScreen(); glob_settings.freeglut_settings.fullscreen = true; }
									else { glutPositionWindow(0, 0); glob_settings.freeglut_settings.fullscreen = false; };
									break;

		default:					
									break;

	}

}
