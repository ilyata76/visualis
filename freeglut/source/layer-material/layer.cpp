#include "layer.hpp"

std::wostream& operator<<(std::wostream& _out, const Layer& _layer) {
	_out << "Index: " << _layer.number << L" Color: "; _out << _layer.color << L" Name: "; _out << _layer.name;
	return _out;
}

bool layer_in_vector(std::vector<Layer>& _vct, int _index) {

	for (const auto& x : _vct) {
		if (x.number == _index) return true;
	}

	return false;

}

bool set_layer(std::vector<Layer>& _vct, int _index, Layer _lay) {
	if (!layer_in_vector(_vct, _index)) return false;

	for (auto& x : _vct) {
		if (x.number == _index) x = _lay;
	}

	return true;
}

bool remove_layer(std::vector<Layer>& _vct, int _index){	
	if (!layer_in_vector(_vct, _index)) return false;

	std::vector<Layer> res;

	for (auto& x : _vct) {
		if (x.number != _index) res.push_back(x);
	}

	_vct = res;

	return true;
}

Layer find_layer_in_vector(std::vector<Layer> _vct, int _index) {
	Assert(_vct.size() > 0);
	
	for (const auto& x : _vct) {
		if (x.number == _index) return x;
	}

	throw Exceptio(100, L"no index");
}

int count_of_layers(const std::vector<Vertex>& _vct) {
	int temp = 0;

	for (const auto& x : _vct) {
		if (x.layer > temp) temp = x.layer;
	}

	return temp + 1;
}
