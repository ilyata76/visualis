#include "./parser-converter.hpp"

bool v5_parser_converter(const std::wstring& _path_to_folder, int _number_of_file) {    
    Assert(_path_to_folder != VVIS_PATH_PLUG_WSTR);
    Assert(_number_of_file != VVIS_INT_PLUG);


    std::wfstream atoms_file;
    std::wfstream spins_file;
    std::wfstream sconfiguration_file;

    std::stringstream ssm;

    std::wstring size1, size2, strk;
    std::wstring m, l, x, y, z;
    std::wstring sx, sy, sz;

    atoms_file.open(_path_to_folder + L"\\" + VVIS_VAMPIRE5_ATOMS_NAME_WSTR + VVIS_VAMPIRE5_ATOMS_FORMAT_WSTR, std::ios_base::in);
    spins_file.open(_path_to_folder + L"\\" + VVIS_VAMPIRE5_SPINS_START_NAME_WSTR + v5_get_file_number(std::to_wstring(_number_of_file)) + VVIS_VAMPIRE5_SPINS_FORMAT_WSTR, std::ios_base::in);
    sconfiguration_file.open(_path_to_folder + L"\\" + VVIS_VVIS_FILE_START_NAME_WSTR + v5_get_file_number(std::to_wstring(_number_of_file)) + VVIS_VVIS_FILE_FORMAT_WSTR, std::ios_base::out | std::ios_base::trunc);

    atoms_file >> size1;
    spins_file >> size2;

    if (size1 != size2) return false;

    sconfiguration_file << VVIS_VVIS_COMMENT << L"count" << L'\n';
    sconfiguration_file << size1            << L'\n';
    sconfiguration_file << VVIS_VVIS_COMMENT << L"M" << L'\t' << L"L" << L'\t' << L"X" << L'\t' << L"Y" << L'\t' << L"Z" << L'\t' << L"SX" << L'\t' << L"SY" << L'\t' << L"SZ" << L'\n';

    while (!spins_file.eof()) {
        
        atoms_file >> m; if (m[0] == VVIS_VAMPIRE5_DATA_COMMENT) { std::getline(atoms_file, strk); atoms_file >> m; }
        atoms_file >> l; if (l[0] == VVIS_VAMPIRE5_DATA_COMMENT) { std::getline(atoms_file, strk); atoms_file >> l; }
        atoms_file >> x; if (x[0] == VVIS_VAMPIRE5_DATA_COMMENT) { std::getline(atoms_file, strk); atoms_file >> x; }
        atoms_file >> y; if (y[0] == VVIS_VAMPIRE5_DATA_COMMENT) { std::getline(atoms_file, strk); atoms_file >> y; }
        atoms_file >> z; if (z[0] == VVIS_VAMPIRE5_DATA_COMMENT) { std::getline(atoms_file, strk); atoms_file >> z; }
        spins_file >> sx; if (sx[0] == VVIS_VAMPIRE5_DATA_COMMENT) { std::getline(spins_file, strk); atoms_file >> sx; }
        spins_file >> sy; if (sy[0] == VVIS_VAMPIRE5_DATA_COMMENT) { std::getline(spins_file, strk); atoms_file >> sy; }
        spins_file >> sz; if (sz[0] == VVIS_VAMPIRE5_DATA_COMMENT) { std::getline(spins_file, strk); atoms_file >> sz; }
        
        sconfiguration_file << l << L'\t' << m << L'\t' << x << L'\t' << y << L'\t' << z << L'\t' << sx << L'\t' << sy << L'\t' << sz << L'\t' << L'\n';

    }
    
    return true;
}
