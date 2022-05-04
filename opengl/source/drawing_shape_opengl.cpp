#include "./include/sample/drawing_shape_opengl.hpp"

#include <iostream>
int glob_index = 0;
int glob_color = false;

std::vector<vvis::creator::Vertex> vrt_vctr;

void vvis::visualization::display_nothing() {
	// TODO: это работает, но я не знаю каким образом надо бы разобраться с матрицами и viewimport'ом
	// тоже кстати не с первого раза запустилась вопрос почему открытый
	glClearColor(1, 1, 1, 0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	gluOrtho2D(0, 1400, 0, 800);

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

void vvis::visualization::display_l() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	std::wcout << "И ГДЕ ТРЕУГОЛЬНИК?\n";
	glBegin(GL_TRIANGLES);
	glColor3f(1, 0, 0);
		glVertex3f(-0.5, -0.5, 0.0);
		glColor3f(0, 0, 1);
		glVertex3f(0.0, 0.5, 0.0);
		glColor3f(0, 1, 0);
		glVertex3f(0.5, -0.5, 0.0);
	glEnd();

	glutSwapBuffers();
}

void vvis::visualization::draw_cone_spin(int& index, bool color) {
	double x = vrt_vctr[glob_index].get_point().get(L'x');
	double y = vrt_vctr[glob_index].get_point().get(L'y');
	double z = vrt_vctr[glob_index].get_point().get(L'z');
	vvis::visualization::Cone my_cone(vrt_vctr[glob_index]);

	glPushMatrix();
	
	if (ROTATE_Z_FO_SECOND_REPRESENTATION) glRotatef(-90, 1, 0, 0);
	
	my_cone.set_draw_configuration();
	
	glTranslated(x / 32, y / 32, z / 32); // TODO: параметры скейлинга трансляции

	if (color == true) 
		my_cone.draw(0.005, 0.05, 10, 10, vvis::visualization::get_color_by_direction(vrt_vctr[glob_index].get_spin())); // TODO: параметры конуса
	else 
		my_cone.draw(0.005, 0.05, 10, 10, vvis::visualization::VvisColor_3f(0, 0, 0)); // TODO: параметры конуса

	glPopMatrix();
}

void vvis::visualization::display_cone() {
	glClearColor(1, 1, 1, 0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	
	if (glob_index == DRAW_ALL) {
		glob_index = 0;
		size_t size = vrt_vctr.size();
		for (glob_index; glob_index != size; ++glob_index) {
			draw_cone_spin(glob_index, glob_color);
		}
		glob_index = DRAW_ALL;
	} else {
		// TODO : проверка не больше ли чем размер
		draw_cone_spin(glob_index, glob_color);
	}
	
	glutSwapBuffers();
}

void vvis::visualization::main_glut(int argc, char** argv, std::vector<vvis::creator::Vertex>& vect, 
									wchar_t shape, bool color, int index) {
	
	vrt_vctr = vect;
	glob_index = index;
	glob_color = color;


	glutInit(&argc, argv);
	glutInitWindowSize(400, 400);
	glutInitWindowPosition(100, 100);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
	
	int MAINWINDOW = glutCreateWindow("mainwindow");
	glutSetWindowTitle("TTITLE");

	switch (shape) {
		case SHAPE_CONE: {
			glutDisplayFunc(vvis::visualization::display_cone);
			glutReshapeFunc(vvis::visualization::myReshape);
			glutMainLoop();
		} break;
		case L'l': {
			glutDisplayFunc(vvis::visualization::display_l);
			glutReshapeFunc(vvis::visualization::myReshape);
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

void vvis::visualization::myReshape(int w, int h) {

	// предупредим деление на ноль
	// если окно сильно перетянуто будет
	if (h == 0)
		h = 1;
	float ratio = 1.0 * w / h;
	std::wcout << w;
	// используем матрицу проекции
	glMatrixMode(GL_PROJECTION);

	// Reset матрицы
	glLoadIdentity();

	// определяем окно просмотра
	glViewport(0, 0, w, h);

	// установить корректную перспективу.

	// 0 do nothing
	//gluPerspective(45, ratio, 1, 1000);
	//gluLookAt(0, 0, 1, 0, 0, 0, 0, 1, 0);
	
	// ну конечно!!! http://dkhramov.dp.ua/Comp.GlutAndOpenGL#.YnMK7OrP2Uk ! мы просто ничего не видим


	glOrtho(0.0, w, h, 0.0, 0.0, 0.0);
	// и как это того этого?

	// https://docs.microsoft.com/en-us/windows/win32/opengl/glortho
	// https://stackoverflow.com/questions/2571402/how-to-use-glortho-in-opengl
	// https://ru.stackoverflow.com/questions/434277/glutreshapefunc-и-glutdisplayfunc-в-opengl

	// вернуться к модели
	glMatrixMode(GL_MODELVIEW);
}