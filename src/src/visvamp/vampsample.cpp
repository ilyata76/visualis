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

			for (int i = 0; i < EXAMPLE.size(); i++) {

				// ���������� �� ��� �X; ������ ��� �Z

				Sx = EXAMPLE[i].getSpin().getX();
				Sy = EXAMPLE[i].getSpin().getY();
				Sz = EXAMPLE[i].getSpin().getZ();

				// theta ������� �����, ��� �� �������� "��� �����" �� ������� �� ������ ���� � "����" - �� ������ �����
				// phi ������� �����, ��� �� �������������� ����������� �� ��� ������ ������� ������� �� �������

				if (Sx > 0 && Sy > 0 && Sz > 0) {
					phi = abs(atan(Sy / Sx) * 180.0 / 3.1415);\
					//
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
					//std::cout << "mi zdes : " << Sy / Sx << std::endl;
					phi = 180 + abs(atan(Sy / Sx) * 180.0 / 3.1415);
					theta = -atan(Sz / (sqrt(pow(Sx, 2) + pow(Sy, 2)))) * 180.0 / 3.1415;
					//theta = acos(Sz / pow((pow(Sx, 2) + pow(Sy, 2) + pow(Sz, 2)), 0.5));
					//std::cout << "theta: " << theta << "   phi : " << phi << std::endl;
				} else if (Sx < 0 && Sy > 0 && Sz > 0) {
					phi = 180 + abs(atan(Sy / Sx) * 180.0 / 3.1415);
					theta = atan(Sz / sqrt(pow(Sx, 2) + pow(Sy, 2))) * 180.0 / 3.1415;
				} else if (Sx > 0 && Sy < 0 && Sz > 0) {
					phi = 270 + abs(atan(Sx / Sy) * 180.0 / 3.1415);
					theta = atan(Sz / sqrt(pow(Sx, 2) + pow(Sy, 2))) * 180.0 / 3.1415;
				} else if (Sx > 0 && Sy < 0 && Sz < 0) {
					//std::cout << "mi zdes : " << Sx / Sy << std::endl;
					phi = 270 + abs(atan(Sx / Sy) * 180.0 / 3.1415);
					//std::cout << phi;
					theta = -atan(Sz / sqrt(pow(Sx, 2) + pow(Sy, 2))) * 180.0 / 3.1415;
				}

				cones.push_back(cone(-phi, -theta, axis(1, 0, 0), axis(0, 1, 0), point(EXAMPLE[i].getPoint())));

			}

			return new coneSample(cones);

		} else if (instruction == "arrow") {
			return new coneSample; // should be arrows
		} else {
			return new coneSample; // empty vector
		}
	}


}