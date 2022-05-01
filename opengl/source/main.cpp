#include "./include/parser-converter/converter-v5.hpp"
#include "./include/parser-converter/parser-v5.hpp"
#include "include/sample/point-spin.hpp"
#include "include/sample/creator_of_vertex_arr.hpp"

#include "libraries/freeglut/include/GL/freeglut.h"

#include <iostream>
#include <ctime>

// TODO: слой первый или второй  а материал?
// TODO: нет проверок соответствует ли количество строк тому, что написано в начале файла

int main(int argc, char** argv) {
	try {
		//time_t aaa;
		//std::wcout << (aaa = std::time(0));
		//std::to_string(argv[0]); // <- для пути и вариаций
		//// флажки придумаем

		//// какой-нибудь понятный интерфейс флажков типа FILES:1,100 - от 1 до 100 файлы проверять будет
		//// visvamp convert <ывфадфывдплфвы>
		//// visvamp visualize <dasfkasdfl>
		//std::wstring a = L"../temp";
		//////std::cout << vampire5::parser::get_count("");
		//std::vector<vvis::creator::Vertex> A = vvis::creator::create_arry(a)(9);
		//using namespace vvis::creator;
		//std::wcout << A[2].get_point().get('x');

		//auto abobus = vampire5::parser::get_string(a);
		//std::wstring aa = abobus(9);
		//int index = 0;
		//vampire5::converter::convert(aa, a, index);
		//time_t bbb = aaa;
		//std::wcout << (bbb = std::time(0)) << L" " << bbb - aaa;
		//double aboba = 1.0;
		//vvis::creator::Point a(aboba, 2.0, 3.0);
		//std::wcout << a.get(L'x');
		//a.set(L'x', 1.1);
		//std::wcout << a.get(L'b');
		//vvis::creator::Spin ss(aboba, 2.0, 3.0);
		//std::wcout << ss.get(L'x');
		//std::wcout << ss.get(L"sx");
	}
	catch (Exceptio& E) {
		_wsetlocale(LC_ALL, L".UTF-8"); // !!! ГДЕ ВЫ БЫЛИ РАНЬШЕ С ВАШИМ .UTF-8

		std::wcout << E.get_description() << L"   " << E.get_comment();
	}
	return 0;
}