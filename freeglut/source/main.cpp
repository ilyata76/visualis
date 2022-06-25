
#include "./settings/settings.hpp"
#include "./console/console_interpretator.hpp"
#include <iostream>

#include "./libraries/freeglut/include/GL/freeglut.h"

int main(int argc, char** argv) {
	Interpretator I;

	enum interpreter_state { ok, error, restart };

	switch (I.loop(argc, argv)) {
		case ok: std::wcout << L"ok\n"; break;
		case error: std::wcout << L"error\n"; break;
		case restart: std::wcout << L"restart\n"; break;
	};

	system("pause");
	 
	return 0;
}