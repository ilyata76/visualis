#include "./console/console_interpretator.hpp"

bool want_to_restart() {
	std::wcout << L"\tDo you want to restart the program? (y/n)\n"; std::wstring answer;
	std::wcout << L"\t"; std::wcin >> answer;

	if (by_synonyms(answer) == L"yes") {
		return true;
	}

	return false;
}


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
		std::wcout << L"\tProgram exception : " << E.get_index() << L" : " << E.get_comment() << L" : " << E.get_description() << std::endl;
		
		/*if (want_to_restart()) return main(argc, argv); else*/ return E.get_index();
	
	} catch(int &E) {
		std::wcout << L"\t" << E << std::endl;

		/*if (want_to_restart()) return main(argc, argv); else*/ return E;
	
	} catch (std::invalid_argument& E) {
		std::wcout << L"\tInvalid argument : " << E.what() << std::endl;

		/*if (want_to_restart()) return main(argc, argv); else*/ return 1;

	} catch (std::domain_error& E) {
		std::wcout << L"\tDomain error : " << E.what() << std::endl;

		/*if (want_to_restart()) return main(argc, argv); else*/ return 1;

	} catch (std::length_error& E) {
		std::wcout << L"\tLength error : " << E.what() << std::endl;

		/*if (want_to_restart()) return main(argc, argv); else*/ return 1;

	} catch (std::out_of_range& E) {
		std::wcout << L"\tOut of range : " << E.what() << std::endl;

		/*if (want_to_restart()) return main(argc, argv); else*/ return 1;

	} catch (std::logic_error& E) {
		std::wcout << L"\tLogic error : " << E.what() << std::endl;

		/*if (want_to_restart()) return main(argc, argv); else*/ return 1;

	}  catch (std::range_error& E) {
		std::wcout << L"\tRange error : " << E.what() << std::endl;

		/*if (want_to_restart()) return main(argc, argv); else*/ return 1;

	} catch (std::overflow_error& E) {
		std::wcout << L"\tOverflow error : " << E.what() << std::endl;

		/*if (want_to_restart()) return main(argc, argv); else*/ return 1;

	} catch (std::system_error& E) {
		std::wcout << L"\tSystem error : " << E.what() << std::endl;

		/*if (want_to_restart()) return main(argc, argv); else*/ return 1;

	} catch (std::runtime_error& E) {
		std::wcout << L"\tRuntime error : " << E.what() << std::endl;

		/*if (want_to_restart()) return main(argc, argv); else*/ return 1;

	} catch (std::exception& E) {
		std::wcout << L"\tStd exception : " << E.what() << std::endl;

		/*if (want_to_restart()) return main(argc, argv); else*/ return 1;
	
	}

	return 0;
}