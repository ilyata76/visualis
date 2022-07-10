#pragma once

#ifndef LAYER_HPP
#define LAYER_HPP

	#include "../color/RGB.hpp"

	struct Layer {

		Rgb background;
		std::wstring name;
		int number;

		Layer() : background(Rgb(0.5, 0.5, 0.5)), name(L"undefined"), number(0) {};
		Layer(Rgb& _background, std::wstring& _name, int _number) : background(_background), name(_name), number(_number) {};

		friend std::wostream& operator<<(std::wostream& _out, const Layer& _layer);

	};

	Layer find_layer_in_vector(std::vector<Layer> _vct, int _index);


#endif // !LAYER_HPP
