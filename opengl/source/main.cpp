#include "./include/parser-converter/converter-v5.hpp"
#include "./include/parser-converter/parser-v5.hpp"
#include "./include/sample/creator_of_vertex_arr.hpp"

#include "./libraries/freeglut/include/GL/freeglut.h"
#include "./libraries/tia-Exceptio/include/assert.hpp"

#include <iostream>
#include <ctime>

// TODO: слой первый или второй  а материал?
// TODO: нет проверок соответствует ли количество строк тому, что написано в начале файла
// TODO: добавить комментарии а то с индексом уже запутался


void display() {
	glClearColor(1, 1, 1, 0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glPushMatrix();
	
	glColor3f(0, 0, 0);
	glRotatef(90, 0, 1, 0);
	glRotatef(90, 0, 0, 1);
	glRotatef(90, 0, 1, 0);
	glutSolidCone(0.05, 0.5, 10, 10);
	glRotatef(-90, 0, 1, 0);
	glRotatef(-90, 0, 0, 1);
	glRotatef(-90, 0, 1, 0);
	glTranslatef(0.1, 0, 0);
	glRotatef(-90, 0, 1, 0);
	glRotatef(-90, 0, 0, 1);
	glRotatef(-90, 0, 1, 0);
	glutSolidCone(0.05, 0.5, 10, 10);
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