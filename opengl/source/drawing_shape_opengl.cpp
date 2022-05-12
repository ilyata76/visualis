#include "./include/sample/drawing_shape_opengl.hpp"


int glob_index = 0;
int glob_color = false;


int w_g = 0;
int h_g = 0;

double glob_camera_theta = 0.0;
double glob_camera_phi = 0.0;

// TODO: поведение камеры странное, будто не хватает пространства для видения (Far, Near плоскости)
// TODO: и это не только в отношении z
// что с ней делать?

// TODO: проверить; page up показал, что 0 1 1 лежит поверх 1 0 0 (увеличение конусов), т.е. Z смотрит НА НАС? ало так правильно всё нормально

// TODO: возможность настройки т.е. кнопкой вызываем консоль туда вбиваем что-нибудь и оно меняет параметры

// TODO: флаг use_ortho

// TODO tolerance flags

// TODO: перемещение камеры по плоскостям образца

struct transl {
	double x;
	double y;
	double z;

	transl() : x(0), y(0), z(0) {};
	transl(double x, double y, double z) : x(x), y(y), z(z) {};
} glob_transl(0, 0, 0);

struct scaling {
	double x;
	double y;
	double z;

	scaling() : x(0), y(0), z(0) {};
	scaling(double x, double y, double z) : x(x), y(y), z(z) {};
} glob_shape_scaling(1, 1, 1);

scaling glob_translation_scaling(1, 1, 1);

struct camera {
	double x;
	double y;
	double z;

	camera() : x(0), y(0), z(0) {};
	camera(double x, double y, double z) : x(x), y(y), z(z) {};
} glob_camera(0, 0, 0);

struct element {
	double x;
	double y;
	double z;

	element() : x(0), y(0), z(0) {};
	element(double x, double y, double z) : x(x), y(y), z(z) {};
} glob_elem(0, 0, -100); // ???


//double glob_camera_phi = 0.0;
//double glob_camera_theta = 0.0;

double glob_estrangement = 1.0;

double ANGLE = 0.0;

std::vector<vvis::creator::Vertex> vrt_vctr;

void vvis::visualization::display_nothing() {
	// TODO: это работает, но я не знаю каким образом надо бы разобраться с матрицами и viewimport'ом
	// тоже кстати не с первого раза запустилась вопрос почему открытый
	
	glClearColor(1, 1, 1, 0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	//gluOrtho2D(0, 1400, 0, 800);

	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	std::string menu = "NOTHING TO DISPLAY";
	glLoadIdentity();
	int len = menu.length();
	glColor3f(0, 0, 0);
	glRasterPos2i(10, 200);  // move in 10 pixels from the left and bottom edges
	for (int i = 0; i < len; ++i) {
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_10, menu[i]);
	}
	glPopMatrix();
	glutSwapBuffers();
}

void vvis::visualization::draw_cone_spin(int& index, bool color) {
	double x = vrt_vctr[glob_index].get_point().get(L'x') * glob_translation_scaling.x;
	double y = vrt_vctr[glob_index].get_point().get(L'y') * glob_translation_scaling.y;
	double z = vrt_vctr[glob_index].get_point().get(L'z') * glob_translation_scaling.z;
	vvis::visualization::Cone my_cone(vrt_vctr[glob_index]);

	glPushMatrix();



	//
	

	glTranslated(0, 0, glob_elem.z);



	if (ROTATE_Z_FOR_SECOND_REPRESENTATION) glRotatef(-90, 1, 0, 0);
	
	glTranslated(glob_transl.x, glob_transl.y, glob_transl.z);
	glTranslated(-glob_camera.x, -glob_camera.y, -glob_camera.z); // делает возможным прокрутку

	
	//glScaled(w_g/2, h_g/2, w_g/2);

	// glScaled(glob_scaling.x, glob_scaling.y, glob_scaling.z); плохо работает: куда деваются конусы?
	
	my_cone.set_draw_configuration();
	
	glRotatef(glob_camera_theta, 1, 0, 0);
	glRotated(glob_camera_phi, 0, 1, 0);

	glTranslated(x / 32, y / 32, z / 32); // TODO: параметры скейлинга трансляции

	if (color == true) {
		//my_cone.draw(0.005 * glob_shape_scaling.x, 0.05 * glob_shape_scaling.y, 10, 10, vvis::visualization::get_color_by_direction(vrt_vctr[glob_index].get_spin())); // TODO: параметры конуса

		double A[4] = { 0.005 * glob_shape_scaling.x, 0.05 * glob_shape_scaling.y, 10, 10 };
		my_cone.new_draw(vvis::visualization::get_color_by_direction(vrt_vctr[glob_index].get_spin()), A);

	}
	else 
		my_cone.draw(0.005 * glob_shape_scaling.x, 0.05 * glob_shape_scaling.y, 10, 10, vvis::visualization::VvisColor_3f(0, 0, 0)); // TODO: параметры конуса

	glPopMatrix();
}

void vvis::visualization::display_cone() {
	glClearColor(1, 1, 1, 0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
		
	gluLookAt(
		glob_camera.x, glob_camera.y, glob_camera.z,
		glob_elem.x, glob_elem.y, glob_elem.z,
		0, 1, 0
	);

	//glTranslated(glob_camera.x, glob_camera.y, glob_camera.z); doesnt work

	//gluPerspective(10, glutGet(GLUT_SCREEN_WIDTH)/glutGet(GLUT_SCREEN_HEIGHT), 1.0, 400.0); // при угле в 1 видно картинку rolf
	
	
	
	//glFrustum(-1, 1, -1, 1, 10 * glob_estrangement, 4000); // этим можно пользоваться, чтобы управлять камерой
	
	// TODO: надо понять как рассчитать изменение положение glob_elem

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	// USE ORTHO?
	glOrtho(-1 * glob_estrangement, 1 * glob_estrangement, -1 * glob_estrangement, 1 * glob_estrangement, 1, 1000); // ортогональная проекция RABOTAET
	//glOrtho(-250, 250, -250, 250, -10, 1000);
	//glOrtho(0, w_g, 0, h_g, -100, 1000);
	
	//glFrustum(-1, 1, -1, 1, 1 * glob_estrangement, 1000);
	
	glMatrixMode(GL_MODELVIEW);
	
	if (glob_index == DRAW_ALL) {

		glob_index = 0; size_t size = vrt_vctr.size();
		for (glob_index; glob_index != size; ++glob_index) {
			draw_cone_spin(glob_index, glob_color);
		}
		glob_index = DRAW_ALL;
	} else {

		// TODO : проверка не больше ли чем размер
		draw_cone_spin(glob_index, glob_color);
	}



	glFlush();
	glutSwapBuffers();
}

//#include <iostream>

// поставить поближе и крутить точнее и чувствительнее? - неудобно для отображения

void vvis::visualization::normal_keys(unsigned char key, int x, int y) {
	
	switch (key) {


		case 'w' : {
			glob_camera.y += 0.1f;
			glob_elem.y -= 0.1f;

			glutPostRedisplay();
		} break;

		case 's' : {
			glob_camera.y -= 0.1f;
			glob_elem.y += 0.1f;

			glutPostRedisplay();
		} break;

		case 'a' : {
			glob_camera.x += 0.1f;
			glob_elem.x -= 0.1f;

			glutPostRedisplay();
		} break;

		case 'd' : {
			glob_camera.x -= 0.1f;
			glob_elem.x += 0.1f;
			
			glutPostRedisplay();
		} break;



		// отдельный блок поворота системы

		// TODO переименовать переменные


		case 'i' : {
			glob_camera_theta += 0.1f;

			glutPostRedisplay();
		} break;

		case 'k' : {
			glob_camera_theta -= 0.1f;

			glutPostRedisplay();
		} break;

		case 'j' : {
			glob_camera_phi += 0.1f;

			glutPostRedisplay();
		} break;

		case 'l' : {
			glob_camera_phi -= 0.1f;
			
			glutPostRedisplay();
		} break;






		case ' ': {
			glob_estrangement += 0.1;
			glutPostRedisplay();

		} break;

		case '9': {
			if (glob_translation_scaling.x < SCALING_TRANSLATION_UPPER_LIMIT && glob_translation_scaling.y < SCALING_TRANSLATION_UPPER_LIMIT && glob_translation_scaling.z < SCALING_TRANSLATION_UPPER_LIMIT) {
				glob_translation_scaling.x *= 1.1;
				glob_translation_scaling.y *= 1.1;
				glob_translation_scaling.z *= 1.1;
			} // здесь, кстати говоря, конусы тоже пропадают
			glutPostRedisplay();
		} break;

		case '8': {
			if (glob_translation_scaling.x > SCALING_TRANSLATION_LOWER_LIMIT && glob_translation_scaling.y > SCALING_TRANSLATION_LOWER_LIMIT && glob_translation_scaling.z > SCALING_TRANSLATION_LOWER_LIMIT) {
				glob_translation_scaling.x *= 0.9;
				glob_translation_scaling.y *= 0.9;
				glob_translation_scaling.z *= 0.9;
			}
			glutPostRedisplay();
		} break;

		default: {

		} break;

	} 
}

void vvis::visualization::special_keys(int key, int x, int y) {
	switch (key) {

		case GLUT_KEY_PAGE_UP: {
			//if (glob_shape_scaling.x < SCALING_SHAPE_UPPER_LIMIT && glob_shape_scaling.y < SCALING_SHAPE_UPPER_LIMIT && glob_shape_scaling.z < SCALING_SHAPE_UPPER_LIMIT) {
				glob_shape_scaling.x *= 1.1;
				glob_shape_scaling.y *= 1.1;
				glob_shape_scaling.z *= 1.1;
			//}
				glutPostRedisplay();
		} break;

		case GLUT_KEY_PAGE_DOWN: {
			//if (glob_shape_scaling.x > SCALING_SHAPE_LOWER_LIMIT && glob_shape_scaling.y > SCALING_SHAPE_LOWER_LIMIT && glob_shape_scaling.z > SCALING_SHAPE_LOWER_LIMIT) {
				glob_shape_scaling.x *= 0.9;
				glob_shape_scaling.y *= 0.9;
				glob_shape_scaling.z *= 0.9;
			//} 
				glutPostRedisplay();
		} break;

		case GLUT_KEY_LEFT: {
			glob_transl.x += -1.0 * TRANSLATION_BY_HEAD * TRANSLATION_CONST;
			glob_transl.y += 0;
			glob_transl.z += 0;
			glutPostRedisplay();
		} break;

		case GLUT_KEY_RIGHT: {
			glob_transl.x += TRANSLATION_BY_HEAD * TRANSLATION_CONST;
			glob_transl.y += 0;
			glob_transl.z += 0;
			glutPostRedisplay();
		} break;

		case GLUT_KEY_UP: {
			glob_transl.x += 0;
			glob_transl.y += TRANSLATION_BY_HEAD * TRANSLATION_CONST;
			glob_transl.z += 0;
			glutPostRedisplay();
		} break;

		case GLUT_KEY_DOWN: {
			glob_transl.x += 0;
			glob_transl.y += -1.0 * TRANSLATION_BY_HEAD * TRANSLATION_CONST;
			glob_transl.z += 0;
			glutPostRedisplay();
		} break;


		case GLUT_KEY_CTRL_L:
		case GLUT_KEY_SHIFT_L: {
			glob_estrangement -= 0.1;
			glutPostRedisplay();
		} break;

		default: {

		} break;

	} 
}

void vvis::visualization::main_glut(int argc, char** argv, std::vector<vvis::creator::Vertex>& vect, 
									wchar_t shape, bool color, int index) {
	
	vrt_vctr = vect;

	glob_index = index;
	glob_color = color;

	glutInit(&argc, argv);

	glutInitWindowSize(glutGet(GLUT_SCREEN_HEIGHT) * 2/3, glutGet(GLUT_SCREEN_HEIGHT) * 2/3); // ПОКА НЕТ RESHAPE
	//w_g = 500, h_g = 500;
	//glutInitWindowSize(w_g, h_g);
	glutInitWindowPosition(0, 0);

	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
		
	int MAINWINDOW = glutCreateWindow("mainwindow"); 
	
	//glutFullScreen(); // ПОКА НЕТ RESHAPE
	
	glutSetWindowTitle("TTITLE");

	switch (shape) {
		case SHAPE_CONE: {

			glutDisplayFunc(vvis::visualization::display_cone);

			glutKeyboardFunc(vvis::visualization::normal_keys);
			glutSpecialFunc(vvis::visualization::special_keys);

			//glutReshapeFunc(vvis::visualization::myReshape); // doesnt work

			glutMainLoop();
		} break;

		default: {
			glutDisplayFunc(vvis::visualization::display_nothing);

			glutMainLoop();
		}
	}

	
	//glutIdleFunc(display);
	
}


//#include <iostream>

//TODO reshape всё ещё не работает
void vvis::visualization::myReshape(int w, int h) {

	glViewport(0, 0, w, h);

	if (h == 0)	h = 1;

	double aspectRatio = double(w) / double(h);

	//std::wcout << "RESHAPE: " << aspectRatio << " W: " << w << " H: " << h << '\n';
	
	glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		
		
		glOrtho(-1, 1, -1, 1, 1, 1000);
		//w_g = w;
		//h_g = h;

	glMatrixMode(GL_MODELVIEW);

}


// TODO: не все reshapы работают (картинка исчезает)
// результаты этого нельзя повторить?? почему? ведь если просто скопировать, то всё работает https://grafika.me/node/128

// NeHe : gluPerspective(45.0f, (GLfloat)w / (GLfloat)h, 0.1f, 100.0f);
// это не работает!!!

//void vvis::visualization::myReshape(int w, int h) {
//
//	// предупредим деление на ноль
//	// если окно сильно перетянуто будет
//	if (h == 0)
//		h = 1;
//	float ratio = 1.0 * w / h;
//	std::wcout << w;
//	// используем матрицу проекции
//	glMatrixMode(GL_PROJECTION);
//
//	// Reset матрицы
//	glLoadIdentity();
//
//	// определяем окно просмотра
//	glViewport(0, 0, w, h);
//
//	// установить корректную перспективу.
//
//	// 0 do nothing
//	//gluPerspective(45, ratio, 1, 1000);
//	//gluLookAt(0, 0, 1, 0, 0, 0, 0, 1, 0);
//	
//	// ну конечно!!! http://dkhramov.dp.ua/Comp.GlutAndOpenGL#.YnMK7OrP2Uk ! мы просто ничего не видим
//
//
//	glOrtho(0.0, w, h, 0.0, 0.0, 0.0);
//	// и как это того этого?
//
//	// https://docs.microsoft.com/en-us/windows/win32/opengl/glortho
//	// https://stackoverflow.com/questions/2571402/how-to-use-glortho-in-opengl
//	// https://ru.stackoverflow.com/questions/434277/glutreshapefunc-и-glutdisplayfunc-в-opengl
//
//	// вернуться к модели
//	glMatrixMode(GL_MODELVIEW);
//}



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

	shape->new_draw(color_config, args_for_draw);

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