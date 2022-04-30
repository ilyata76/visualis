#include "../include/tia/assert.hpp"

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
		Assert((1 < 0), 1, "1 less 0? i guess not");
	}
	catch (Exceptio& E) {
		std::cout << "-------- ERROR --------" << std::endl;
		output_line_with_exceptio(E);
		std::cout << "--------       --------" << std::endl;
	}
	return 0;
}