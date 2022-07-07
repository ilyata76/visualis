#include "./vertex.hpp"

std::vector<Vertex> sconfiguration_parsing(const std::string& _path_to_file) {
    Assert(_path_to_file != VVIS_PATH_PLUG_WSTR);
    Assert(_path_to_file != "\0" && _path_to_file != "\n");
    
    std::vector<Vertex> result;
    
    std::wfstream sconfiguration_file;
    sconfiguration_file.open(c_str(_path_to_file), std::ios_base::in);
    
    std::wstring str = L"#", strk;
    
    do {
        std::getline(sconfiguration_file, str);
    } while (str[0] == '#');

    size_t count = std::stod(str) + 1.0;
    result.reserve(count);

    std::wstring l, m; std::wstring x, y, z, sx, sy, sz;

    for (int index = 0; !sconfiguration_file.eof() && index < count - 1.0; ++index) {
        sconfiguration_file >> m; while (m[0] == VVIS_VAMPIRE5_DATA_COMMENT) { std::getline(sconfiguration_file, strk); sconfiguration_file >> m; }
        sconfiguration_file >> l; while (l[0] == VVIS_VAMPIRE5_DATA_COMMENT) { std::getline(sconfiguration_file, strk); sconfiguration_file >> l; }
        sconfiguration_file >> x; while (x[0] == VVIS_VAMPIRE5_DATA_COMMENT) { std::getline(sconfiguration_file, strk); sconfiguration_file >> x; }
        sconfiguration_file >> y; while (y[0] == VVIS_VAMPIRE5_DATA_COMMENT) { std::getline(sconfiguration_file, strk); sconfiguration_file >> y; }
        sconfiguration_file >> z; while (z[0] == VVIS_VAMPIRE5_DATA_COMMENT) { std::getline(sconfiguration_file, strk); sconfiguration_file >> z; }
        sconfiguration_file >> sx; while (sx[0] == VVIS_VAMPIRE5_DATA_COMMENT) { std::getline(sconfiguration_file, strk); sconfiguration_file >> sx; }
        sconfiguration_file >> sy; while (sy[0] == VVIS_VAMPIRE5_DATA_COMMENT) { std::getline(sconfiguration_file, strk); sconfiguration_file >> sy; }
        sconfiguration_file >> sz; while (sz[0] == VVIS_VAMPIRE5_DATA_COMMENT) { std::getline(sconfiguration_file, strk); sconfiguration_file >> sz; }

        if (m != L"\0" && m != L"\n" && l != L"\0" && l != L"\n" && is_number(l) && is_number(m)) {
            Point p(std::stod(x), std::stod(y), std::stod(z));
            Spin s(std::stod(sx), std::stod(sy), std::stod(sz));
            result.push_back(Vertex(p, s, index, std::stoi(l), std::stoi(m)));
        }

    }

    sconfiguration_file.close();
    return result;
}
