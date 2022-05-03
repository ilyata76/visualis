#include "./include/parser-converter/converter-v5.hpp"
#include "./include/parser-converter/parser-v5.hpp"
#include "./include/sample/creator_of_vertex_arr.hpp"

#include "./libraries/freeglut/include/GL/freeglut.h"
#include "./libraries/tia-Exceptio/include/assert.hpp"

#include "./include/sample/shape.hpp"

#include <iostream>
#include <ctime>

// TODO: слой первый или второй  а материал?
// TODO: нет проверок соответствует ли количество строк тому, что написано в начале файла
// TODO: добавить комментарии а то с индексом уже запутался


void display() {
	glClearColor(1, 1, 1, 0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glPushMatrix();
	
	glRotatef(-90, 1, 0, 0); // представление второе (по часовой стрелке)
	

	vvis::creator::Vertex A(vvis::creator::Point(1, 1, 1), vvis::creator::Spin(1,1,-1));

	vvis::visualization::Cone B(A);
	B.set_draw_configuration();
	B.draw(0.05, 0.5, 200, 200, vvis::visualization::VvisColor_3f(0, 1, 0)/*vvis::visualization::get_color_by_direction(0.1, 1, 0.9)*/);
	//glTranslatef(0.1, 0, 0); 	B.draw(0.05, 0.5, 200, 200, vvis::visualization::VvisColor_3f(0, 1, 0));
	//glTranslatef(0, 0.1, 0); 	B.draw(0.05, 0.5, 200, 200, vvis::visualization::VvisColor_3f(0, 0, 1));
	//glTranslatef(0, 0, 0.3); B.draw(0.05, 0.5, 200, 200, vvis::visualization::VvisColor_3f(0, 0, 0));

	glPopMatrix();
	glutSwapBuffers();
}


int main(int argc, char** argv) {
	try {
		glutInitWindowSize(500, 250);
		glutInitWindowPosition(140, 140);
		glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
		glutInit(&argc, argv);
		int MAINWINDOW = glutCreateWindow("mainwindow");
		glutSetWindowTitle("TTITLE");
		glutDisplayFunc(display);
		//glutIdleFunc(display);
		glutMainLoop();
		system("pause");

	}
	catch (Exceptio& E) {
		_wsetlocale(LC_ALL, L".UTF-8");
		std::wcout << E.get_description() << L"   " << E.get_comment();
	}
	return 0;
}