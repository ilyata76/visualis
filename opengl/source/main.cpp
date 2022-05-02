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
	
	//glColor3f(0, 0, 0);
	//glRotatef(90, 0, 1, 0);
	//glRotatef(90, 0, 0, 1);
	//glRotatef(90, 0, 1, 0);
	//glutSolidCone(0.05, 0.5, 200, 200);
	//glRotatef(-90, 0, 1, 0);
	//glRotatef(-90, 0, 0, 1);
	//glRotatef(-90, 0, 1, 0);
	//glTranslatef(0.1, 0, 0);
	//glRotatef(-90, 0, 1, 0);
	//glRotatef(-90, 0, 0, 1);
	//glRotatef(-90, 0, 1, 0);
	//glutSolidCone(0.05, 0.5, 10, 10);

	vvis::creator::Vertex A(vvis::creator::Point(1, 1, 1), vvis::creator::Spin(1, 1, 1));
	vvis::visualization::Cone B(A);
	B.draw(0.05, 0.5, 200, 200, vvis::visualization::VvisColor_3f());

	glPopMatrix();
	glutSwapBuffers();
}


// Shape
// виртуальный метод set_draw_configurations() БЕЗ ПАРАМЕТРОВ
// будет виртуальный метод draw() БЕЗ ПАРАМЕТРОВ. он уже рисует фигуру ОН ПРОСТО ВЫЗЫВАЕТ ФУНКЦИЮ GLUT
// для каждой фигуры будет ещё дополнительные метод draw(ПАРАМЕТРЫ). он уже рисует фигуру по параметрам
//		для каждой фигуры они будут разные, когда draw - стандартизированно (стандарты будут в defines)

// виртуальный метод string info() просто будет давать что это за фигура
//	можно будет потом это использовать в ветвлении

// char/int info() даст возможность в switch-case

// всё брехня
// функция draw() возращает ФУНКЦИЮ КОТОРАЯ БУДЕТ РИСОВАТЬ ПОТОМ ПО ПАРАМЕТРАМ
// ТО ЕСТЬ A.draw()(ПАРАМЕТРЫ)

// это тоже не сработает потому что они должны совпадать по возвращаемому значению
// тогда у каждой будет только свой draw отдельный
// а виртуального не будет
// но пусть возвращает функцию это веселее

// shape содежрит в себе vertex
// наследники содержат в себе доп. поля которые помогут рисовать например углы
// они будут определяться через get_draw_confi..()

// это кстати надо будет проверить сможет ли glut вызывать функцию из другого файла вообще где он не инициализирован

// А ВСЕ ОСТАЛЬНЫЕ ОПЕРАЦИИ ЭТО УЖЕ НЕ ПРЕРОГАТИВА КЛАССА
// в общем задача - это класс который может собрать свою конфигурацию чтобы потом отрисовать фигуру

// в других классах из дргухи файлов - РИСУЕТ!


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