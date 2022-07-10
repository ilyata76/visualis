#pragma once

#ifndef LAYER_HPP
#define LAYER_HPP

	#include "../color/RGB.hpp"

	struct Layer {

		Rgb color;
		std::wstring name;
		int number;

		Layer() : color(Rgb(1, 1, 1)), name(L"undefined"), number(0) {};
		Layer(Rgb& _color, std::wstring& _name, int _number) : color(_color), name(_name), number(_number) {};
		Layer(Rgb& _color, int _number) : color(_color), name(std::to_wstring(_number)), number(_number) {};

		friend std::wostream& operator<<(std::wostream& _out, const Layer& _layer);

	};

	bool layer_in_vector(std::vector<Layer>& _vct, int _index);
	bool set_layer(std::vector<Layer>& _vct, int _index, Layer _lay);
	Layer find_layer_in_vector(std::vector<Layer> _vct, int _index);


#endif // !LAYER_HPP
