#include "../include/visvamp/fileformat.hpp"

namespace vampire5 {


	bool createFile(std::string path, std::ifstream& file1, std::ifstream& file2, std::string number, std::string out_instruction) {
		using std::literals::string_literals::operator""s;

		std::ofstream file;
		file.open(path + "/spins-"s + number + ".visv"s, std::ios::out);
		
		// чтение
		if (file.is_open()) {

			if (out_instruction == "yes") std::cout << "[VISUALIS/VAMPIRE] ==========================================="s << std::endl;
			if (out_instruction == "yes") std::cout << "[VISUALIS/VAMPIRE] Start reading data"s << std::endl;
			if (out_instruction == "yes") std::cout << "[VISUALIS/VAMPIRE] ___________________________________________"s << std::endl;

			std::vector <vertex> res = parse(file1, file2, out_instruction);

			if (out_instruction == "yes") std::cout << "[VISUALIS/VAMPIRE] ==========================================="s << std::endl;

			if (out_instruction == "yes") std::cout << "[VISUALIS/VAMPIRE] Start writing data"s << std::endl;
			if (out_instruction == "yes") std::cout << "[VISUALIS/VAMPIRE] ___________________________________________"s << std::endl;

			file << "NUMBER\t MATERIAL\t LAYER\t X_COORD\t Y_COORD\t Z_COORD\t X_SPIN\t Y_SPIN\t Z_SPIN\t";


			file << '\n'
				<< std::to_string(res.size());

			for (int j = 0; j < res.size(); ++j) {

				if (out_instruction == "yes")
					if ((j + 1) % OUT_STEP == 0 || ((j + 1) == res.size())) std::cout << "[VISUALIS/VAMPIRE] WRITED: "s + std::to_string(j + 1) + "/"s + std::to_string(res.size()) << std::endl;

				file << '\n'
					<< res[j].getNumber() + 1 << '\t'
					<< res[j].getPoint().getMaterial() << '\t'
					<< res[j].getPoint().getLayer() << '\t'
					<< res[j].getPoint().getX() << '\t'
					<< res[j].getPoint().getY() << '\t'
					<< res[j].getPoint().getZ() << '\t'
					<< res[j].getSpin().getX() << '\t'
					<< res[j].getSpin().getY() << '\t'
					<< res[j].getSpin().getZ();
			}

			if (out_instruction == "yes") std::cout << "[VISUALIS/VAMPIRE] ==========================================="s << std::endl;

			return true;
		} else {
			return false;
		}

	}


	std::vector <vertex> fileParse(std::ifstream& file, std::string out_instruction) {
		std::vector <vertex> result;

		if (file.is_open() && !file.eof()) {

		}


		return result;
	}




} // !vampire5