#include "./include/parser-converter/converter-v5.hpp"
#include "./include/parser-converter/parser-v5.hpp"
#include "./include/sample/creator_of_vertex_arr.hpp"

#include "./libraries/freeglut/include/GL/freeglut.h"
#include "./libraries/tia-Exceptio/include/assert.hpp"

#include "./include/defines.hpp"

#include "./include/sample/shape.hpp"
#include "./include/sample/drawing_shape_opengl.hpp"

#include <iostream>
#include <ctime>

// TODO: слой первый или второй  а материал?
// TODO: нет проверок соответствует ли количество строк тому, что написано в начале файла
// TODO: добавить комментарии а то с индексом уже запутался

// TODO: сделать вектор из Cone из Vertex : функцию для этого, чтобы при рисовании не создавать новых конусов
// TODO: может также сделать и с Point? из Vertex : функция для вычленения

// TODO: что насчёт Assert? кажется, мы забыли про них

// TODO: reshape функция
// разбираться с ней стоит после того, как разберёмся с камерой и движениями


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


			vvis::visualization::main_glut(argc, argv, vect, SHAPE_CONE, true, DRAW_ALL);

			system("pause");
		};




		system("pause");
	}
	catch (Exceptio& E) {
		_wsetlocale(LC_ALL, L".UTF-8");
		std::wcout << E.get_description() << L"   " << E.get_comment();
	}
	return 0;
}