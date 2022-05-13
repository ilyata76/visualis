#include "./include/parser-converter/parser-v5.hpp"

////////////////////////////////////////////////////////////
//			ПОЛУЧЕНИЕ КОЛИЧЕСТВА СТРОК В ФАЙЛЕ
////////////////////////////////////////////////////////////

int vampire5::parser::get_count(const std::wstring& path_to_file) {
	// количество прописывается в первой строке файла
	// TODO: не хватает проверки на int

	std::wfstream file; std::wstring out = L"";
	
	file.open(path_to_file, std::ios_base::in);
	
	std::getline(file, out, L'\n');

	file.close();

	return int(std::stoi(out));
}

int vampire5::parser::get_count(const wchar_t* path_to_file) {
	// количество прописывается в первой строке файла
	// TODO: не хватает проверки на целочисленность

	std::wfstream file; std::wstring out = L"";

	file.open(path_to_file, std::ios_base::in);

	std::getline(file, out, L'\n');

	file.close();

	return int(std::stoi(out));
}

////////////////////////////////////////////////////////////
//			ПОЛУЧЕНИЕ ФОРМАТИРОВАННОЙ СТРОКИ
////////////////////////////////////////////////////////////

std::wstring path_to_folder = L"";

std::wstring vampire5::parser::get_spin_file_name(const int& number) {
	std::wstring num = std::to_wstring(number); std::wstring base = BASE_NUMBER_OF_FILE_V5;
	size_t num_lenght = num.length(); size_t base_lenght = base.length();
	for (int i = 0; num_lenght != 0; ++i, num.pop_back(), num_lenght = num.length()) {
		base[base_lenght - 1 - i] = num[num_lenght - 1];
	};
	return std::wstring(START_OF_SPINS_NAME_FILE_V5 + base);
}

std::wstring vampire5::parser::get_out(const int& number) {

	std::wstring name_of_atoms_file = NAME_OF_ATOMS_FILE_V5;
	std::wstring name_of_spins_file = vampire5::parser::get_spin_file_name(number);
	
	std::wfstream atoms_file;
	std::wfstream spins_file;

	atoms_file.open(path_to_folder + L"/" + name_of_atoms_file + FORMAT_OF_ATOMS_FILE_V5, std::ios_base::in);
	spins_file.open(path_to_folder + L"/" + name_of_spins_file + FORMAT_OF_SPINS_FILE_V5, std::ios_base::in);

	Assert(atoms_file.is_open(), 101, L"atoms_file не открылся", L"Assert. ФУНКЦИЯ: vampire5::parser::get_out");

	std::wstring desc = name_of_spins_file + L" не открылся";
	std::wstring comm = L"Assert. ФУНКЦИЯ: vampire5::parser::get_out";
	Assert(spins_file.is_open(), 111, desc, comm);
	
	std::wstring str1 = L"str1";
	std::wstring str2 = L"str2";

	std::getline(atoms_file, str1, L'\n');
	std::getline(spins_file, str2, L'\n');

	// TODO: не хватает проверки на целочисленность

	Assert( std::stoi(str1) == std::stoi(str2), 102, L"str1 != str2, разное количество строк в файлах", 
											   L"Assert. Проверьте первую строку обоих файлов. ФУНКЦИЯ: vampire5::parser::get_out" );

	
	std::wstring format_string;
	format_string.reserve( sizeof(std::to_wstring(number) + PLUG_3 + str1 + PLUG_3) + sizeof(char) * 9 * number + sizeof(PLUG_2)*number + sizeof(char)*5*number);
	format_string += std::to_wstring(number) + PLUG_3 + str1 + PLUG_3;

	// далее цикл по сборке строки

	while (!atoms_file.eof() && !spins_file.eof()) {
		
		std::getline(atoms_file, str1, L'\n');
		std::getline(spins_file, str2, L'\n');

		if (str1 == L"\n" || str1 == L"\0") continue;
		if (str2 == L"\n" || str2 == L"\0") continue;

		std::replace(str1.begin(), str1.end(), L'\t', PLUG_1);
		std::replace(str2.begin(), str2.end(), L'\t', PLUG_1);
		
		str2.push_back(PLUG_2);
		
		format_string += str1 + PLUG_1;
		format_string += str2;
	}

	atoms_file.close();
	spins_file.close();
	

	return format_string;
}

vampire5::parser::FUNCTION_STRING_CONSTINTL vampire5::parser::get_string(const std::wstring& p_t_folder) {
	path_to_folder = p_t_folder;
	return vampire5::parser::get_out;
}

////////////////////////////////////////////////////////////