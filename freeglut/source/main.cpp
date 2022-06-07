
#include "./color/RGB.hpp"
#include "./settings/settings.hpp"
#include <iostream>

int main(int argc, char** argv) {
	Global_settings a;
	Freeglut_settings b;
	Settings AA (a, b);
	AA.global_settings.path_to_folder = L".";
	AA.get(L'a');
	AA.print_only_freeglut(std::wcout);
	AA.print_only_global(std::wcout);
	system("pause");
	return 0;
}