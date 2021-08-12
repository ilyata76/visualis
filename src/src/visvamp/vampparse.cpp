#include "../include/visvamp/vampparse.hpp"


namespace vampire5 {



	std::vector<vertex> parse() {

		std::vector<vertex> result;

		//std::vector<point> points;
		//std::vector<spin> spins;

		std::ifstream file1; // for point
		std::ifstream file2; // for spin

		file1.open("D:\\CPP_2020\\opengl-visualis\\trash\\atoms-coords.data");
		file2.open("D:\\CPP_2020\\opengl-visualis\\trash\\spins-00000000.data");

		if (file1.is_open() && !file1.eof()) {


			if (file2.is_open() && !file2.eof()) {

				std::string str1;
				std::string str2;

				std::getline(file1, str1);
				std::getline(file2, str2);

				if (std::stoi(str1) == std::stoi(str2)) {

					int numbers = stoi(str1);

					std::vector<float> s1;
					std::vector<float> s2;

					std::string forint1 = "";
					std::string forint2 = "";


					for (int i = 0; !file2.eof() && !file1.eof(); i++) {
					
						if (i % 10000 == 0) std::cout << "LOADED: " << i << "/" << numbers << std::endl;

						std::getline(file1, str1);
						std::getline(file2, str2);

						if (str1 != "" && str1 != " " && str1 != "\n" && str1 != "\t" && str2 != "" && str2 != " " && str2 != "\n" && str2 != "\t") {

							for (int j = 0; j < str1.size(); j++) {
								if (str1[j] != ' ' && str1[j] != '\n' && str1[j] != '\t') {
									forint1.push_back(str1[j]);
								} else {
									s1.push_back(std::stof(forint1));
									forint1.clear();
								}
							}

							s1.push_back(std::stof(forint1));
							forint1.clear();
						
							for (int j = 0; j < str2.size(); j++) {
								if (str2[j] != ' ' && str2[j] != '\n' && str2[j] != '\t') {
									forint2.push_back(str2[j]);
								} else {
									s2.push_back(std::stof(forint2));
									forint2.clear();
								}
							} 

							s2.push_back(std::stof(forint2));
							forint2.clear();
						
							result.push_back(vertex(spin(s2[0], s2[1], s2[2], i), point(s1[0], s1[1], s1[2], s1[3], s1[4], i), i));

							s1.clear();
							s2.clear();

							//std::cout << result[i].stringVertex();
						
						} else continue;

					}


				} else {
					std::cerr << "The numbers of atoms in the two files does not converge\n";
					result.push_back(vertex(spin(INT_CHECK_VP, INT_CHECK_VP, INT_CHECK_VP, INT_CHECK_VP), point(INT_CHECK_VP, INT_CHECK_VP, INT_CHECK_VP, INT_CHECK_VP, INT_CHECK_VP, INT_CHECK_VP), INT_CHECK_VP));
				}


			} else {
				std::cerr << "Second file (spins-...) is empty or closed\n";
				result.push_back(vertex(spin(INT_CHECK_VP, INT_CHECK_VP, INT_CHECK_VP, INT_CHECK_VP), point(INT_CHECK_VP, INT_CHECK_VP, INT_CHECK_VP, INT_CHECK_VP, INT_CHECK_VP, INT_CHECK_VP), INT_CHECK_VP));
			}


		} else {
			std::cerr << "First file (.data) is empty or closed\n";
			result.push_back(vertex(spin(INT_CHECK_VP, INT_CHECK_VP, INT_CHECK_VP, INT_CHECK_VP), point(INT_CHECK_VP, INT_CHECK_VP, INT_CHECK_VP, INT_CHECK_VP, INT_CHECK_VP, INT_CHECK_VP), INT_CHECK_VP));
		}

		
		return result;
	}



	bool operator == (point& X, int Y) {
		if (X.m1 == Y) {
			if (X.l == Y) {
				if (X.number == Y) {
					if (X.X == Y) {
						if (X.Y == Y) {
							if (X.Z == Y) {
								return true;
							}
						}
					}
				}
			}
		}
		return false;
	}

	bool operator == (spin& X, int Y) {
		if (X.number == Y) {
			if (X.X == Y) {
				if (X.Y == Y) {
					if (X.Z == Y) {
						return true;
					}
				}
			}
		}
		return false;
	}

	bool operator == (vertex& X, int Y) {
		if (X.P == Y) {
			if (X.S == Y) {
				if (X.number == Y) {
					return true;
				}
			}
		}
		return false;
	}

	bool operator != (point& X, int Y) {
		return !(X == Y);
	}

	bool operator != (spin& X, int Y) {
		return !(X == Y);
	}

	bool operator != (vertex& X, int Y) {
		return !(X == Y);
	}






} // !namespace vampire5