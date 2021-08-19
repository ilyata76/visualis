#include "./visvamp/vampsample.hpp"

namespace vampire5 {


	coneSample* makeSample(std::vector<vertex> EXAMPLE, std::string instruction, int iteration, std::string out_instruction) {
		
		
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

				if (out_instruction == "yes") 
					if ((i + 1) % OUT_STEP == 0 || i + 1 == numbers) std::cout << "[VISUALIS/VAMPIRE] TRANSFORMATED[" << iteration << "]: " << i + 1 << "/" << numbers << std::endl;
			}

			return new coneSample(cones);

		} else if (instruction == "arrow") {
			return new coneSample; // should be arrows
		} else {
			return new coneSample(); // empty vector
		}
	}

	bool cone::coneCreated() {
		if (this->phi == INT_CHECK_VP || this->theta == INT_CHECK_VP 
			|| this->Ap.x == INT_CHECK_VP|| this->At.x == INT_CHECK_VP
			|| this->Ap.y == INT_CHECK_VP || this->At.y == INT_CHECK_VP
			|| this->Ap.z == INT_CHECK_VP || this->At.z == INT_CHECK_VP
			|| this->P == INT_CHECK_VP
			) return false;
		else return true;
	}

	std::vector < coneSample* > makeVSample(std::vector< std::vector<vertex> > EXAMPLE, std::string instruction, std::string out_instruction) {
		using std::literals::string_literals::operator""s;

		std::vector < coneSample* > result;

		coneSample* cS;

		for (int i = 0; i < EXAMPLE.size(); ++i) {
			cS = makeSample(EXAMPLE[i], "cone", i, out_instruction);
			if (cS->getCone(0).coneCreated()) result.push_back(cS);
		}

		return result;

	}



} // !namespace vampire5