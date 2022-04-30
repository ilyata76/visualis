#include "./include/parser-converter/converter-v5.hpp"



// formatted string: NUMBER?COUNT?x;y;z;sx;sy;sz!x;y;z;sx;sy;sz!
bool vampire5::converter::convert(const std::string& formatted_str, const std::string& path_to_folder, int& index) {

	std::fstream output;

	std::string number = vampire5::converter::get_number_of_file_from_f_str(formatted_str, index);
	std::string filename = vampire5::converter::get_file_name(number);
	std::string count = vampire5::converter::get_count_from_f_str(formatted_str, index);

	output.open(path_to_folder + "/" + filename + FORMAT_OF_OUR_FILE, std::ios_base::out | std::ios_base::trunc);

	output << COMMENT_OF_OUT_FILE << '\t' << "number" << '\t' << "count" << '\n';
	output <<						 '\t' <<  number  << '\t' <<  count  << '\n';
	output << COMMENT_OF_OUT_FILE << "M" << '\t' << "L" << '\t' << "X" << '\t' << "Y" << '\t' << "Z" << '\t' << "SX" << '\t' << "SY" << '\t' << "SZ" << '\n';
	

	while (index < formatted_str.length()) {
		output << vampire5::converter::get_output_str(formatted_str, index) << '\n';
	} output << std::flush;

	return true;
}


std::string vampire5::converter::get_number_of_file_from_f_str(const std::string& f_str, int& index) {
	Assert(f_str != "\0", 201, "Передана пустая строка в get_number", "Assert. ФУНКЦИЯ: vampire5::converter::get_number_of_file_from_f_str");
	//Assert(index < f_str.length(), 201, "index превзошёл длину строки", "Assert. ФУНКЦИЯ: vampire5::converter::get_number_of_file_from_f_str");
	std::string out;
	for (int i = index; f_str[i] != PLUG_3; ++i, ++index) {
		out.push_back(f_str[i]);
	} ++index;
	return out;
}

std::string vampire5::converter::get_count_from_f_str(const std::string& f_str, int& index) {
	Assert(f_str != "\0", 201,"Передана пустая строка в get_count", "Assert. ФУНКЦИЯ: vampire5::converter::get_count_from_f_str");
	//Assert(index < f_str.length(), 201, "index превзошёл длину строки", "Assert. ФУНКЦИЯ: vampire5::converter::get_count_from_f_str");
	std::string out;
	for (int i = index; f_str[i] != PLUG_3; ++i, ++index) {
		out.push_back(f_str[i]);
	} ++index;
	return out;
}

std::string vampire5::converter::get_output_str(const std::string& f_str, int& index) {
	Assert(f_str != "\0", 201,"Передана пустая строка в get_out", "Assert. ФУНКЦИЯ: vampire5::converter::get_output_str");
	//Assert(index < f_str.length(), 201, "index превзошёл длину строки", "Assert. ФУНКЦИЯ: vampire5::converter::get_output_str");
	std::string out;
	for (int i = index; f_str[i] != PLUG_2; ++i, ++index) {
		out.push_back(f_str[i]);
	} ++index;
	std::replace(out.begin(), out.end(), PLUG_1, '\t');
	return out;
}

std::string vampire5::converter::get_file_name(const std::string& number) {
	Assert(number != "\0", 201,"Передана пустая строка number в get_file_name spin-xxx", "Assert. ФУНКЦИЯ: vampire5::converter::get_spin_file_name");
	std::string num = number;
	std::string base = BASE_NUMBER_OF_FILE_V5;

	for (int i = 0; num.length() != 0; ++i, num.pop_back()) {
		base[base.length() - 1 - i] = num[num.length() - 1];
	};

	return std::string(START_OF_OUR_FILE + base);
}
