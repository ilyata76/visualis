#include "./include/parser-converter/converter-v5.hpp"

#include <iostream>

// formatted string: NUMBER?COUNT?x;y;z;sx;sy;sz!x;y;z;sx;sy;sz!
bool vampire5::converter::convert(const std::string& formatted_str, int& index) {

	std::cout << formatted_str << std::endl;
	std::string number = vampire5::converter::get_number_of_file_from_f_str(formatted_str, index);
	std::cout << number << std::endl;
	std::cout << vampire5::converter::get_spin_file_name(number) << std::endl;
	std::cout << vampire5::converter::get_count_from_f_str(formatted_str, index) << '\n';
	std::cout << vampire5::converter::get_output_str(formatted_str, index) << '\n';
	std::cout << vampire5::converter::get_output_str(formatted_str, index) << '\n';
	std::cout << index;

	return true;
}


std::string vampire5::converter::get_number_of_file_from_f_str(const std::string& f_str, int& index) {
	std::string out;
	for (int i = index; f_str[i] != PLUG_3; ++i, ++index) {
		out.push_back(f_str[i]);
	} ++index;
	return out;
}

std::string vampire5::converter::get_count_from_f_str(const std::string& f_str, int& index) {
	std::string out;
	for (int i = index; f_str[i] != PLUG_3; ++i, ++index) {
		out.push_back(f_str[i]);
	} ++index;
	return out;
}

std::string vampire5::converter::get_output_str(const std::string& f_str, int& index) {
	std::string out;
	for (int i = index; f_str[i] != PLUG_2; ++i, ++index) {
		out.push_back(f_str[i]);
	} ++index;
	std::replace(out.begin(), out.end(), PLUG_1, '\t');
	return out;
}

std::string vampire5::converter::get_spin_file_name(const std::string& number) {

	std::string num = number;
	std::string base = BASE_NUMBER_OF_FILE_V5;

	for (int i = 0; num.length() != 0; ++i, num.pop_back()) {
		base[base.length() - 1 - i] = num[num.length() - 1];
	};

	return std::string("spins-" + base);
}
