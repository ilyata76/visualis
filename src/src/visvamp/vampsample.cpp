#include "./visvamp/vampsample.hpp"

namespace vampire5 {


	coneSample* makeSample(std::vector<vertex> EXAMPLE, std::string instruction) {
		
		
		if (instruction == "cone") {

			std::vector<cone> cones;

			float Sx = 0;
			float Sy = 0;
			float Sz = 0;

			float phi = 0;
			float theta = 0;

			int numbers = EXAMPLE.size();

			for (int i = 0; i < EXAMPLE.size(); i++) {

				// отклонение от оси ОX; вокруг оси ОZ

				Sx = EXAMPLE[i].getSpin().getX();
				Sy = EXAMPLE[i].getSpin().getY();
				Sz = EXAMPLE[i].getSpin().getZ();

				// theta принята углом, что от проекции "идёт вверх" до вектора со знаком плюс и "вниз" - со знаком минус
				// phi принята углом, что от положительного направления ОХ идёт против часовой стрелки до вектора

				if (Sx > 0 && Sy > 0 && Sz > 0) {
					phi = abs(atan(Sy / Sx) * 180.0 / 3.1415);\
					theta = atan(Sz / sqrt(pow(Sx, 2) + pow(Sy, 2))) * 180.0 / 3.1415;
				} else if (Sx > 0 && Sy > 0 && Sz < 0) {
					phi = abs(atan(Sy / Sx) * 180.0 / 3.1415);
					theta = -atan(Sz / sqrt(pow(Sx, 2) + pow(Sy, 2))) * 180.0 / 3.1415;
				} else if (Sx < 0 && Sy > 0 && Sz > 0) {
					phi = 90 + abs(atan(Sx / Sy) * 180.0 / 3.1415);
					theta = atan(Sz / sqrt(pow(Sx, 2) + pow(Sy, 2))) * 180.0 / 3.1415;
				} else if (Sx < 0 && Sy > 0 && Sz < 0) {
					phi = 90 + abs(atan(Sx / Sy) * 180.0 / 3.1415);
					theta = -atan(Sz / sqrt(pow(Sx, 2) + pow(Sy, 2))) * 180.0 / 3.1415;
				} else if (Sx < 0 && Sy < 0 && Sz < 0) {
					phi = 180 + abs(atan(Sy / Sx) * 180.0 / 3.1415);
					theta = -atan(Sz / (sqrt(pow(Sx, 2) + pow(Sy, 2)))) * 180.0 / 3.1415;
				} else if (Sx < 0 && Sy < 0 && Sz > 0) {
					phi = 180 + abs(atan(Sy / Sx) * 180.0 / 3.1415);
					theta = atan(Sz / sqrt(pow(Sx, 2) + pow(Sy, 2))) * 180.0 / 3.1415;
				} else if (Sx > 0 && Sy < 0 && Sz > 0) {
					phi = 270 + abs(atan(Sx / Sy) * 180.0 / 3.1415);
					theta = atan(Sz / sqrt(pow(Sx, 2) + pow(Sy, 2))) * 180.0 / 3.1415;
				} else if (Sx > 0 && Sy < 0 && Sz < 0) {
					phi = 270 + abs(atan(Sx / Sy) * 180.0 / 3.1415);
					theta = -atan(Sz / sqrt(pow(Sx, 2) + pow(Sy, 2))) * 180.0 / 3.1415;
				} else {
					std::cerr << "[VISUALIS/VAMPIRE] случай не предусмотрен\n";
				}

				cones.push_back(cone(-phi, -theta, axis(1, 0, 0), axis(0, 1, 0), point(EXAMPLE[i].getPoint())));
				if ((i + 1) % OUT_STEP == 0 || i + 1 == numbers) std::cout << "[VISUALIS/VAMPIRE] TRANSFORMATED: " << i + 1 << "/" << numbers << std::endl;
			}

			return new coneSample(cones);

		} else if (instruction == "arrow") {
			return new coneSample; // should be arrows
		} else {
			return new coneSample(); // empty vector
		}
	}



	coneSample* makeSample(std::vector< std::vector<vertex> > EXAMPLE, std::string instruction, int iteration) {
		return makeSample(EXAMPLE[iteration], "cone");
	}



} // !namespace vampire5