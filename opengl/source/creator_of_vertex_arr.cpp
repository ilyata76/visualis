#include "./include/sample/creator_of_vertex_arr.hpp"

using vvis::creator::Point;
using vvis::creator::Spin;
using vvis::creator::Vertex;


//Vertex::Vertex(Point& p, Spin& s, unsigned int number) {
//	this->point = p;
//	this->spin = s;
//	this->number = number;
//	this->material = INT_PLUG_VVIS;
//	this->layer = INT_PLUG_VVIS;
//}
//
//Vertex::Vertex(Point& p, Spin& s) {
//	this->point = p;
//	this->spin = s;
//	this->number = INT_PLUG_VVIS;
//	this->material = INT_PLUG_VVIS;
//	this->layer = INT_PLUG_VVIS;
//}
//
//Vertex::Vertex(Point& p, Spin& s, unsigned int number, short int layer, short int material) {
//	this->point = p;
//	this->spin = s;
//	this->number = number;
//	this->material = material;
//	this->layer = layer;
//}


Point Vertex::get_point() {
	return this->point;
}

Spin Vertex::get_spin() {
	return this->spin;
}

unsigned int Vertex::get_number() {
	return this->number;
}

short int vvis::creator::Vertex::get_layer() {
	return this->layer;
}

short int vvis::creator::Vertex::get_material() {
	return this->material;
}

///////

std::wstring path_to_folder_ = L"";

std::wstring vvis::creator::get_file_name(const int& number) {
	std::wstring num = std::to_wstring(number); std::wstring base = BASE_NUMBER_OF_FILE_V5;
	size_t num_lenght = num.length(); size_t base_lenght = base.length();
	for (int i = 0; num_lenght != 0; ++i, num.pop_back(), num_lenght = num.length()) {
		base[base_lenght - 1 - i] = num[num_lenght - 1];
	};
	return std::wstring(START_OF_OUR_FILE + base);
}

std::vector <Vertex> vvis::creator::get_out(const int& index) {
	// TODO: не хватает проверок
	

	std::wstring name_of_file = vvis::creator::get_file_name(index);

	std::wfstream input_file;

	input_file.open(path_to_folder_ + L"/" + name_of_file + FORMAT_OF_OUR_FILE, std::ios_base::in);

	std::wstring line_with_number_and_count = [&input_file]() {
		std::wstring str; 
		do { 
			std::getline(input_file, str); 
		} while (str[0] == '#'); // scip #coms

		return str; 
	}();

	std::wstringstream sstream(line_with_number_and_count); 

	int number_of_file = INT_PLUG_VVIS;
	size_t spins_count = INT_PLUG_VVIS;

	int layer = INT_PLUG_VVIS;
	int material = INT_PLUG_VVIS;
	
	double x = DOUBLE_PLUG_VVIS;
	double y = DOUBLE_PLUG_VVIS;
	double z = DOUBLE_PLUG_VVIS;
	double sx = DOUBLE_PLUG_VVIS;
	double sy = DOUBLE_PLUG_VVIS;
	double sz = DOUBLE_PLUG_VVIS;

	std::wstring abob;

	sstream >> number_of_file >> spins_count; // 2nd line
	std::vector<Vertex> result; size_t for_reserve = spins_count + 1; // на последней итерации цикла vector добавляет место под ещё один элемент, хотя его не будет
	result.reserve(for_reserve); // change capacity of vector

	for (int _index = 0; !input_file.eof() && _index != spins_count; ++_index) {
		
		number_of_file = INT_PLUG_VVIS;
		spins_count = INT_PLUG_VVIS;

		layer = INT_PLUG_VVIS;
		material = INT_PLUG_VVIS;

		x = DOUBLE_PLUG_VVIS;
		y = DOUBLE_PLUG_VVIS;
		z = DOUBLE_PLUG_VVIS;
		sx = DOUBLE_PLUG_VVIS;
		sy = DOUBLE_PLUG_VVIS;
		sz = DOUBLE_PLUG_VVIS;

		std::wstring str;

		do { 
			std::getline(input_file, str); 

		} while (str[0] == '#'); // skip #  comments 
		
		std::wstringstream mystream(str);
		mystream >> material >> layer >> x >> y >> z >> sx >> sy >> sz;
		
		// INVERTING OY IN VISUALIZATION
		if (INVERT_Y_FOR_THIRD_REPRESENTATION) { sy = -sy; y = -y; };

		if (str != L"\0" && str != L"\n") result.push_back(Vertex(Point(x, y, z), Spin(sx, sy, sz), _index, layer, material));

	}

	input_file.close();
	return result;
}

vvis::creator::FUNCTION_VERTEX_CONSTINT vvis::creator::create_arry(const std::wstring& p_t_folder) {
	path_to_folder_ = p_t_folder;
	return get_out;
}
