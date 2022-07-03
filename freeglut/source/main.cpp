#include "./console/console_interpretator.hpp"

int main(int argc, char** argv) {
	try {
		Interpretator I;

		enum interpreter_state { ok, error, restart };

		switch (I.loop(argc, argv)) {
			case ok: break;
			case error: std::wcout << L"\terror!\n"; break;
			case restart: std::wcout << L"\trestarting\n"; return main(argc, argv); break;
		};

	} catch (Exceptio& E) {
		return E.get_index();
	} catch(int &E) {
		return E;
	} catch (std::exception& E) {
		std::wcout << E.what();
		return 1;
	} // todo: проработать

	return 0;
}