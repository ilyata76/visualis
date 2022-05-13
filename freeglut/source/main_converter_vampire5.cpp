#include <iostream>


#include "./include/parser-converter/converter-v5.hpp"
#include "./include/parser-converter/parser-v5.hpp"

// name converter_v5.exe

bool is_number(const std::wstring& s) {
    return !s.empty() && std::find_if(s.begin(),
        s.end(), [](wchar_t c) { return !std::isdigit(c); }) == s.end();
}

std::wstring my_path(const std::wstring& backup_path, const std::wstring& path) {
    if (path[0] == L'.') {
        return  backup_path + L'\\' + path;
    } else  {
        return path;
    }
}


int main(int argc, char** argv) {
    try {
        if (argc == 1) {

            _wsetlocale(LC_ALL, L""); std::wstring F; std::wstring backup_path;

            std::string paths(argv[0]); std::wstring path(paths.begin(), paths.end()); path.erase(path.end() - 17, path.end()); backup_path = path;
            std::wcout << L"| | Directory: " << path << '\n';

            // https://docs.microsoft.com/ru-ru/dotnet/standard/io/file-path-formats

        
            confirming:

            
            do {
                std::wcout << L"| | Confirm this: " << my_path(backup_path, path) << L": (y/n)? "; std::wcin >> F; 
            } while (F != L"n" && F != L"y");

            if (F == L"n") {

                F = L"x";
                while (F != L"n" && F != L"y") {
                    std::wcout << L"| | Do you want to write a new path: (y/n)? "; std::wcin >> F;
                }

                if (F == L"y") {
                    std::wcout << L"| | Path >> "; std::wcin >> path; F = L"x"; goto confirming; 
                } else {
                    return 0;
                }

            }

            std::wstring filenumber;

            do {
                std::wcout << L"| | Spins file number? (1, 2, etc.). Use \"all\" to convert all files : "; std::wcin >> filenumber;
            } while (!is_number(filenumber) && filenumber != L"all");
            
            path = my_path(backup_path, path);
            
            int index = 0;
            if (filenumber != L"all") {

                index = std::stoi(filenumber);

                std::wcout << L"\n|" << filenumber << L"|" << L": reading... ";
                std::wstring format_string = vampire5::parser::get_string(path)(index);

                std::wcout << L"; convering... ";
                if (vampire5::converter::convert(format_string, path)) std::wcout << L"; success! ";
                else std::wcout << L"; something went wrong.. ";


            } else {

                for (index = 0;; ++index) {
                    

                    std::wstring name_of_spins_file = vampire5::parser::get_spin_file_name(index); std::ifstream spins_file;
                    spins_file.open(path + L"/" + name_of_spins_file + FORMAT_OF_SPINS_FILE_V5, std::ios_base::in);
                    
                    if (index != 0 && !spins_file.is_open()) { std::wcout << L"\n| | " << vampire5::parser::get_spin_file_name(index - 1) + FORMAT_OF_SPINS_FILE_V5 << " was last.\n"; break; }
                    spins_file.close();
                    
                    std::wcout << L"\n|" << index << L"|" << L": reading... ";
                    std::wstring format_string = vampire5::parser::get_string(path)(index);
                   
                    std::wcout << L"; convering... ";
                    
                    if (vampire5::converter::convert(format_string, path)) std::wcout << L"; success! ";
                    else std::wcout << L"; something went wrong.. ";
                }
            }

        } else {
            // место для флагов

        }
    } catch (Exceptio& E) {
        // коды ошибки
        std::wstring F;
        std::wcout << L"\n| | An error has occurred. Do you want to repeat it (y/n)? : "; std::wcin >> F;

        if (F == L"y") return main(argc, argv);

    }


    system("pause");
    return 0;
}