#include "./include/parser-converter/parser-v5.hpp"
#include "./include/parser-converter/converter-v5.hpp"

#include "./include/sample/creator_of_vertex_arr.hpp"
#include "./include/sample/drawing_shape_opengl.hpp"

#include <iostream>


int main(int argc, char** argv) {
	try {
		_wsetlocale(LC_ALL, L".UTF-8");
		std::wstring path(L""); int index = 0;
		std::wcout << L"Введите путь ДО ПАПКИ: "; std::wcin >> path; std::wcout << L'\n';
		std::wcout << L"Введите номер файла: "; std::wcin >> index; std::wcout << L'\n';
		
		std::wcout << L"Парсим файл...\n";
		std::wstring fstr = vampire5::parser::get_string(path)(index);
		std::wcout << L"Конвертируем...\n";
		bool converted = vampire5::converter::convert(fstr, path);

		if (converted) {
			std::wcout << L"Читаем файл...\n";
			std::vector <vvis::creator::Vertex> vect = vvis::creator::create_arry(path)(index);
			std::wcout << L"Количество загруженных спинов: " << vect.size() << '\n';
			vvis::visualization::main_glut(argc, argv, vect, SHAPE_CONE, true, DRAW_ALL);
		};
		system("pause");
	}
	catch (Exceptio& E) {
		_wsetlocale(LC_ALL, L".UTF-8");
		std::wcout << E.get_description() << L"   " << E.get_comment();
	}
	return 0;
}