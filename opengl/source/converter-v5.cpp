#include "./include/parser-converter/converter-v5.hpp"


bool vampire5::converter::convert(const std::wstring& formatted_str, const std::wstring& path_to_folder, int index) {

	std::wfstream output;
	std::wstring number = vampire5::converter::get_number_of_file_from_f_str(formatted_str, index);
	std::wstring filename = vampire5::converter::get_file_name(number);
	std::wstring count = vampire5::converter::get_count_from_f_str(formatted_str, index);
	output.open(path_to_folder + L"/" + filename + FORMAT_OF_OUR_FILE, std::ios_base::out | std::ios_base::trunc);

	output << COMMENT_OF_OUR_FILE << L'\t' << L"number" << L'\t' << L"count" << L'\n';
	output <<						 L'\t' <<  number  << L'\t' <<  count  << L'\n';
	output << COMMENT_OF_OUR_FILE << L"M" << L'\t' << L"L" << L'\t' << L"X" << L'\t' << L"Y" << L'\t' << L"Z" << L'\t' << L"SX" << L'\t' << L"SY" << L'\t' << L"SZ" << L'\n';
	

	while (index < formatted_str.length()) {
		output << vampire5::converter::get_output_str(formatted_str, index) << '\n';
	} output << std::flush;
	
	output.close();

	return true;
}


std::wstring vampire5::converter::get_number_of_file_from_f_str(const std::wstring& f_str, int& index) {
	Assert(f_str != L"\0", 201, L"Передана пустая строка в get_number", L"Assert. ФУНКЦИЯ: vampire5::converter::get_number_of_file_from_f_str");
	//Assert(index < f_str.length(), 201, "index превзошёл длину строки", "Assert. ФУНКЦИЯ: vampire5::converter::get_number_of_file_from_f_str");
	std::wstring out;
	for (int i = index; f_str[i] != PLUG_3; ++i, ++index) {
		out.push_back(f_str[i]);
	} ++index;
	return out;
}

std::wstring vampire5::converter::get_count_from_f_str(const std::wstring& f_str, int& index) {
	Assert(f_str != L"\0", 201, L"Передана пустая строка в get_count", L"Assert. ФУНКЦИЯ: vampire5::converter::get_count_from_f_str");
	//Assert(index < f_str.length(), 201, "index превзошёл длину строки", "Assert. ФУНКЦИЯ: vampire5::converter::get_count_from_f_str");
	std::wstring out;
	for (int i = index; f_str[i] != PLUG_3; ++i, ++index) {
		out.push_back(f_str[i]);
	} ++index;
	return out;
}

std::wstring vampire5::converter::get_output_str(const std::wstring& f_str, int& index) {
	Assert(f_str != L"\0", 201, L"Передана пустая строка в get_out", L"Assert. ФУНКЦИЯ: vampire5::converter::get_output_str");
	//Assert(index < f_str.length(), 201, "index превзошёл длину строки", "Assert. ФУНКЦИЯ: vampire5::converter::get_output_str");
	std::wstring out;
	for (int i = index; f_str[i] != PLUG_2; ++i, ++index) {
		out.push_back(f_str[i]);
	} ++index;
	std::replace(out.begin(), out.end(), PLUG_1, L'\t');
	return out;
}

std::wstring vampire5::converter::get_file_name(const std::wstring& number) {
	Assert(number != L"\0", 201, L"Передана пустая строка number в get_file_name spin-xxx", L"Assert. ФУНКЦИЯ: vampire5::converter::get_spin_file_name");
	std::wstring num = number;
	std::wstring base = BASE_NUMBER_OF_FILE_V5;

	for (int i = 0; num.length() != 0; ++i, num.pop_back()) {
		base[base.length() - 1 - i] = num[num.length() - 1];
	};

	return std::wstring(START_OF_OUR_FILE + base);
}
