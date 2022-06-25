#include "./console/console_interpretator.hpp"


int main(int argc, char** argv) {
	Interpretator I;

	enum interpreter_state { ok, error, restart };

	switch (I.loop(argc, argv)) {
		case ok: break;
		case error: std::wcout << L"\terror!\n"; break;
		case restart: std::wcout << L"\trestarting\n"; return main(argc, argv); break;
	};
	 
	return 0;
}