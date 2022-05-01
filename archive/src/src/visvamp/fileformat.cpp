#include "../include/visvamp/fileformat.hpp"

namespace vampire5 {


	bool createFile(std::string path, std::ifstream& file1, std::ifstream& file2, std::string number, std::string out_instruction) {
		using std::literals::string_literals::operator""s;

		std::ofstream file;
		file.open(path + "/spins-"s + number + ".visv"s, std::ios::out);
		
		// чтение
		if (file.is_open()) {

			std::vector <vertex> res = parse(file1, file2, out_instruction);

			file << "NUMBER\t MATERIAL\t LAYER\t X_COORD\t Y_COORD\t Z_COORD\t X_SPIN\t Y_SPIN\t Z_SPIN\t";


			file << '\n'
				<< std::to_string(res.size());

			for (int j = 0; j < res.size(); ++j) {

				if (out_instruction == "yes")
					if ((j + 1) % OUT_STEP == 0 || (j + 1) == static_cast<int>(res.size())) std::cout << "[VISUALIS/VAMPIRE] WRITED: "s + std::to_string(j + 1) + "/"s + std::to_string(res.size()) << std::endl;

				file << '\n'
					<< res[j].getNumber() << '\t'
					<< res[j].getPoint().getMaterial() << '\t'
					<< res[j].getPoint().getLayer() << '\t'
					<< res[j].getPoint().getX() << '\t'
					<< res[j].getPoint().getY() << '\t'
					<< res[j].getPoint().getZ() << '\t'
					<< res[j].getSpin().getX() << '\t'
					<< res[j].getSpin().getY() << '\t'
					<< res[j].getSpin().getZ();
			}

			return true;
		} else {
			return false;
		}

	}


	std::vector <vertex> fileParse(std::ifstream& file, std::string out_instruction) {
		using std::literals::string_literals::operator""s;
		std::vector <vertex> result;
		std::string numbers;
		std::string str;

		std::getline(file, str);
		std::getline(file, numbers);
		str.clear();

		if (file.is_open() && !file.eof()) {


			for (int j = 0; !file.eof(); ++j) {

				std::vector<float> s1;
				std::string strfor;

				std::getline(file, str);


				if (str != "" && str != " " && str != "\n" && str != "\t" && str != "" && str != " " && str != "\n" && str != "\t") {

					for (int j = 0; j < str.size(); j++) {
						if (str[j] != ' ' && str[j] != '\n' && str[j] != '\t') {
							strfor.push_back(str[j]);
						} else {
							s1.push_back(std::stof(strfor));
							strfor.clear();
						}
					}

					s1.push_back(std::stof(strfor));
					strfor.clear();

					int number = s1[0];

					result.push_back(vertex(
						spin(s1[6], s1[7], s1[8], number),
						point(s1[1], s1[2], s1[3], s1[4], s1[5], number),
						number
					));

					s1.clear();


					if (out_instruction == "yes")
						if ((j + 1) % OUT_STEP == 0 || (j + 1) == stoi(numbers)) std::cout << "[VISUALIS/VAMPIRE] READED: "s + std::to_string(j + 1) + "/"s + numbers << std::endl;
					
				} else {
					//
				}
			}
		} else {
			std::cerr << "[VISUALIS/VAMPIRE][ERROR] : File spins-XXX.visv empty or closed does not exist or closed or empty\n"s;
			result.push_back(vertex(spin(INT_CHECK_VP, INT_CHECK_VP, INT_CHECK_VP, INT_CHECK_VP), point(INT_CHECK_VP, INT_CHECK_VP, INT_CHECK_VP, INT_CHECK_VP, INT_CHECK_VP, INT_CHECK_VP), INT_CHECK_VP));
		}
		// std::cout << result[24].stringVertex();
		return result;
	}




} // !vampire5