#include "./material.hpp"

std::wostream& operator<<(std::wostream& _out, const Material& _material) {
	_out << "\t\t Index: " << _material.number << L'\n\t\t Color: '; _out << _material.color << L'\n\t\t Name: '; _out << _material.name;
	return _out;
}

bool material_in_vector(std::vector<Material>& _vct, int _index) {

	for (const auto& x : _vct) {
		if (x.number == _index) return true;
	}

	return false;

}

Material find_material_in_vector(std::vector<Material>& _vct, int _index) {
	Assert(_vct.size() > 0);
	
	for (const auto& x : _vct) {
		if (x.number == _index) return x;
	}

	throw Exceptio(100, L"no index");
}
