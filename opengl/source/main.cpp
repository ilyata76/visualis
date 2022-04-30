#include "./include/parser-converter/converter-v5.hpp"
#include "./include/parser-converter/parser-v5.hpp"

#include <iostream>


// TODO: exceptio просто компилируется вместе с проектом, но она простая
// однако хочется, чтобы не нужно было прописывать всё вручную - со сложными библиотеками будет затруднительнее это делать

int main(int argc, char* argv) {
	try {

		std::string a = "../temp";
		//std::cout << vampire5::parser::get_count("");


		auto abobus = vampire5::parser::get_string(a);
		std::cout << abobus(1);



	}
	catch (Exceptio& E) {

	}
	return 0;
}