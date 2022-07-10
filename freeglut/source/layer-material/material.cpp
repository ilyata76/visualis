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

bool remove_material(std::vector<Material>& _vct, int _index) {
	if (!material_in_vector(_vct, _index)) return false;

	std::vector<Material> res;

	for (auto& x : _vct) {
		if (x.number != _index) res.push_back(x);
	}
	
	_vct = res;

	return true;
}

Material find_material_in_vector(std::vector<Material>& _vct, int _index) {
	Assert(_vct.size() > 0);
	
	for (const auto& x : _vct) {
		if (x.number == _index) return x;
	}

	throw Exceptio(100, L"no index");
}

int count_of_materials(const std::vector<Vertex>& _vct) {
	int temp = 0;

	for (const auto& x : _vct) {
		if (x.material > temp) temp = x.material;
	}

	return temp + 1;
}
