#include "./include/sample/drawing_shape_opengl.hpp"


int glob_index = 0;
int glob_color = false;


// TODO: поведение камеры странное, будто не хватает пространства для видения (Far, Near плоскости)
// TODO: и это не только в отношении z
// что с ней делать?

// TODO: проверить; page up показал, что 0 1 1 лежит поверх 1 0 0 (увеличение конусов), т.е. Z смотрит НА НАС? ало так правильно всё нормально

// TODO: возможность настройки т.е. кнопкой вызываем консоль туда вбиваем что-нибудь и оно меняет параметры

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


double glob_camera_phi = 0.0;
double glob_camera_theta = 0.0;

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



	glRotated(glob_camera_phi, 0, 1, 0);
	glRotated(glob_camera_theta, 1, 0, 0);

	glTranslatef(0, 0, glob_elem.z);

	if (ROTATE_Z_FO_SECOND_REPRESENTATION) glRotatef(-90, 1, 0, 0);
	
	glTranslated(glob_transl.x, glob_transl.y, glob_transl.z);
	glTranslated(-glob_camera.x, -glob_camera.y, -glob_camera.z);

	
	// glScaled(glob_scaling.x, glob_scaling.y, glob_scaling.z); плохо работает: куда деваются конусы?
	
	my_cone.set_draw_configuration();
	
	glTranslated(x / 32, y / 32, z / 32); // TODO: параметры скейлинга трансляции

	if (color == true)
		my_cone.draw(0.005 * glob_shape_scaling.x, 0.05 * glob_shape_scaling.y, 10, 10, vvis::visualization::get_color_by_direction(vrt_vctr[glob_index].get_spin())); // TODO: параметры конуса
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
	glOrtho(-1 * glob_estrangement, 1 * glob_estrangement, -1 * glob_estrangement, 1 * glob_estrangement, 1, 1000); // ортогональная проекция
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

		} break;

		case 's' : {
			glob_camera.y -= 0.1f;
			glob_elem.y += 0.1f;

		} break;

		case 'a' : {
			glob_camera.x += 0.1f;
			glob_elem.x -= 0.1f;

		} break;

		case 'd' : {
			glob_camera.x -= 0.1f;
			glob_elem.x += 0.1f;
			
		} break;



		// отдельный блок поворота системы

		// TODO переименовать переменные


		//case 'i' : {
		//	//std::cout << "ABOBUS: "; int a; std::cin >> a; это работает
		//	glob_camera_theta += 0.1f;

		//} break;

		//case 'k' : {
		//	glob_camera_theta -= 0.1f;

		//} break;

		//case 'j' : {
		//	glob_camera_phi += 0.1f;

		//} break;

		//case 'l' : {
		//	glob_camera_phi -= 0.1f;
		//	
		//} break;






		case ' ': {
			glob_estrangement += 0.1;

		} break;

		case '9': {
			if (glob_translation_scaling.x < SCALING_TRANSLATION_UPPER_LIMIT && glob_translation_scaling.y < SCALING_TRANSLATION_UPPER_LIMIT && glob_translation_scaling.z < SCALING_TRANSLATION_UPPER_LIMIT) {
				glob_translation_scaling.x *= 1.1;
				glob_translation_scaling.y *= 1.1;
				glob_translation_scaling.z *= 1.1;
			} // здесь, кстати говоря, конусы тоже пропадают
		} break;

		case '8': {
			if (glob_translation_scaling.x > SCALING_TRANSLATION_LOWER_LIMIT && glob_translation_scaling.y > SCALING_TRANSLATION_LOWER_LIMIT && glob_translation_scaling.z > SCALING_TRANSLATION_LOWER_LIMIT) {
				glob_translation_scaling.x *= 0.9;
				glob_translation_scaling.y *= 0.9;
				glob_translation_scaling.z *= 0.9;
			}
		} break;

	} glutPostRedisplay();
}

void vvis::visualization::special_keys(int key, int x, int y) {
	switch (key) {

		case GLUT_KEY_PAGE_UP: {
			if (glob_shape_scaling.x < SCALING_SHAPE_UPPER_LIMIT && glob_shape_scaling.y < SCALING_SHAPE_UPPER_LIMIT && glob_shape_scaling.z < SCALING_SHAPE_UPPER_LIMIT) {
				glob_shape_scaling.x *= 1.1;
				glob_shape_scaling.y *= 1.1;
				glob_shape_scaling.z *= 1.1;
			}
		} break;

		case GLUT_KEY_PAGE_DOWN: {
			if (glob_shape_scaling.x > SCALING_SHAPE_LOWER_LIMIT && glob_shape_scaling.y > SCALING_SHAPE_LOWER_LIMIT && glob_shape_scaling.z > SCALING_SHAPE_LOWER_LIMIT) {
				glob_shape_scaling.x *= 0.9;
				glob_shape_scaling.y *= 0.9;
				glob_shape_scaling.z *= 0.9;
			} 
			
		} break;

		case GLUT_KEY_LEFT: {
			glob_transl.x += -1.0 * TRANSLATION_BY_HEAD * TRANSLATION_CONST;
			glob_transl.y += 0;
			glob_transl.z += 0;

		} break;

		case GLUT_KEY_RIGHT: {
			glob_transl.x += TRANSLATION_BY_HEAD * TRANSLATION_CONST;
			glob_transl.y += 0;
			glob_transl.z += 0;

		} break;

		case GLUT_KEY_UP: {
			glob_transl.x += 0;
			glob_transl.y += TRANSLATION_BY_HEAD * TRANSLATION_CONST;
			glob_transl.z += 0;

		} break;

		case GLUT_KEY_DOWN: {
			glob_transl.x += 0;
			glob_transl.y += -1.0 * TRANSLATION_BY_HEAD * TRANSLATION_CONST;
			glob_transl.z += 0;

		} break;


		case GLUT_KEY_CTRL_L:
		case GLUT_KEY_SHIFT_L: {
			glob_estrangement -= 0.1;

		} break;

	} glutPostRedisplay();
}

void vvis::visualization::main_glut(int argc, char** argv, std::vector<vvis::creator::Vertex>& vect, 
									wchar_t shape, bool color, int index) {
	
	vrt_vctr = vect;

	glob_index = index;
	glob_color = color;

	glutInit(&argc, argv);

	glutInitWindowSize(glutGet(GLUT_SCREEN_WIDTH), glutGet(GLUT_SCREEN_HEIGHT)); // ПОКА НЕТ RESHAPE
	glutInitWindowPosition(0, 0);

	glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
		
	int MAINWINDOW = glutCreateWindow("mainwindow"); 
	
	//glutFullScreen(); // ПОКА НЕТ RESHAPE
	
	glutSetWindowTitle("TTITLE");

	switch (shape) {
		case SHAPE_CONE: {

			glutDisplayFunc(vvis::visualization::display_cone);

			glutKeyboardFunc(vvis::visualization::normal_keys);
			glutSpecialFunc(vvis::visualization::special_keys);

			//glutReshapeFunc(vvis::visualization::myReshape); doesnt work

			glutMainLoop();
		} break;

		default: {
			glutDisplayFunc(vvis::visualization::display_nothing);

			glutMainLoop();
		}
	}

	
	//glutIdleFunc(display);
	
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