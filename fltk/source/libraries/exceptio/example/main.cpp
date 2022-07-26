#include "../src/exceptio.hpp"
#include "../src/assert.hpp"
#include "../src/assert_3rd.hpp"

#include <iostream>

namespace tia {
	class Logic_Error : public tia::Exceptio {
		public:
			Logic_Error(int _index) : Exceptio(_index) {};
			Logic_Error(int _index, const wchar_t* _discr) : Exceptio(_index, _discr) {};
			
			std::wstring what() override {
				return std::wstring(L"Logic Error!");
			};

			~Logic_Error() {
				std::wcout << "LE object was Destroyed\n";
			}
	};
}



int main() {

	try {

		std::wcout << "Exceptio Error...";
		throw tia::Exceptio(0, L"exceptio");

	} catch(tia::Exceptio& E) {

		try {

			std::wcout << " catched by Exceptio!\n";
			std::wcout << "Logic Error...";
			throw tia::Logic_Error(0, L"logic");

		} catch(tia::Exceptio& E) {

			try {
				tia::Assert assert;
				
				std::wcout << " catched by Exceptio!\n";
				std::wcout << "Override what(): " << E.what() << L"\n";
				std::wcout << "Assert false condition...";
				
				assert(bool(0));

			} catch(tia::Exceptio& E) {


				try {

					std::wcout << " catched by Exceptio!\n";
					std::wcout << "ASSERT false condition...";

					ASSERT(0);
				} catch (tia::Exceptio& E) {
					
					
					try {
						std::wcout << " catched by Exceptio!\n";

						std::wcout << "Assert_t false condition...";
						tia::Assert_t{}(0, std::exception{});
					}
					catch (std::exception& E) {

						try {
							std::wcout << " catched by std::exception!\n";

							std::wcout << "ASSERTT false condition...";
							ASSERTT(0);
						}
						catch (tia::Exceptio& E) {

							std::wcout << " catched by tia::Exceptio!\n";

							std::wcout << L"Creating exception: "; std::exception exc("sus");
							std::wcout << L"exc.what(): " << exc.what() << L'\n';

							std::wcout << L"Exceptio by exception deepcopying: " << (tia::Exceptio{ 100 } = exc).get_description() << L'\n';
							std::wcout << L"Exceptio by exception constructor: " << (tia::Exceptio{ exc }.get_description()) << L'\n';



						}
					}

				}

			}

		}


	}
	
	return 0;
}