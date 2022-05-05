#include "include/sample/shape.hpp"

wchar_t vvis::visualization::Cone::info_wchar() {
	return SHAPE_CONE;
}

std::wstring vvis::visualization::Cone::info_wstr() {
	return SHAPE_CONE_STR;
}

bool vvis::visualization::Cone::set_draw_configuration() {
	double sx = vrt.get_spin().get(L'x');
	double sy = vrt.get_spin().get(L'y');
	double sz = vrt.get_spin().get(L'z');

	if (sx == 0.0 && sy == 0.0 && sz == 0.0) return false;

	this->euler_phi = vvis::visualization::get_euler_phi(sx, sy, sz);
	this->euler_theta = vvis::visualization::get_euler_theta(sx, sy, sz);

	return true;
}

bool vvis::visualization::Cone::draw(double base, double height, GLint slices, GLint stacks, vvis::visualization::VvisColor_3f color) {
	glColor3f(color.red, color.green, color.blue);
	// повернули
	glRotatef(this->euler_phi, 0, 0, 1);
	glRotatef(this->euler_theta, 0, 1, 0);
	// нарисовали
	glutSolidCone(base, height, slices, stacks);
	// отвернули
	glRotatef(- this->euler_theta, 0, 1, 0);
	glRotatef(- this->euler_phi, 0, 0, 1);

	return true;
}
