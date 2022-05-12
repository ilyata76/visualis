#include "./include/parser-converter/parser-v5.hpp"
#include "./include/parser-converter/converter-v5.hpp"

#include "./include/sample/creator_of_vertex_arr.hpp"
#include "./include/sample/drawing_shape_opengl.hpp"

#include <iostream>

// TODO: слой первый или второй  а материал?
// TODO: нет проверок соответствует ли количество строк тому, что написано в начале файла
// TODO: добавить комментарии а то с индексом уже запутался

// TODO: сделать вектор из Cone из Vertex : функцию для этого, чтобы при рисовании не создавать новых конусов
// тогда в Cone нужен геттер вертекса
// TODO: может также сделать и с Point? из Vertex : функция для вычленения

// TODO: что насчёт Assert? кажется, мы забыли про них

// TODO: reshape функция
// разбираться с ней стоит после того, как разберёмся с камерой и движениями
// с камерой проблемы

// TODO: class app

// TODO: draw не полиморфна

int main(int argc, char** argv) {
	try {
		_wsetlocale(LC_ALL, L".UTF-8");
		std::wstring path(L""); int index = 0;
		//std::wcout << L"Введите путь ДО ПАПКИ: "; std::wcin >> path; std::wcout << L'\n';
		path = L"../temp/b";
		//std::wcout << L"Введите номер файла: "; std::wcin >> index; std::wcout << L'\n';
		index = 30;
		
		std::wcout << L"Парсим файл...\n";
		std::wstring fstr = vampire5::parser::get_string(path)(index);
		std::wcout << L"Конвертируем...\n";
		bool converted = vampire5::converter::convert(fstr, path);

		if (converted) {
			std::wcout << L"Читаем файл...\n";
			std::vector <vvis::creator::Vertex> vect = vvis::creator::create_arry(path)(index);
			std::wcout << L"Количество загруженных спинов: " << vect.size() << '\n';

			vvis::visualization::app_freeglut app(vect, SHAPE_NOTHING, true, DRAW_ALL);
			vvis::visualization::draw_sample(app, argc, argv);
		};
		system("pause");
	}
	catch (Exceptio& E) {
		_wsetlocale(LC_ALL, L".UTF-8");
		std::wcout << E.get_description() << L"   " << E.get_comment();
	}
	return 0;
}