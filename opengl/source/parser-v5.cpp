#include "./include/parser-converter/parser-v5.hpp"



int vampire5::parser::get_count(const std::string& path_to_file) {
	// количество прописывается в первой строке файла

	std::fstream file; std::string out = "";
	
	file.open(path_to_file, std::ios_base::in);
	
	std::getline(file, out, '\n');

	file.close();

	return int(std::stoi(out));
}

int vampire5::parser::get_count(const char* path_to_file) {
	// количество прописывается в первой строке файла

	std::fstream file; std::string out = "";

	file.open(path_to_file, std::ios_base::in);

	std::getline(file, out, '\n');

	file.close();

	return int(std::stoi(out));
}

////////////////////////////////////////////////////////////

std::string path_to_folder = "";

std::string vampire5::parser::get_spin_file_name(const int& number) {
	std::string num = std::to_string(number); std::string base = "00000000";
	for (int i = 0; num.length() != 0; ++i, num.pop_back()) {
		base[base.length() - 1 - i] = num[num.length() - 1];
	};
	return std::string("spins-" + base);
}




std::string vampire5::parser::get_out(const int& number) {

	// здесь уже проверено наличие atoms_file
	// осталось проверить наличие спиновых

	std::fstream atoms_file;
	std::fstream spins_file;
	
	std::string name_of_atoms_file = "atoms-coords";
	std::string name_of_spins_file = get_spin_file_name(number);
	
	std::string str1 = "str1";
	std::string str2 = "str2";

	atoms_file.open(path_to_folder + "/" + name_of_atoms_file + ".data", std::ios_base::in);
	spins_file.open(path_to_folder + "/" + name_of_spins_file + ".data", std::ios_base::in);

	std::getline(atoms_file, str1, '\n');
	std::getline(spins_file, str2, '\n');

	// проверка

	Assert(1 != 1, "aboba");

	std::string format_string = std::to_string(number) + "?" + str1 + "?";

	// далее цикл по сборке строки

	while (!atoms_file.eof() && !spins_file.eof()) {
		
		std::getline(atoms_file, str1, '\n');
		std::getline(spins_file, str2, '\n');

		if (str1 == "\n" || str1 == "\0") break;
		if (str2 == "\n" || str2 == "\0") break;


		std::replace(str1.begin(), str1.end(), '\t', ';');
		std::replace(str2.begin(), str2.end(), '\t', ';');
		
		str2.push_back('!');
		//str2.push_back('\n');
		
		format_string += str1 + ';';
		format_string += str2;
	}



	return format_string;
}

vampire5::parser::FUNCTION_STRING_CONSTINTL vampire5::parser::get_string(const std::string& p_t_folder) {
	path_to_folder = p_t_folder;
	// проверка на наличие файлов atoms data atoms meta
	return vampire5::parser::get_out;
}

////////////////////////////////////////////////////////////