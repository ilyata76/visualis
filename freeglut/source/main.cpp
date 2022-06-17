
#include "./settings/settings.hpp"
#include "./console/console_interpretator.hpp"
#include <iostream>

#include "./libraries/freeglut/include/GL/freeglut.h"

int main(int argc, char** argv) {
	Global_settings a;
	Freeglut_settings b;
	Settings AA (a, b);
	AA.global_settings.path_to_folder = L".";
	AA.get(L'a');
	Interpretator I(AA);
	//AA.print_only_freeglut(std::wcout);
	//AA.print_only_global(std::wcout);

	enum interpreter_state { ok, error, restart };

	switch (I.loop(argc, argv)) {
		case ok: std::wcout << L"ok\n"; print_logo(std::wcout); AA.print_only_global(std::wcout); AA.print_only_freeglut(std::wcout);  break;
		case error: std::wcout << L"error\n"; break;
		case restart: std::wcout << L"restart\n"; break;
	};

	system("pause");
	 
	return 0;
}