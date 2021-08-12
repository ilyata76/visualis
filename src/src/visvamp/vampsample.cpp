#include "./visvamp/vampsample.hpp"

namespace vampire5 {


	prototype* makeSample(std::vector<vertex> EXAMPLE, std::string instruction = "cone") {
		
		
		if (instruction == "cone") {

			std::vector<cone> cones;


			int i;

			EXAMPLE[i].getPoint().getX();







			return new coneSample(cones);

		} else if (instruction == "arrow") {
			return new coneSample; // should be arrows
		} else {
			return new coneSample; // empty vector
		}
	}


}