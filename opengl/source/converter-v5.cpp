#include "./include/parser-converter/converter-v5.hpp"



// formatted string: NUMBER?COUNT?x;y;z;sx;sy;sz!x;y;z;sx;sy;sz!
bool vampire5::converter::convert(std::string& formatted_str) {

	//std::string vampire5::parser::get_spin_file_name(const int& number) {
	//	std::string num = std::to_string(number); std::string base = "00000000";
	//	for (int i = 0; num.length() != 0; ++i, num.pop_back()) {
	//		base[base.length() - 1 - i] = num[num.length() - 1];
	//	};
	//	return std::string("spins-" + base);
	//} это из парсера



	return true;
}


std::string vampire5::converter::get_number_of_file_from_f_str(std::string& f_str, int& index) {
	return std::string();
}

std::string vampire5::converter::get_count_from_f_str(std::string& f_str, int& index) {
	return std::string();
}

std::string vampire5::converter::get_output_str(std::string& f_str, int& index) {
	return std::string();
}

std::string vampire5::converter::get_spin_file_name(std::string& number) {
	return std::string();
}
