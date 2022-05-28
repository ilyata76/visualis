

#include "./include/main_inter.hpp"

// TODO: нет проверок соответствует ли количество строк тому, что написано в начале файла
// TODO: добавить комментарии а то с индексом уже запутался

// TODO: сделать вектор из Cone из Vertex : функцию для этого, чтобы при рисовании не создавать новых конусов
// тогда в Cone нужен геттер вертекса
// может также сделать и с Point? из Vertex : функция для вычленения
// TODO: что насчёт Assert? кажется, мы забыли про них
// TODO: draw не полиморфна



Interpretator i; // TODO чтобы при ошибке не слетали параметры надо сделать файл с настройками?

int main(int argc, char** argv) {
	try {
		_wsetlocale(LC_ALL, L"");
		
		print_visualis_logo();
		
		i.loop(argc, argv);

	}
	catch (Exceptio& E) {
		_wsetlocale(LC_ALL, L"");
		std::wcout << L"\n" << E.get_description() << L"   " << E.get_comment() << L"\n" << std::endl;
		
		std::wstring asker = L"";
		do {
			std::wcout << "\nDo you want to repeat? (y/n) >> "; std::wcin >> asker;
			if (by_synonyms(asker) == L"yes") return main(argc, argv);
		} while (by_synonyms(asker) != L"no");
		return 1;
	}
	
	return 0;
}





