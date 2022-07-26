#include "../include/tia/exceptio.hpp"

#include <iostream>

void output_line_with_exceptio(Exceptio& E) {
	if (checking_index_for_out(E)) 
		std::cout << E.get_index() << '\t';
	if (checking_description_for_out(E)) 
		std::cout << E.get_description() << '\t';
	if (checking_comment_for_out(E)) 
		std::cout << E.get_comment() << '\t';
	std::cout << std::endl;
}

int main(int argc, char** argv) {
	try {
		int numerator = 0; int denominator = 0;
		std::cout << "for integer division input the numerator: "; std::cin >> numerator;
		std::cout << "input the denominator: "; std::cin >> denominator;
		if (denominator == 0) throw Exceptio(1, "Division by zero!", "Change your denominator value next time");
		std::cout << (numerator / denominator);
	} catch (Exceptio& E) {
		std::cout << "-------- ERROR --------" << std::endl;
		output_line_with_exceptio(E);
		std::cout << "--------       --------" << std::endl;
	}
	return 0;
}