#pragma once

#ifndef VAMPSAMPLE_HPP
#define VAMPSAMPLE_HPP


	#include "./visvamp/vampparse.hpp"
	#include <math.h>

	namespace vampire5 {

		class prototype {
		public:
			//std::vector<vertex> PROTO;
		public:

			 prototype() {};

			 /*prototype(std::vector<vertex> P) {
				 this->PROTO = P;
			 };*/

			 virtual std::string info() = 0;
			 virtual ~prototype() {};
		};

		
		
		class axis {
		public:
			float x; float y; float z;
		public:
			axis() { this->y = this->z = this->x = 0; };
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
			cone() { this->phi = 0; this->theta = 0; };
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

		};

		class coneSample : public prototype {
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
			
		};


		prototype* makeSample(std::vector<vertex> EXAMPLE, std::string instruction = "cone"); // функция для преобразования
	}


#endif // !VAMPSAMPLE_HPP