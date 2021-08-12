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
					phi = atan(Sy / Sx);
					theta = atan(Sz / sqrt(pow(Sx, 2) + pow(Sy, 2)));
				} else if (Sx > 0 && Sy > 0 && Sz < 0) {
					phi = atan(Sy / Sx);
					theta = -atan(Sz / sqrt(pow(Sx, 2) + pow(Sy, 2)));
				} else if (Sx < 0 && Sy > 0 && Sz > 0) {
					phi = 90 + atan(Sx / Sy);
					theta = atan(Sz / sqrt(pow(Sx, 2) + pow(Sy, 2)));
				} else if (Sx < 0 && Sy > 0 && Sz < 0) {
					phi = 90 + atan(Sx / Sy);
					theta = -atan(Sz / sqrt(pow(Sx, 2) + pow(Sy, 2)));
				} else if (Sx < 0 && Sy < 0 && Sz < 0) {
					phi = 180 + atan(Sy / Sx);
					theta = -atan(Sz / sqrt(pow(Sx, 2) + pow(Sy, 2)));
				} else if (Sx < 0 && Sy > 0 && Sz > 0) {
					phi = 180 + atan(Sy / Sx);
					theta = atan(Sz / sqrt(pow(Sx, 2) + pow(Sy, 2)));
				} else if (Sx > 0 && Sy < 0 && Sz > 0) {
					phi = 270 + atan(Sx / Sy);
					theta = atan(Sz / sqrt(pow(Sx, 2) + pow(Sy, 2)));
				} else if (Sx > 0 && Sy < 0 && Sz < 0) {
					phi = 270 + atan(Sx / Sy);
					theta = -atan(Sz / sqrt(pow(Sx, 2) + pow(Sy, 2)));
				}

				cones.push_back(cone(phi, theta, axis(0, 1, 0), axis(0, 0, 1), point(EXAMPLE[i].getPoint())));

			}

			return new coneSample(cones);

		} else if (instruction == "arrow") {
			return new coneSample; // should be arrows
		} else {
			return new coneSample; // empty vector
		}
	}


}