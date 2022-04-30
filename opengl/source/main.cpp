#include "./include/parser-converter/converter-v5.hpp"
#include "./include/parser-converter/parser-v5.hpp"

#include <iostream>


int main(int argc, char* argv) {
	try {
		std::to_string(argv[0]); // <- для пути и вариаций
		// флажки придумаем
		std::string a = "../temp";
		//std::cout << vampire5::parser::get_count("");


		auto abobus = vampire5::parser::get_string(a);
		std::string aa = abobus(1);
		int index = 0;
		vampire5::converter::convert(aa, index);



	}
	catch (Exceptio& E) {
		std::cout << E.get_description();
	}
	return 0;
}