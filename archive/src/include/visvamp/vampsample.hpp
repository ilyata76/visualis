#pragma once

#ifndef VAMPSAMPLE_HPP
#define VAMPSAMPLE_HPP


	#include "./visvamp/vampparse.hpp"
	#include <math.h>

	namespace vampire5 {
			
		class axis {
		public:
			float x; float y; float z;
		public:
			axis() { this->y = this->z = this->x = INT_CHECK_VP; };
			axis(float x, float y, float z) {
				this->x = x;
				this->y = y;
				this->z = z;
			}
		};

		class cone {
		private:
			float phi;
			axis Ap;

			float theta;
			axis At;

			point P;

		public:
			cone() { this->phi = INT_CHECK_VP; this->theta = INT_CHECK_VP; };
			cone(float phi, float theta, axis Ap, axis At, point P) {
				this->phi = phi; this->theta = theta;
				this->Ap = Ap; this->At = At;
				this->P = P;
			};

			float getPhiAngle() {
				return this->phi; // 100
			}

			float getThetaAngle() {
				return this->theta; //010
			}

			axis getPhiAxes() {
				return this->Ap;
			}

			axis getThetaAxes() {
				return this->At;
			}

			point getPoint() {
				return this->P;
			}

			bool coneCreated();

		};

		class coneSample {
		private:
			std::vector<cone> cones;
		public:
			coneSample() {};
			coneSample(std::vector<cone> C) {
				this->cones = C;
			};



			std::string info() {
				return ("CONE [(angle of rotation),(axis for rotation)]\n");
			}

			cone getCone(int iteration) {
				return this->cones[iteration];
			}
			
			int size() { return cones.size(); }

		};


		coneSample* makeSample(std::vector<vertex> EXAMPLE, std::string instruction = "cone", int iteration = 0, std::string out_instruction = "yes"); // функция для преобразования
		//coneSample* makeSample(std::vector< std::vector<vertex> > EXAMPLE, std::string instruction = "cone", int iteration = 0);

		std::vector < coneSample* > makeVSample(std::vector< std::vector<vertex> > EXAMPLE, std::string instruction = "cone", std::string out_instruction = "yes");

	} // !namespace vampire5


#endif // !VAMPSAMPLE_HPP