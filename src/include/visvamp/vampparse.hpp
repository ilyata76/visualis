#pragma once


#ifndef VAMPPARSE_HPP
#define VAMPPARSE_HPP

	#include <vector>
	#include <iostream>
	#include <fstream>
	#include <string>


	namespace vampire5 {


		class spin {
		private:
			float X;
			float Y;
			float Z;
			int number;
		public:
			spin() { this->X = this->Y = this->Z = 0; this->number = 0; };
			spin(float X, float Y, float Z, int number) {
				this->X = X;
				this->Y = Y;
				this->Z = Z;
				this->number = number;
			};

			std::string stringSpin() {
				return std::string(
					"SPIN VECTOR COORDS: " + std::to_string(this->X)
					+ " " + std::to_string(this->Y) + " " + std::to_string(this->Z) + " "
				);
			};


			~spin() {};

		};

		class point {
		private:
			int m1;
			int m2;
			float X;
			float Y;
			float Z;
			int number;
		public:
			point() { this->X = this->Y = this->Z = 0; this->number = this->m1 = this->m2 = 0; };
			point(int m1, int m2, float X, float Y, float Z, int number) {
				this->m1 = m1;
				this->m2 = m2;
				this->X = X;
				this->Y = Y;
				this->Z = Z;
				this->number = number;
			};


			std::string stringPoint() {
				return std::string(
					"POINT coords (X Y Z): " + std::to_string(this->X) + " " + std::to_string(this->Y) + " " + std::to_string(this->Z)
					+ " MATERIAL (m1 m2): " + std::to_string(this->m1) + " " + std::to_string(this->m2)
				);
			};


			~point() {};

		};

		class vertex {
		private:
			spin S;
			point P;
			int number;
		public:
			vertex() { this->number = 0; };
			vertex(spin S, point P, int number) {
				this->S = S;
				this->P = P;
				this->number = number;
			};

			std::string stringVertex() {
				return std::string(
					"NUMBER: " + std::to_string(this->number) + " " +
					P.stringPoint() + " " + S.stringSpin() + "\n"
				);
			};

			~vertex() {};

		};

		class prototype {
		private:
			std::vector<vertex> PROTO;
			// набор вертексов, преображённых до компонент конуса, готовый к отрисовке
		public:
			prototype() {};
			~prototype() {};
		};

		std::vector<vertex> parse(); // заглавная функция для чтения данных

		prototype makePrototype(std::vector<vertex> EXAMPLE); // функция для преобразования

		// нужен ли материал??




	} // !namespace vampire5

#endif // !VAMPPARSE_HPP