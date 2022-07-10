#pragma once

#ifndef MATERIAL_HPP
#define MATERIAL_HPP

	#include "../color/RGB.hpp"
	#include "../vertex-shape/vertex.hpp"

	struct Material {

		Rgb color;
		std::wstring name;
		int number;

		Material() : color(Rgb(1, 1, 1)), name(L"undefined"), number(0) {};
		Material(Rgb& _color, std::wstring& _name, int _number) : color(_color), name(_name), number(_number) {};
		Material(Rgb& _color, int _number) : color(_color), name(std::to_wstring(_number)), number(_number) {};

		friend std::wostream& operator<<(std::wostream& _out, const Material& _material);

	};

	bool material_in_vector(std::vector<Material>& _vct, int _index);
	bool set_material(std::vector<Material>& _vct, int _index, Material _mat);
	bool remove_material(std::vector<Material>& _vct, int _index);
	Material find_material_in_vector(std::vector<Material>& _vct, int _index);

	int count_of_materials(const std::vector<Vertex>& _vrt);


#endif // !MATERIAL_HPP