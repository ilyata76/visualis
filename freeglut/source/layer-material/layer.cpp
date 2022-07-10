#include "layer.hpp"

std::wostream& operator<<(std::wostream& _out, const Layer& _layer) {
	_out << "\t\t Index: " << _layer.number << L'\n\t\t Color: '; _out << _layer.color << L'\n\t\t Name: '; _out << _layer.name;
	return _out;
}

bool layer_in_vector(std::vector<Layer>& _vct, int _index) {

	for (const auto& x : _vct) {
		if (x.number == _index) return true;
	}

	return false;

}

Layer find_layer_in_vector(std::vector<Layer> _vct, int _index) {
	Assert(_vct.size() > 0);
	
	for (const auto& x : _vct) {
		if (x.number == _index) return x;
	}

	throw Exceptio(100, L"no index");
}
