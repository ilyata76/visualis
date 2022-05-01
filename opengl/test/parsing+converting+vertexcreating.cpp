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
		time_t current = time(0);
		std::wstring a = L"../temp";
		int index = 9;
		std::wstring str = vampire5::parser::get_string(a)(index);
		time_t afterparser = time(0);
		int nol = 0;
		bool created = vampire5::converter::convert(str, a);
		time_t afterconverter = time(0);
		std::vector<vvis::creator::Vertex> A = vvis::creator::create_arry(a)(index);
		time_t aftercreator = time(0);

		std::wcout << "START: " << current << '\n';
		std::wcout << "AFTER PARSING: " << afterparser << " " << afterparser - current << '\n';
		std::wcout << "AFTER CONVERTING: " << afterconverter << " " << afterconverter - afterparser << " " << afterconverter - current << '\n';
		std::wcout << "AFTER VERTEX CREATING: " << aftercreator << " " << aftercreator - afterconverter << " " << aftercreator - current << '\n';
		std::wcout << A[100000].get_point().get('x') << '\n';
		std::wcout << time(0);
	}
	catch (Exceptio& E) {
		_wsetlocale(LC_ALL, L".UTF-8"); // !!! ГДЕ ВЫ БЫЛИ РАНЬШЕ С ВАШИМ .UTF-8

		std::wcout << E.get_description() << L"   " << E.get_comment();
	}
	return 0;
}