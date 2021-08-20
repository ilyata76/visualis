#include "../include/visvamp/fileformat.hpp"

namespace vampire5 {


	bool createFile(std::string path, std::ifstream& file1, std::ifstream& file2, std::string number, std::string out_instruction) {
		using std::literals::string_literals::operator""s;

		std::ofstream file;
		file.open(path + "/spins-"s + number + ".visv"s);
		



	}






} // !vampire5