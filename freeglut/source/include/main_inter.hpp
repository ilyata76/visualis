#pragma once


#ifndef MAIN_INTER_HPP
#define MAIN_INTER_HPP
	
	#include "./include/parser-converter/parser-v5.hpp"
	#include "./include/parser-converter/converter-v5.hpp"

	#include "./include/sample/creator_of_vertex_arr.hpp"
	#include "./include/sample/drawing_shape_opengl.hpp"

	#define prompt _prompt()

	#define COMMAND_UNKNOW_COMMAND 100
	#define COMMAND_SET 101

	#include <iostream>
	#include <algorithm>
	#include <map>

	extern struct settings;
	extern std::map<std::wstring, int> main_command;


	void print_visualis_logo();
	
	std::wstring _prompt();
	std::wstring tolower_wstr(std::wstring& _value);

	int switch_code_of_operation(std::map<std::wstring, int> mapp, std::wstring& _value);

	std::wstring by_synonyms(const std::wstring& _value);
	
	void interpertator_loop(int argc, char** argv);




#endif