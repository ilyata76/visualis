#include "./parser-converter.hpp"

bool v5_parser_converter(const std::string& _path_to_folder, int _number_of_file) {    
    Assert(_path_to_folder != VVIS_PATH_PLUG_WSTR);
    Assert(_number_of_file != VVIS_INT_PLUG);


    std::wfstream atoms_file;
    std::wfstream spins_file;
    std::wfstream sconfiguration_file;

    std::wstring size1, size2, strk;
    std::wstring m, l, x, y, z;
    std::wstring sx, sy, sz;

    atoms_file.open(c_str(_path_to_folder + "/" + VVIS_VAMPIRE5_ATOMS_NAME_WSTR + VVIS_VAMPIRE5_ATOMS_FORMAT_WSTR), std::ios_base::in);
    spins_file.open(c_str(_path_to_folder + "/" + VVIS_VAMPIRE5_SPINS_START_NAME_WSTR + v5_get_file_number(std::to_string(_number_of_file)) + VVIS_VAMPIRE5_SPINS_FORMAT_WSTR), std::ios_base::in);
    sconfiguration_file.open(c_str(_path_to_folder + "/" + VVIS_VVIS_FILE_START_NAME_WSTR + v5_get_file_number(std::to_string(_number_of_file)) + VVIS_VVIS_FILE_FORMAT_WSTR), std::ios_base::out | std::ios_base::trunc);

    atoms_file >> size1;
    spins_file >> size2;

    if (size1 != size2) return false;

    sconfiguration_file << VVIS_VVIS_COMMENT << L"count" << L'\n';
    sconfiguration_file << size1            << L'\n';
    sconfiguration_file << VVIS_VVIS_COMMENT << L"M" << VVIS_VVIS_SEPARATOR << L"L" << VVIS_VVIS_SEPARATOR << L"X" << VVIS_VVIS_SEPARATOR << L"Y" << VVIS_VVIS_SEPARATOR << L"Z" << VVIS_VVIS_SEPARATOR
        << L"SX" << VVIS_VVIS_SEPARATOR << L"SY" << VVIS_VVIS_SEPARATOR << L"SZ" << L'\n';

    for (int index = 0; !spins_file.eof() && index != std::stoi(size1); ++index) {
        
        atoms_file >> m; while (m[0] == VVIS_VAMPIRE5_DATA_COMMENT) { std::getline(atoms_file, strk); atoms_file >> m; }
        atoms_file >> l; while (l[0] == VVIS_VAMPIRE5_DATA_COMMENT) { std::getline(atoms_file, strk); atoms_file >> l; }
        atoms_file >> x; while (x[0] == VVIS_VAMPIRE5_DATA_COMMENT) { std::getline(atoms_file, strk); atoms_file >> x; }
        atoms_file >> y; while (y[0] == VVIS_VAMPIRE5_DATA_COMMENT) { std::getline(atoms_file, strk); atoms_file >> y; }
        atoms_file >> z; while (z[0] == VVIS_VAMPIRE5_DATA_COMMENT) { std::getline(atoms_file, strk); atoms_file >> z; }
        spins_file >> sx; while (sx[0] == VVIS_VAMPIRE5_DATA_COMMENT) { std::getline(spins_file, strk); atoms_file >> sx; }
        spins_file >> sy; while (sy[0] == VVIS_VAMPIRE5_DATA_COMMENT) { std::getline(spins_file, strk); atoms_file >> sy; }
        spins_file >> sz; while (sz[0] == VVIS_VAMPIRE5_DATA_COMMENT) { std::getline(spins_file, strk); atoms_file >> sz; }
        
        sconfiguration_file << m << VVIS_VVIS_SEPARATOR << l << VVIS_VVIS_SEPARATOR << x << VVIS_VVIS_SEPARATOR << y << VVIS_VVIS_SEPARATOR << z << VVIS_VVIS_SEPARATOR 
            << sx << VVIS_VVIS_SEPARATOR << sy << VVIS_VVIS_SEPARATOR << sz << L'\n';

    }
    
    atoms_file.close();
    spins_file.close();
    sconfiguration_file.close();

    return true;
}
