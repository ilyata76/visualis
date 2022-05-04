﻿#include "./include/parser-converter/converter-v5.hpp"
#include "./include/parser-converter/parser-v5.hpp"
#include "./include/sample/creator_of_vertex_arr.hpp"

#include "./libraries/freeglut/include/GL/freeglut.h"
#include "./libraries/tia-Exceptio/include/assert.hpp"

#include "./include/defines.hpp"

#include "./include/sample/shape.hpp"

#include <iostream>
#include <ctime>

// TODO: слой первый или второй  а материал?
// TODO: нет проверок соответствует ли количество строк тому, что написано в начале файла
// TODO: добавить комментарии а то с индексом уже запутался

// TODO: сделать вектор из Cone из Vertex : функцию для этого, чтобы при рисовании не создавать новых конусов
// TODO: может также сделать и с Point? из Vertex : функция для вычленения

// TODO: что насчёт Assert? кажется, мы забыли про них

//int index = 0;
//double dx = 0;
//double dy = 0;
//double dz = 0;
//std::vector <vvis::creator::Vertex> vect;
//int size = 0;
//double scale = 0.01 * 1.0e-9;

//double dist_min = 3.e-10;
//double dipole_head_length = scale * dist_min / 2.0;
//double dipole_head_radius = dipole_head_length / 4.0;

//void draw_spin(int& index) {
//	glPushMatrix();
//	glRotatef(-90, 1, 0, 0);
//	vvis::creator::Point p = vect[index].get_point();
//	dx = p.get(L'x'); dy = p.get(L'y'); dz = p.get(L'z');
//	vvis::visualization::Cone B(vect[index]);
//	
//	glTranslated(dx / 32, dy / 32, dz / 32);
//	
//	B.set_draw_configuration();
//
//	B.draw(0.005, 0.05, 10, 10, vvis::visualization::VvisColor_3f(0, 0, 0));
//	glPopMatrix();
//}

void display() {
	//index = 0;
	glClearColor(1, 1, 1, 0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	
	if (ROTATE_Z_FO_SECOND_REPRESENTATION) glRotatef(-90, 1, 0, 0);
	//for (index;index != size;++index)
	//	draw_spin(index);
	vvis::creator::Vertex A = vvis::creator::Vertex(vvis::creator::Point(0, 0, 0), vvis::creator::Spin(-1, 1, -1));
	vvis::visualization::Cone B(A);
	B.set_draw_configuration();
	B.draw(0.05, 0.5, 10, 10, vvis::visualization::get_color_by_direction(A.get_spin()));
	glutSwapBuffers();

}


int main(int argc, char** argv) {
	try {
		time_t current = time(0);
		//index = 0;
		std::wstring fstr = vampire5::parser::get_string(L"../temp")(31);
		time_t afterparser = time(0);
		bool converted = vampire5::converter::convert(fstr, L"../temp");
		time_t afterconverter = time(0);

		if (converted) {
			std::vector <vvis::creator::Vertex> vect = vvis::creator::create_arry(L"../temp")(31);
			time_t aftercreator = time(0);
			std::wcout << "START: " << current << '\n';
			std::wcout << "AFTER PARSING: " << afterparser << " " << afterparser - current << '\n';
			std::wcout << "AFTER CONVERTING: " << afterconverter << " " << afterconverter - afterparser << " " << afterconverter - current << '\n';
			std::wcout << "AFTER VERTEX CREATING: " << aftercreator << " " << aftercreator - afterconverter << " " << aftercreator - current << '\n';
			//std::wcout << L"ONE : " << vect[0].get_spin().get(L'x');
			//size = vect.size();
			//std::wcout << size;

			glutInitWindowSize(1800, 1000);
			glutInitWindowPosition(0, 0);
			glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
			glutInit(&argc, argv);
			int MAINWINDOW = glutCreateWindow("mainwindow");
			glutSetWindowTitle("TTITLE");
			glutDisplayFunc(display);
			//glutIdleFunc(display);
			glutMainLoop();
			system("pause");
		};





	}
	catch (Exceptio& E) {
		_wsetlocale(LC_ALL, L".UTF-8");
		std::wcout << E.get_description() << L"   " << E.get_comment();
	}
	return 0;
}