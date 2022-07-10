#pragma once

#ifndef MATERIAL_HPP
#define MATERIAL_HPP

	#include "../color/RGB.hpp"

	struct Material {

		Rgb background;
		std::wstring name;
		int number;

		Material() : background(Rgb(0.5, 0.5, 0.5)), name(L"undefined"), number(0) {};
		Material(Rgb& _background, std::wstring& _name, int _number) : background(_background), name(_name), number(_number) {};

		friend std::wostream& operator<<(std::wostream& _out, const Material& _material);

	};

	Material find_material_in_vector(std::vector<Material> _vct, int _index);


#endif // !MATERIAL_HPP