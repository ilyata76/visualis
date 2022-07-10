#include "./material.hpp"

std::wostream& operator<<(std::wostream& _out, const Material& _material) {
	_out << "Index: " << _material.number << L" Color: "; _out << _material.color << L" Name: "; _out << _material.name;
	return _out;
}

bool material_in_vector(std::vector<Material>& _vct, int _index) {

	for (const auto& x : _vct) {
		if (x.number == _index) return true;
	}

	return false;

}

bool set_material(std::vector<Material>& _vct, int _index, Material _mat) {

	if (!material_in_vector(_vct, _index)) return false;

	for (auto& x : _vct) {
		if (x.number == _index) x = _mat;
	}

	return true;
}

Material find_material_in_vector(std::vector<Material>& _vct, int _index) {
	Assert(_vct.size() > 0);
	
	for (const auto& x : _vct) {
		if (x.number == _index) return x;
	}

	throw Exceptio(100, L"no index");
}
