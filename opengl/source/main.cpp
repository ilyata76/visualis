#include "./include/parser-converter/converter-v5.hpp"
#include "./include/parser-converter/parser-v5.hpp"

#include <iostream>
#include <ctime>

// TODO: слой первый или второй  а материал?

int main(int argc, char* argv) {
	try {
		//time_t aaa;
		//std::wcout << (aaa = std::time(0));
		//std::to_string(argv[0]); // <- для пути и вариаций
		//// флажки придумаем

		//// какой-нибудь понятный интерфейс флажков типа FILES:1,100 - от 1 до 100 файлы проверять будет
		//// visvamp convert <ывфадфывдплфвы>
		//// visvamp visualize <dasfkasdfl>
		//std::wstring a = L"../temp";
		////std::cout << vampire5::parser::get_count("");


		//auto abobus = vampire5::parser::get_string(a);
		//std::wstring aa = abobus(9);
		//int index = 0;
		//vampire5::converter::convert(aa, a, index);
		//time_t bbb = aaa;
		//std::wcout << (bbb = std::time(0)) << L" " << bbb - aaa;

	}
	catch (Exceptio& E) {
		std::wcout << E.get_description() << "\t" << E.get_comment();
	}
	return 0;
}