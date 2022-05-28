#include "./include/sample/drawing_shape_opengl.hpp"

// TODO: возможность настройки т.е. кнопкой вызываем консоль туда вбиваем что-нибудь и оно меняет параметры
// TODO: флаг use_ortho

// TODO: перемещение камеры по плоскостям образца

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



vvis::visualization::app_freeglut::app_freeglut() {
	this->index_of_line = 0;
	this->additional_rotation_phi = 0.0;
	this->additional_rotation_theta = 0.0;

	this->estrangement = 1.0;

	this->use_color = false;
	this->shape = SHAPE_NOTHING;
	this->fullscreen = false;

	this->height_of_window = 0;
	this->width_of_window = 0;

	this->global_translation = vec3(0., 0., 0.);
	this->scaling_parameters = vec3(1., 1., 1.);
	this->scaling_translation = vec3(1., 1., 1.);
	this->position_of_camera = vec3(0., 0., 0.);
	this->position_of_element = vec3(0., 0., -100.);

	this->scaling_parameters_changes = vec3(SCALING_PARAMETERS_CHANGES_X, SCALING_PARAMETERS_CHANGES_Y, SCALING_PARAMETERS_CHANGES_Z);
	//this->scaling_translation_changes_up = vec3(SCALING_PARAMETERS_CHANGES_UP_X, SCALING_PARAMETERS_CHANGES_UP_Y, SCALING_PARAMETERS_CHANGES_UP_Z);
	//this->scaling_translation_changes_down = vec3(SCALING_PARAMETERS_CHANGES_DOWN_X, SCALING_PARAMETERS_CHANGES_DOWN_Y, SCALING_PARAMETERS_CHANGES_DOWN_Z);

	this->translation_changes = vec3(TRANSLATION_CHANGES_X, TRANSLATION_CHANGES_Y, TRANSLATION_CHANGES_Z);

	this->translation_by_element = ELEMENT_TRANSLATION;

	this->camera_changes = vec3(CAMERA_CHANGES_X, CAMERA_CHANGES_Y, CAMERA_CHANGES_Z);

	this->estrangement_changes = ESTRAGNEMENT_CHANGES;

}

vvis::visualization::app_freeglut::app_freeglut(std::vector<vvis::creator::Vertex>& vect_of_vertexes, wchar_t shape, bool use_color, int index_of_line) {
	this->index_of_line = index_of_line;
	this->additional_rotation_phi = 0.0;
	this->additional_rotation_theta = 0.0;

	this->estrangement = 1.0;

	this->use_color = use_color;
	this->shape = shape;
	this->fullscreen = false;

	this->height_of_window = 0;
	this->width_of_window = 0;

	this->global_translation = vec3(0., 0., 0.);
	this->scaling_parameters = vec3(20., 20., 20.);
	this->scaling_translation = vec3(1., 1., 1.);
	this->position_of_camera = vec3(0., 0., 0.);
	this->position_of_element = vec3(0., 0., -100.);

	this->scaling_parameters_changes = vec3(SCALING_PARAMETERS_CHANGES_X, SCALING_PARAMETERS_CHANGES_Y, SCALING_PARAMETERS_CHANGES_Z);
	//this->scaling_translation_changes_up = vec3(SCALING_PARAMETERS_CHANGES_UP_X, SCALING_PARAMETERS_CHANGES_UP_Y, SCALING_PARAMETERS_CHANGES_UP_Z);
	//this->scaling_translation_changes_down = vec3(SCALING_PARAMETERS_CHANGES_DOWN_X, SCALING_PARAMETERS_CHANGES_DOWN_Y, SCALING_PARAMETERS_CHANGES_DOWN_Z);

	this->translation_changes = vec3(TRANSLATION_CHANGES_X, TRANSLATION_CHANGES_Y, TRANSLATION_CHANGES_Z);

	this->translation_by_element = ELEMENT_TRANSLATION;

	this->camera_changes = vec3(CAMERA_CHANGES_X, CAMERA_CHANGES_Y, CAMERA_CHANGES_Z);

	this->estrangement_changes = ESTRAGNEMENT_CHANGES;

	this->vect_of_vertexes = vect_of_vertexes;
}

vvis::visualization::app_freeglut* glob_app;

void vvis::visualization::draw_sample(app_freeglut& app, int argc, char** argv) {
	glob_app = &app;

	glutInit(&argc, argv);

	glob_app->height_of_window = glutGet(GLUT_SCREEN_HEIGHT) * 2 / 3; //
	glob_app->width_of_window = glutGet(GLUT_SCREEN_HEIGHT) * 2 / 3; //
	
	glutInitWindowSize(glob_app->height_of_window, glob_app->width_of_window);

	glutInitWindowPosition(0, 0);

	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);

	int MAINWINDOW = glutCreateWindow("main_window"); glutSetWindowTitle("VISUALIS");

		glutDisplayFunc(display_render);
		glutReshapeFunc(reshape_render);

		glutKeyboardFunc(n_keys);
		glutSpecialFunc(s_keys);

		main_menu_init();

	
	glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE, GLUT_ACTION_CONTINUE_EXECUTION);
	glutMainLoop();
	
}

void vvis::visualization::display_render() {

	//glClearColor(108/255., 146/255., 175/255., 0);
	glClearColor(1.0, 1.0, 1.0, 0.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	if (glob_app->shape == SHAPE_NOTHING || glob_app->vect_of_vertexes.size() == 0) {
		// TODO: не хватает проверок. почему-то DRAW_ALL >= .size() true (???)
		glMatrixMode(GL_PROJECTION);
			
			glLoadIdentity();
			gluOrtho2D(0, glob_app->width_of_window, 0, glob_app->height_of_window);
			glColor3f(0, 0, 0);
			
		glMatrixMode(GL_MODELVIEW);
			
			glPushMatrix();
			glColor3f(0, 0, 0);
			glLoadIdentity();
			
			glRasterPos2i(glob_app->width_of_window/2, glob_app->height_of_window/2);

			[](std::string text) {int len = text.length(); for (int i = 0; i < len; ++i) glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, text[i]); }("NOTHING TO DISPLAY");
			
			glPopMatrix();

		glFlush();
		glutSwapBuffers();

	} else {

		glMatrixMode(GL_MODELVIEW);
			glLoadIdentity();

			gluLookAt(
				glob_app->position_of_camera.x, glob_app->position_of_camera.y, glob_app->position_of_camera.z,			//
				glob_app->position_of_element.x, glob_app->position_of_element.y, glob_app->position_of_element.z,		//
				0., 1., 0.
			);

		glMatrixMode(GL_PROJECTION);
			glLoadIdentity();
		
			// TODO: use ortho?
			//glOrtho(-1 * glob_app->estrangement, 1 * glob_app->estrangement, -1 * glob_app->estrangement, 1 * glob_app->estrangement, 1, 1000);	//
			//glOrtho(0, glob_app->width_of_window * glob_app->estrangement, 0, glob_app->height_of_window * glob_app->estrangement, 1, 1000);	//картинка при скейлинге в 1 в нижнем левом углу, но нужно понижать чувствительность
			
			glOrtho(
				-(double(glob_app->width_of_window) / 2.) * double(glob_app->estrangement), (double(glob_app->width_of_window) / 2.) * double(glob_app->estrangement), 
				-(double(glob_app->height_of_window) / 2.) * double(glob_app->estrangement), (double(glob_app->height_of_window) / 2.) * double(glob_app->estrangement),
				1., 1000.
			);
			
			//glob_app->global_translation.x = glob_app->width_of_window / 2;
			//glob_app->global_translation.y = glob_app->height_of_window / 2;

			

		glMatrixMode(GL_MODELVIEW);

		// TODO: проверка на индекс	

		// TODO: как сюда добавить текст, чтобы по-умному?
		// этот внизу работаетъ
		// сделать подокна
		//glColor3f(0, 0, 0);
		//glRasterPos3i(-glob_app->width_of_window / 3, -glob_app->height_of_window / 3, 0);
		//[](std::string text) {int len = text.length(); for (int i = 0; i < len; ++i) glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, text[i]); }("NOTHING TO DISPLAY");

		if (glob_app->index_of_line == DRAW_ALL) {
					
			size_t size_of_vector = glob_app->vect_of_vertexes.size();
					
			for (unsigned int i = 0; i != size_of_vector; ++i) {
				draw_shape(i);
			}

		} else {
			draw_shape(glob_app->index_of_line);
		}


		glFlush();
		glutSwapBuffers();

	}
}

void vvis::visualization::draw_shape(int index) {

	Shape* shape = NULL; // полиморфная
	double args_for_draw[4]; // 4 max of args now

	vvis::creator::Vertex current_vertex = glob_app->vect_of_vertexes[index];

	double x = current_vertex.get_point().get(L'x') * glob_app->scaling_translation.x; //
	double y = current_vertex.get_point().get(L'y') * glob_app->scaling_translation.y; //
	double z = current_vertex.get_point().get(L'z') * glob_app->scaling_translation.z; //

	switch (glob_app->shape) {



		case SHAPE_CONE: { 
			shape = new Cone(current_vertex); 

			args_for_draw[0] = 0.005 * glob_app->scaling_parameters.x;		//
			args_for_draw[1] = 0.05 * glob_app->scaling_parameters.y;		//
			args_for_draw[2] = 10;
			args_for_draw[3] = 10;

		} break;

		default: { 
			shape = new Cone(current_vertex);

			args_for_draw[0] = 0.005 * glob_app->scaling_parameters.x;		//
			args_for_draw[1] = 0.05 * glob_app->scaling_parameters.y;		//
			args_for_draw[2] = 10;
			args_for_draw[3] = 10;

		} break;
	}


	// РИСОВАНИЕ

	glPushMatrix();

	if (ROTATE_Z_FOR_SECOND_REPRESENTATION) glRotatef(-90, 1, 0, 0);

	glTranslated(0, 0, glob_app->position_of_element.z); // отвели на position_of_element от камеры нашу структуру

	

	glTranslated(glob_app->global_translation.x, glob_app->global_translation.y, glob_app->global_translation.z); // делает возможным движение вверх-вниз и вправо-влево
	glTranslated(-glob_app->position_of_camera.x, -glob_app->position_of_camera.y, -glob_app->position_of_camera.z); // делает возможным прокрутку камеры

	
	shape->set_draw_configuration(); // настроили нашу фигуру

	glRotated(glob_app->additional_rotation_phi, 0, 1, 0); // позволяет вращать фигуру саму по себе вместе с осями
	glRotatef(glob_app->additional_rotation_theta, 1, 0, 0);

	glTranslated(x, y, z);

	vvis::visualization::VvisColor_3f color_config(0, 0, 0);

	if (glob_app->use_color) {
		color_config = vvis::visualization::get_color_by_direction(current_vertex.get_spin());
	}

	shape->draw(color_config, args_for_draw);

	glPopMatrix();

	delete shape;

}

void vvis::visualization::reshape_render(int w, int h) {

	if (h == 0) h = 1;
	if (w == 0) w = 1;

	glViewport(0, 0, w, h);
	
	// по сути эти переприсвоения и сохраняет пропорции
	glob_app->width_of_window = w;
	glob_app->height_of_window = h;

}



void vvis::visualization::main_menu_init() {
	int _main_menu_render = glutCreateMenu(main_menu_render);
	
	int _menu_movements_by_arrows = glutCreateMenu(menu_movements_by_arrows);
	int _menu_movements_by_wasd = glutCreateMenu(menu_movements_by_wasd);
	int _menu_movements_by_shiftspace = glutCreateMenu(menu_movements_by_shiftspace);
	int _menu_scaling = glutCreateMenu(menu_scaling);
	int _menu_color = glutCreateMenu(menu_color);

	// sprintf делает вывод в массив buff

	glutSetMenu(_menu_movements_by_arrows);
		char buff[256]; sprintf(buff, "Current: (%g, %g, %g)", glob_app->translation_changes.x, glob_app->translation_changes.y, glob_app->translation_changes.z);
		glutAddMenuEntry(buff, MENU_RENDER_MOVEMENTS_BY_ARROWS_SHOW_SENSIVITY);
		glutAddMenuEntry("Inrease sensivity", MENU_RENDER_MOVEMENTS_BY_ARROWS_INCREASE_SENSIVITY);
		glutAddMenuEntry("Decrease sensivity", MENU_RENDER_MOVEMENTS_BY_ARROWS_DECREASE_SENSIVITY);

	glutSetMenu(_menu_movements_by_wasd);
		sprintf(buff, "Current: (%g, %g, %g)", glob_app->camera_changes.x, glob_app->camera_changes.y, glob_app->camera_changes.z);
		glutAddMenuEntry(buff, MENU_RENDER_MOVEMENTS_BY_WASD_SHOW_SENSIVITY);
		glutAddMenuEntry("Inrease sensivity", MENU_RENDER_MOVEMENTS_BY_WASD_INCREASE_SENSIVITY);
		glutAddMenuEntry("Decrease sensivity", MENU_RENDER_MOVEMENTS_BY_WASD_DECREASE_SENSIVITY);

	glutSetMenu(_menu_movements_by_shiftspace);
		sprintf(buff, "Current: (%g)", glob_app->estrangement_changes);
		glutAddMenuEntry(buff, MENU_RENDER_MOVEMENTS_BY_SHIFTSPACE_SHOW_SENSIVITY);
		glutAddMenuEntry("Inrease sensivity", MENU_RENDER_MOVEMENTS_BY_SHIFTSPACE_INCREASE_SENSIVITY);
		glutAddMenuEntry("Decrease sensivity", MENU_RENDER_MOVEMENTS_BY_SHIFTSPACE_DECREASE_SENSIVITY);

	glutSetMenu(_menu_scaling);
		sprintf(buff, "Current: (%g, %g, %g)", glob_app->scaling_parameters_changes.x, glob_app->scaling_parameters_changes.y, glob_app->scaling_parameters_changes.z);
		glutAddMenuEntry(buff, MENU_RENDER_SCALING_SHOW_SENSIVITY);
		glutAddMenuEntry("Inrease sensivity", MENU_RENDER_SCALING_INCREASE_SENSIVITY);
		glutAddMenuEntry("Decrease sensivity", MENU_RENDER_SCALING_DECREASE_SENSIVITY);

	glutSetMenu(_menu_color);
		glutAddMenuEntry("ON", MENU_COLOR_OO_ON);
		glutAddMenuEntry("OFF", MENU_COLOR_OO_OFF);

	glutSetMenu(_main_menu_render);
		glutAddSubMenu("Movements by arrows", _menu_movements_by_arrows);
		glutAddSubMenu("Movements by wasd/ijkl", _menu_movements_by_wasd);
		glutAddSubMenu("Movements by shift(lctrl)/space", _menu_movements_by_shiftspace);
		glutAddSubMenu("Scaling parameters by pageup/pagedown", _menu_scaling);
		glutAddSubMenu("Coloring", _menu_color);

	glutAttachMenu(GLUT_RIGHT_BUTTON);
	glutDetachMenu(GLUT_LEFT_BUTTON);

}

void vvis::visualization::main_menu_render(int code) {
	switch (code) {
		default: {

		} break;
	}
}

void vvis::visualization::menu_movements_by_arrows(int code) {
	switch (code) {


		case MENU_RENDER_MOVEMENTS_BY_ARROWS_INCREASE_SENSIVITY: {
			glob_app->translation_changes.x *= MOVEMENTS_BY_ARROWS_MULTIPLY_SENSIVITY;
			glob_app->translation_changes.y *= MOVEMENTS_BY_ARROWS_MULTIPLY_SENSIVITY;
			glob_app->translation_changes.z *= MOVEMENTS_BY_ARROWS_MULTIPLY_SENSIVITY;

			char buff[256]; sprintf(buff, "Current: (%g, %g, %g)", glob_app->translation_changes.x, glob_app->translation_changes.y, glob_app->translation_changes.z);
			glutChangeToMenuEntry(1, buff, MENU_RENDER_MOVEMENTS_BY_ARROWS_SHOW_SENSIVITY);

		} break;

		case MENU_RENDER_MOVEMENTS_BY_ARROWS_DECREASE_SENSIVITY: {
			glob_app->translation_changes.x /= MOVEMENTS_BY_ARROWS_MULTIPLY_SENSIVITY;
			glob_app->translation_changes.y /= MOVEMENTS_BY_ARROWS_MULTIPLY_SENSIVITY;
			glob_app->translation_changes.z /= MOVEMENTS_BY_ARROWS_MULTIPLY_SENSIVITY;

			char buff[256]; sprintf(buff, "Current: (%g, %g, %g)", glob_app->translation_changes.x, glob_app->translation_changes.y, glob_app->translation_changes.z);
			glutChangeToMenuEntry(1, buff, MENU_RENDER_MOVEMENTS_BY_ARROWS_SHOW_SENSIVITY);

		} break;

		default: {

		} break;
	}
}

void vvis::visualization::menu_movements_by_wasd(int code) {
	switch (code) {


		case MENU_RENDER_MOVEMENTS_BY_WASD_INCREASE_SENSIVITY: {
			glob_app->camera_changes.x *= MOVEMENTS_BY_WASD_MULTIPLY_SENSIVITY;
			glob_app->camera_changes.y *= MOVEMENTS_BY_WASD_MULTIPLY_SENSIVITY;
			glob_app->camera_changes.z *= MOVEMENTS_BY_WASD_MULTIPLY_SENSIVITY;

			char buff[256]; sprintf(buff, "Current: (%g, %g, %g)", glob_app->camera_changes.x, glob_app->camera_changes.y, glob_app->camera_changes.z);
			glutChangeToMenuEntry(1, buff, MENU_RENDER_MOVEMENTS_BY_WASD_SHOW_SENSIVITY);

		} break;

		case MENU_RENDER_MOVEMENTS_BY_WASD_DECREASE_SENSIVITY: {
			glob_app->camera_changes.x /= MOVEMENTS_BY_WASD_MULTIPLY_SENSIVITY;
			glob_app->camera_changes.y /= MOVEMENTS_BY_WASD_MULTIPLY_SENSIVITY;
			glob_app->camera_changes.z /= MOVEMENTS_BY_WASD_MULTIPLY_SENSIVITY;

			char buff[256]; sprintf(buff, "Current: (%g, %g, %g)", glob_app->camera_changes.x, glob_app->camera_changes.y, glob_app->camera_changes.z);
			glutChangeToMenuEntry(1, buff, MENU_RENDER_MOVEMENTS_BY_WASD_SHOW_SENSIVITY);

		} break;

		default: {

		} break;
	}
}

void vvis::visualization::menu_movements_by_shiftspace(int code) {
	switch (code) {

		case MENU_RENDER_MOVEMENTS_BY_SHIFTSPACE_INCREASE_SENSIVITY: {
			glob_app->estrangement_changes *= MOVEMENTS_BY_SHIFTSPACE_MULTIPLY_SENSIVITY;

			char buff[256]; sprintf(buff, "Current: (%g)", glob_app->estrangement_changes);
			glutChangeToMenuEntry(1, buff, MENU_RENDER_MOVEMENTS_BY_SHIFTSPACE_SHOW_SENSIVITY);

		} break;

		case MENU_RENDER_MOVEMENTS_BY_SHIFTSPACE_DECREASE_SENSIVITY: {
			glob_app->estrangement_changes /= MOVEMENTS_BY_SHIFTSPACE_MULTIPLY_SENSIVITY;

			char buff[256]; sprintf(buff, "Current: (%g)", glob_app->estrangement_changes);
			glutChangeToMenuEntry(1, buff, MENU_RENDER_MOVEMENTS_BY_SHIFTSPACE_SHOW_SENSIVITY);

		} break;

		default: {

		} break;
	}
}

void vvis::visualization::menu_scaling(int code) {
	switch (code) {

		case MENU_RENDER_SCALING_INCREASE_SENSIVITY: {
			glob_app->scaling_parameters_changes.x *= SCALING_MULTIPLY_SENSIVITY_X;
			glob_app->scaling_parameters_changes.y *= SCALING_MULTIPLY_SENSIVITY_Y;
			glob_app->scaling_parameters_changes.z *= SCALING_MULTIPLY_SENSIVITY_Z;

			char buff[256]; sprintf(buff, "Current: (%g, %g, %g)", glob_app->scaling_parameters_changes.x, glob_app->scaling_parameters_changes.y, glob_app->scaling_parameters_changes.z);
			glutChangeToMenuEntry(1, buff, MENU_RENDER_SCALING_SHOW_SENSIVITY);
		} break;

		case MENU_RENDER_SCALING_DECREASE_SENSIVITY: {
			glob_app->scaling_parameters_changes.x /= SCALING_MULTIPLY_SENSIVITY_X;
			glob_app->scaling_parameters_changes.y /= SCALING_MULTIPLY_SENSIVITY_Y;
			glob_app->scaling_parameters_changes.z /= SCALING_MULTIPLY_SENSIVITY_Z;

			char buff[256]; sprintf(buff, "Current: (%g, %g, %g)", glob_app->scaling_parameters_changes.x, glob_app->scaling_parameters_changes.y, glob_app->scaling_parameters_changes.z);
			glutChangeToMenuEntry(1, buff, MENU_RENDER_SCALING_SHOW_SENSIVITY);
		} break;

	}
}

void vvis::visualization::menu_color(int code) {
	switch (code) {

		case MENU_COLOR_OO_OFF: {
			glob_app->use_color = false;

			glutPostRedisplay();
		} break;

		case MENU_COLOR_OO_ON: {
			glob_app->use_color = true;

			glutPostRedisplay();
		} break;

	}
}

void vvis::visualization::s_keys(int key, int x, int y) {
	
	switch (key) {


		// отвечают за увеличение и уменьшение самих конусов

		case GLUT_KEY_PAGE_UP: {

			glob_app->scaling_parameters.x += glob_app->scaling_parameters_changes.x;
			glob_app->scaling_parameters.y += glob_app->scaling_parameters_changes.y;
			glob_app->scaling_parameters.z += glob_app->scaling_parameters_changes.z;
				
			glutPostRedisplay();
		} break;

		case GLUT_KEY_PAGE_DOWN: {

			glob_app->scaling_parameters.x -= glob_app->scaling_parameters_changes.x;
			glob_app->scaling_parameters.y -= glob_app->scaling_parameters_changes.y;
			glob_app->scaling_parameters.z -= glob_app->scaling_parameters_changes.z;

			glutPostRedisplay();
		} break;


		// отвечают за движение картинки

		case GLUT_KEY_LEFT: {

			glob_app->global_translation.x -= glob_app->translation_by_element * glob_app->translation_changes.x;

			glutPostRedisplay();
		} break;

		case GLUT_KEY_RIGHT: {

			glob_app->global_translation.x += glob_app->translation_by_element * glob_app->translation_changes.x;

			glutPostRedisplay();
		} break;

		case GLUT_KEY_UP: {

			glob_app->global_translation.y += glob_app->translation_by_element * glob_app->translation_changes.y;

			glutPostRedisplay();
		} break;

		case GLUT_KEY_DOWN: {

			glob_app->global_translation.y -= glob_app->translation_by_element * glob_app->translation_changes.y;

			glutPostRedisplay();
		} break;

		// отвечают за приближение к картинке

		case GLUT_KEY_CTRL_L:
		case GLUT_KEY_SHIFT_L: {

			glob_app->estrangement -= glob_app->estrangement_changes;

			glutPostRedisplay();
		} break;

		// полный экран

		case GLUT_KEY_F11: {

			if (!glob_app->fullscreen) {
				glutFullScreen(); glob_app->fullscreen = true;
			} else {
				glutPositionWindow(0, 0); glob_app->fullscreen = false;
			}
				
		} break;

		default: {
			//
		} break;

	}
}

void vvis::visualization::n_keys(unsigned char key, int x, int y) {
	
	switch (key) {

		// отвечают за поведение камеры (вверх-вниз, влево-вправо)

		case 'w' : {
			glob_app->position_of_camera.y -= glob_app->translation_by_element * glob_app->camera_changes.y;
			glob_app->position_of_element.y += glob_app->translation_by_element * glob_app->camera_changes.y;

			glutPostRedisplay();
		} break;

		case 's' : {
			glob_app->position_of_camera.y += glob_app->translation_by_element * glob_app->camera_changes.y;
			glob_app->position_of_element.y -= glob_app->translation_by_element * glob_app->camera_changes.y;

			glutPostRedisplay();
		} break;

		case 'a' : {
			glob_app->position_of_camera.x += glob_app->translation_by_element * glob_app->camera_changes.x;
			glob_app->position_of_element.x -= glob_app->translation_by_element * glob_app->camera_changes.x;

			glutPostRedisplay();
		} break;

		case 'd' : {
			glob_app->position_of_camera.x -= glob_app->translation_by_element * glob_app->camera_changes.x;
			glob_app->position_of_element.x += glob_app->translation_by_element * glob_app->camera_changes.x;
			
			glutPostRedisplay();
		} break;


		// отвечают за дополнительный поворот образца

		case 'i': {
			glob_app->additional_rotation_theta -= glob_app->translation_by_element * glob_app->camera_changes.y;

			glutPostRedisplay();
		} break;

		case 'k': {
			glob_app->additional_rotation_theta += glob_app->translation_by_element * glob_app->camera_changes.y;

			glutPostRedisplay();
		} break;

		case 'j': {
			glob_app->additional_rotation_phi -= glob_app->translation_by_element * glob_app->camera_changes.x;

			glutPostRedisplay();
		} break;

		case 'l': {
			glob_app->additional_rotation_phi += glob_app->translation_by_element * glob_app->camera_changes.x;

			glutPostRedisplay();
		} break;

		// отвечает за отдаление картинки

		case ' ': {

			glob_app->estrangement += glob_app->estrangement_changes;

			glutPostRedisplay();
		} break;

		case 27: {
			//int mod = glutGetModifiers(); if mod == GLUT_ACTIVE_SHIFT ctrl alt 
			glutLeaveMainLoop();
		} break;

		default: {
			//
		} break;

	}

}