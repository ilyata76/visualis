#include "./include/parser-converter/parser-v5.hpp"

////////////////////////////////////////////////////////////
//			ПОЛУЧЕНИЕ КОЛИЧЕСТВА СТРОК В ФАЙЛЕ
////////////////////////////////////////////////////////////

int vampire5::parser::get_count(const std::string& path_to_file) {
	// количество прописывается в первой строке файла
	// TODO: не хватает проверки на int

	std::fstream file; std::string out = "";
	
	file.open(path_to_file, std::ios_base::in);
	
	std::getline(file, out, '\n');

	file.close();

	return int(std::stoi(out));
}

int vampire5::parser::get_count(const char* path_to_file) {
	// количество прописывается в первой строке файла
	// TODO: не хватает проверки на целочисленность

	std::fstream file; std::string out = "";

	file.open(path_to_file, std::ios_base::in);

	std::getline(file, out, '\n');

	file.close();

	return int(std::stoi(out));
}

////////////////////////////////////////////////////////////
//			ПОЛУЧЕНИЕ ФОРМАТИРОВАННОЙ СТРОКИ
////////////////////////////////////////////////////////////

std::string path_to_folder = "";

std::string vampire5::parser::get_spin_file_name(const int& number) {
	std::string num = std::to_string(number); std::string base = BASE_NUMBER_OF_FILE_V5;
	for (int i = 0; num.length() != 0; ++i, num.pop_back()) {
		base[base.length() - 1 - i] = num[num.length() - 1];
	};
	return std::string(START_OF_SPINS_NAME_FILE_V5 + base);
}

std::string vampire5::parser::get_out(const int& number) {

	std::string name_of_atoms_file = NAME_OF_ATOMS_FILE_V5;
	std::string name_of_spins_file = get_spin_file_name(number);
	
	std::fstream atoms_file;
	std::fstream spins_file;

	atoms_file.open(path_to_folder + "/" + name_of_atoms_file + FORMAT_OF_ATOMS_FILE_V5, std::ios_base::in);
	spins_file.open(path_to_folder + "/" + name_of_spins_file + FORMAT_OF_SPINS_FILE_V5, std::ios_base::in);

	Assert(atoms_file.is_open(), 101, "atoms_file не открылся");
	Assert(spins_file.is_open(), 101, "spins_file не открылся");
	
	std::string str1 = "str1";
	std::string str2 = "str2";

	std::getline(atoms_file, str1, '\n');
	std::getline(spins_file, str2, '\n');

	// TODO: не хватает проверки на целочисленность

	Assert( std::stoi(str1) == std::stoi(str2), 102, "str1 != str2, разное количество строк в файлах", 
											   "Assert. Проверьте первую строку обоих файлов" );

	std::string format_string = std::to_string(number) + PLUG_3 + str1 + PLUG_3;

	// далее цикл по сборке строки

	while (!atoms_file.eof() && !spins_file.eof()) {
		
		std::getline(atoms_file, str1, '\n');
		std::getline(spins_file, str2, '\n');

		if (str1 == "\n" || str1 == "\0") continue;
		if (str2 == "\n" || str2 == "\0") continue;

		std::replace(str1.begin(), str1.end(), '\t', PLUG_1);
		std::replace(str2.begin(), str2.end(), '\t', PLUG_1);
		
		str2.push_back(PLUG_2);
		
		format_string += str1 + PLUG_1;
		format_string += str2;
	}

	atoms_file.close();
	spins_file.close();
	

	return format_string;
}

vampire5::parser::FUNCTION_STRING_CONSTINTL vampire5::parser::get_string(const std::string& p_t_folder) {
	path_to_folder = p_t_folder;
	return vampire5::parser::get_out;
}

////////////////////////////////////////////////////////////