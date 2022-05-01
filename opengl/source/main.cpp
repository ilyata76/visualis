#include "./include/parser-converter/converter-v5.hpp"
#include "./include/parser-converter/parser-v5.hpp"
#include "include/sample/point-spin.hpp"
#include "include/sample/creator_of_vertex_arr.hpp"

#include "libraries/freeglut/include/GL/freeglut.h"

#include <iostream>
#include <ctime>

// TODO: слой первый или второй  а материал?
// TODO: нет проверок соответствует ли количество строк тому, что написано в начале файла
// TODO: добавить комментарии а то с индексом уже запутался

int main(int argc, char** argv) {
	try {
		//
	}
	catch (Exceptio& E) {
		_wsetlocale(LC_ALL, L".UTF-8"); // !!! ГДЕ ВЫ БЫЛИ РАНЬШЕ С ВАШИМ .UTF-8

		std::wcout << E.get_description() << L"   " << E.get_comment();
	}
	return 0;
}