#pragma once

#ifndef FILEFORMAT_HPP
#define FILEFORMAT_HPP

	#include <string>
	#include <fstream>
	#include <iostream>

	#include "./vampparse.hpp"

	namespace vampire5 {

		bool createFile(std::string path, std::ifstream& file1, std::ifstream& file2, std::string number, std::string out_instruction = "yes");
		std::vector <vertex> fileParse(std::ifstream& file, std::string out_instruction = "yes");

	} // !vampire5

#endif // !FILEFORMAT_HPP