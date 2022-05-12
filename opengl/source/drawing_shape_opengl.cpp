#include "./include/sample/drawing_shape_opengl.hpp"

// TODO: возможность настройки т.е. кнопкой вызываем консоль туда вбиваем что-нибудь и оно меняет параметры
// TODO: флаг use_ortho

// TODO: перемещение камеры по плоскостям образца

vvis::visualization::app_freeglut::app_freeglut() {
	this->index_of_line = 0;
	this->additional_rotation_phi = 0.0;
	this->additional_rotation_theta = 0.0;

	this->estrangement = 1.0;

	this->use_color = false;
	this->shape = SHAPE_NOTHING;

	this->height_of_window = 0;
	this->width_of_window = 0;

	this->global_translation = vec3(0., 0., 0.);
	this->scaling_parameters = vec3(1., 1., 1.);
	this->scaling_translation = vec3(1. / 32., 1. / 32., 1. / 32.);
	this->position_of_camera = vec3(0., 0., 0.);
	this->position_of_element = vec3(0., 0., -100.);

	this->scaling_translation_changes_up = vec3(SCALING_PARAMETERS_CHANGES_UP_X, SCALING_PARAMETERS_CHANGES_UP_Y, SCALING_PARAMETERS_CHANGES_UP_Z);
	this->scaling_translation_changes_down = vec3(SCALING_PARAMETERS_CHANGES_DOWN_X, SCALING_PARAMETERS_CHANGES_DOWN_Y, SCALING_PARAMETERS_CHANGES_DOWN_Z);

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

	this->height_of_window = 0;
	this->width_of_window = 0;

	this->global_translation = vec3(0., 0., 0.);
	this->scaling_parameters = vec3(1., 1., 1.);
	this->scaling_translation = vec3(1./32., 1./32., 1./32.);
	this->position_of_camera = vec3(0., 0., 0.);
	this->position_of_element = vec3(0., 0., -100.);

	this->scaling_translation_changes_up = vec3(SCALING_PARAMETERS_CHANGES_UP_X, SCALING_PARAMETERS_CHANGES_UP_Y, SCALING_PARAMETERS_CHANGES_UP_Z);
	this->scaling_translation_changes_down = vec3(SCALING_PARAMETERS_CHANGES_DOWN_X, SCALING_PARAMETERS_CHANGES_DOWN_Y, SCALING_PARAMETERS_CHANGES_DOWN_Z);

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
	
	glutInitWindowSize(glob_app->height_of_window, glob_app->width_of_window); // ПОКА НЕТ RESHAPE

	glutInitWindowPosition(0, 0);

	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);

	int MAINWINDOW = glutCreateWindow("main_window"); glutSetWindowTitle("VISUALIS");

		glutDisplayFunc(display);

		glutKeyboardFunc(vvis::visualization::n_keys);
		glutSpecialFunc(vvis::visualization::s_keys);

		glutMainLoop();
}


void vvis::visualization::display() {

	glClearColor(1, 1, 1, 0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	if (glob_app->shape == SHAPE_NOTHING || glob_app->vect_of_vertexes.size() == 0 || glob_app->index_of_line >= glob_app->vect_of_vertexes.size()) {

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

		glutSwapBuffers();

	} else {

		glMatrixMode(GL_MODELVIEW);
			glLoadIdentity();

			gluLookAt(
				glob_app->position_of_camera.x, glob_app->position_of_camera.y, glob_app->position_of_camera.z,			//
				glob_app->position_of_element.x, glob_app->position_of_element.y, glob_app->position_of_element.z,		//
				0, 1, 0
			);

		glMatrixMode(GL_PROJECTION);
			glLoadIdentity();
		
			// TODO: use ortho?
			glOrtho(-1 * glob_app->estrangement, 1 * glob_app->estrangement, -1 * glob_app->estrangement, 1 * glob_app->estrangement, 1, 1000);	//
			//glOrtho(0, glob_app->width_of_window * glob_app->estrangement, 0, glob_app->height_of_window * glob_app->estrangement, 1, 1000);	//картинка при скейлинге в 1 в нижнем левом углу, но нужно понижать чувствительность
			//glOrtho(-(glob_app->width_of_window / 2) * glob_app->estrangement, (glob_app->width_of_window/2) * glob_app->estrangement, -(glob_app->width_of_window / 2) * glob_app->estrangement, (glob_app->width_of_window / 2) * glob_app->estrangement, 1, 1000);
			// работают все варианты, но нужно определиться с тем, который использовать, потому что всё остальное зависит от него

		glMatrixMode(GL_MODELVIEW);

		// TODO: проверка на индекс	



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

	glTranslated(0, 0, glob_app->position_of_element.z); // отвели на position_of_element от камеры нашу структуру

	if (ROTATE_Z_FOR_SECOND_REPRESENTATION) glRotatef(-90, 1, 0, 0);

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

void vvis::visualization::s_keys(int key, int x, int y) {
	
	switch (key) {


		// отвечают за увеличение и уменьшение самих конусов

		case GLUT_KEY_PAGE_UP: {

			glob_app->scaling_parameters.x *= glob_app->scaling_translation_changes_up.x;
			glob_app->scaling_parameters.y *= glob_app->scaling_translation_changes_up.y;
			glob_app->scaling_parameters.z *= glob_app->scaling_translation_changes_up.z;
				
			glutPostRedisplay();
		} break;

		case GLUT_KEY_PAGE_DOWN: {

			glob_app->scaling_parameters.x *= glob_app->scaling_translation_changes_down.x;
			glob_app->scaling_parameters.y *= glob_app->scaling_translation_changes_down.y;
			glob_app->scaling_parameters.z *= glob_app->scaling_translation_changes_down.z;

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

		default: {
			//
		} break;

	}

}