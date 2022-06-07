
#include "./color/RGB.hpp"
#include "./settings/global_settings.hpp"
#include "./settings/freeglut_settings.hpp"
#include <iostream>

int main(int argc, char** argv) {
	Global_settings a;
	Freeglut_settings b;
	std::wcout << a;
	std::wcout << b;
	system("pause");
	return 0;
}