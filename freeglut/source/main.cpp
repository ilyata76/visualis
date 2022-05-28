

#include "./include/main_inter.hpp"

// TODO: нет проверок соответствует ли количество строк тому, что написано в начале файла
// TODO: добавить комментарии а то с индексом уже запутался

// TODO: сделать вектор из Cone из Vertex : функцию для этого, чтобы при рисовании не создавать новых конусов
// тогда в Cone нужен геттер вертекса
// TODO: может также сделать и с Point? из Vertex : функция для вычленения

// TODO: что насчёт Assert? кажется, мы забыли про них

// TODO: class app

// TODO: draw не полиморфна

// TODO: функция проверки, существуют ли уже конвертированные файлы
// флаг -convert -force


int main(int argc, char** argv) {
	try {
		_wsetlocale(LC_ALL, L"");
		
		print_visualis_logo();
		
		interpertator_loop(argc, argv);
		

		
		std::wstring path(L""); int index = 0;
		std::wcout << prompt <<L"Введите путь ДО ПАПКИ: "; std::wcin >> path;
		//path = L"../temp/b";
		std::wcout << L"Введите номер файла: "; std::wcin >> index;
		//index = 30;
		
		// не забываем про get_file_name и проверять всё можно здесь

		std::wcout << L"Парсим файл...\n";
		std::wstring fstr = vampire5::parser::get_string(path)(index);
		std::wcout << L"Конвертируем...\n";
		bool converted = vampire5::converter::convert(fstr, path);

		if (converted) {
			std::wcout << L"Читаем файл...\n";
			std::vector <vvis::creator::Vertex> vect = vvis::creator::create_arry(path)(index);
			std::wcout << L"Количество загруженных спинов: " << vect.size() << '\n';

			vvis::visualization::app_freeglut app(vect, SHAPE_CONE, true, DRAW_ALL);
			
			vvis::visualization::draw_sample(app, argc, argv);

			std::wstring asker = L"";
			std::wcout << "Do you want to repeat? (y, n) >> "; std::wcin >> asker;
			if (asker == L"y") return main(argc, argv);
		};

	}
	catch (Exceptio& E) {
		_wsetlocale(LC_ALL, L"");
		std::wcout << E.get_description() << L"   " << E.get_comment();
		return E.get_index();
	}
	

	return 0;
}





