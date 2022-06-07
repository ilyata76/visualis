
#include "./color/RGB.hpp"
#include "./settings/settings.hpp"
#include <iostream>

int main(int argc, char** argv) {
	Global_settings a;
	Freeglut_settings b;
	a.number_of_file = 100;
	Settings AA (a, b);
	AA.global_settings.path_to_folder = L".";
	AA.save(L'a');
	AA.print_only_freeglut(std::wcout);
	AA.print_only_global(std::wcout);
	system("pause");
	return 0;
}